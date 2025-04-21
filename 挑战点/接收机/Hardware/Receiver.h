#ifndef __RECEIVER_H
#define __RECEIVER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Defines -------------------------------------------------------------------*/ 
//TIM3_CH1
#define REC_PORT GPIOA
#define REC_PIN  GPIO_Pin_1

extern uint16_t RE_Data[9];
extern uint16_t okay2;

/* Functions ------------------------------------------------------------------*/
void REC_Init(void);

#endif

