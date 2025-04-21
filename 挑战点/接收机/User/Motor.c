#include "stm32f4xx.h"                  // Device header
#include "PWM.h"
#include "Delay.h"

void Motor_Init(){
  PWM_Init();
  Delay_ms(500);
}


void Motor_Start(uint8_t speed){
	speed = speed <100 ? (speed>0 ? speed : 0) : 100;
	PWM_SetCompareAll((speed+100)*10);
}
