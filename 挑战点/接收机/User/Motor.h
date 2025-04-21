#ifndef  __MOTOR_H_
#define __MOTOR_H_
#include "stm32f4xx.h"                  // Device header

void Motor_Init();
void Motor_Start(uint8_t speed);

#endif
