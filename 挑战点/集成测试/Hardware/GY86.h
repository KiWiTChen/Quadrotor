#ifndef __GY86_H_
#define __GY86_H_
#include "stm32f4xx.h"                  // Device header
void GY86_WriteRegister(uint8_t SlaveAddress, uint8_t RegisterAddress, uint8_t val);

uint8_t GY86_ReadRegister(uint8_t SlaveAddress, uint8_t RegisterAddress);
void MPU6050_Init(void);
void HMC5883L_Init(void);
void GY86_Init(void);
void GY86_GetData(uint16_t *x, uint16_t *y, uint16_t *z, int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                              int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);


#endif
