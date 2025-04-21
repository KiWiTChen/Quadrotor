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
#include "Test.h"

uint16_t Rc_Data[8];
uint8_t Cal=0; 

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1)!= RESET)   //状态寄存器
	{
		 uint32_t Rc_Val = TIM_GetCapture1(TIM2); //获取CRR
	
		if(Rc_Val > 2050){             //捕获标志
			Cal = 0;
		}
		else if(Cal < 8){
			Rc_Data[Cal] = Rc_Val;
			Cal++;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);  //清除标志位
	}
}
	

int main(void){

	  PPM_Init();
		PWM_Init();
    GY86_Init();  
	  BLE_Init();

    PWM_SetCompareAll(1000);
		Delay_s(1);
	 while(1){
		
		 Show_GY86();
		 PWM_SetCompareAll(Rc_Data[1]);
	
		
	}

}
