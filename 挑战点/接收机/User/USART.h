#ifndef __ATKBLE01_H
#define __ATKBLE01_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include <stdarg.h>

/* Defines -------------------------------------------------------------------*/ 

extern uint8_t Serial_TxPacket[4];
extern uint8_t Serial_RxPacket[4];
extern uint8_t Serial_RxFlag;
extern uint16_t Serial_RxData;

/* Functions ------------------------------------------------------------------*/
void Serial_Init(void);

void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
uint32_t Serial_Pow(uint32_t x, uint32_t y);
int fputc(int ch, FILE *f);
void Serial_Printf(char *format, ...);
uint8_t Serial_GetRxFlag(void);
	
void Serial_SendPacket(void);

#endif

	
