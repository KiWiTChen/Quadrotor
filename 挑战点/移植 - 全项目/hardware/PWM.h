#ifndef __PWM_H_
#define __PWM_H_
#include "stm32f4xx.h"                  // Device header


void PWM_Init(void);


void PWM_SetCompareAll(uint16_t Compare);

#endif
