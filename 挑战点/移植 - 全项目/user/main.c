//main.c
#include <ucos_ii.h>
#include "Task.h"
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "OLED.h"
#include "PPM.h"
#include "PWM.h"
#include "Delay.h"
#include "MYIIC.h"
#include "GY86.h"
#include "ATKBLE01.h"
#include "stdio.h"

OS_STK  TASK_ShowGY86Datastk[APP_CFG_STARTUP_TASK_STK_SIZE];
OS_STK  TASK_ChangeMotorstk[APP_CFG_STARTUP_TASK_STK_SIZE];

OS_EVENT *PPM_Sem;    // ����֪ͨ������������
OS_EVENT *Data_Mutex; // ����Rc_Data�Ļ�����

int main(void){
	PPM_Init();
	PWM_Init();
    GY86_Init();  
	BLE_Init();
	OSInit();
	
	// ����ͬ������
    INT8U err;
    PPM_Sem = OSSemCreate(0);
    Data_Mutex = OSMutexCreate(0, &err);
	
	//�������
    PWM_SetCompareAll(1000);
	Delay_s(1);
	
	
	OSTaskCreate(TASK_ChangeMotor,(void*)0,(OS_STK*)&TASK_ChangeMotorstk[APP_CFG_STARTUP_TASK_STK_SIZE-1], 5);
	OSTaskCreate(TASK_ShowGY86Data,(void*)0,(OS_STK*)&TASK_ShowGY86Datastk[APP_CFG_STARTUP_TASK_STK_SIZE-1], 6);
	OSStart();
	
	return 0;
	
}
