#include "stm32f4xx.h"                  // Device header
#include "PWM.h"
#include "Delay.h"

void Motor_Init(){
	PWM_Init();
	PWM_SetCompareAll(10000);
	Delay_ms(5000);

}


void setSpeedAll(uint8_t speed){
	speed = speed <100 ? (speed>0 ? speed : 0) : 100;
	PWM_SetCompareAll(speed*200);
}
