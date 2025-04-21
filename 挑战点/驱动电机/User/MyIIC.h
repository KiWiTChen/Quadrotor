#ifndef __MYIIC_H_
#define __MYIIC_H_

#include "stm32f4xx.h"                  // Device header

void MyIIC_Init();
void MyIIC_W_SCL(int BitValue);
void MyIIC_W_SDA(int BitValue);

uint8_t MyIIC_R_SCL();
uint8_t MyIIC_R_SDA();

void MyIIC_Start(void);
void MyIIC_Stop(void);

void MyIIC_SendByte(uint8_t Byte);
uint8_t MyIIC_ReceiveByte();

void MyIIC_SendACK(uint8_t AckBit);
uint8_t MyIIC_ReceiveACK();

#endif
