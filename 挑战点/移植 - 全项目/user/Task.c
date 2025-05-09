//Task.c�ļ������÷����������ȼ����
#include "Task.h"
#include <ucos_ii.h>
#include <os.h>
#include "stm32f4xx.h"                  // Device header
#include "GY86.h"
#include "OLED.h"
#include "ATKBLE01.h"
#include "PWM.h"

uint16_t x,y,z;
int16_t AX, AY, AZ, GX, GY, GZ;
uint16_t Rc_Data[8];
uint8_t Cal=0; 


void TIM2_IRQHandler(void)
{
	OS_CPU_SR  cpu_sr = 0u;
    OSIntEnter();  // �����ж�

    if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
    {
        uint32_t Rc_Val = TIM_GetCapture1(TIM2);
        
        //������Ҫ������������
        OS_ENTER_CRITICAL();
        if(Rc_Val > 2050){
            Cal = 0;
        }
        else if(Cal < 8){
            Rc_Data[Cal] = Rc_Val;
            Cal++;
            
            // ��8ͨ����������ʱ�����ź���
            if(Cal >= 8){
                OSSemPost(PPM_Sem);  // ֪ͨ����
            }
        }
        OS_EXIT_CRITICAL();
        
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
    }
    
    OSIntExit();  // �˳��ж�
}

void TASK_ShowGY86Data(void *p_arg){
	while(1){
		GY86_GetData(&x, &y, &z, &AX, &AY, &AZ, &GX, &GY, &GZ);
				 OLED_ShowNum(2,6,x, 5);
				 OLED_ShowNum(3,6,y, 5);
				 OLED_ShowNum(4,6,z, 5);
			 BLE_Printf ("%5d\n",AX);
				 BLE_Printf ("%5d\n",AY);
				 BLE_Printf ("%5d\n",AZ);
				 BLE_Printf ("%5d\n",GX);
				 BLE_Printf ("%5d\n",GY);
				 BLE_Printf ("%5d\n",GZ);	
	}
}
void TASK_ChangeMotor(void *p_arg){
	INT8U err;
    
    while(1){
        // �ȴ��ź���
        OSSemPend(PPM_Sem, 0, &err); 
        // ��ȡ���ݷ���Ȩ
        OSMutexPend(Data_Mutex, 0, &err);
        uint16_t throttle = Rc_Data[1];  //ͨ��1��������
        OSMutexPost(Data_Mutex);
        // ���õ��ת��
        PWM_SetCompareAll(throttle);
    }
}
