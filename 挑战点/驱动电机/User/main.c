#include "stm32f4xx.h"                   // Device header
#include "PWM.h"
#include "Delay.h"

int main(void){
	 PWM_Init();

	 while(1){
		 PWM_SetCompareAll(2000);
		 Delay_ms(500);
		 PWM_SetCompareAll(1000);
		 Delay_s(1);
		 PWM_SetCompareAll(2000);
		 Delay_s(3);
	}

}
