#include "stm32f4xx.h"                  // Device header
#include "GY86.h"
#include "OLED.h"
#include "ATKBLE01.h"
uint16_t x,y,z;
int16_t AX, AY, AZ, GX, GY, GZ;

void Show_GY86(void){
	
	   GY86_GetData(&x, &y, &z, &AX, &AY, &AZ, &GX, &GY, &GZ);
		 OLED_ShowNum(2,6,x, 5);
		 OLED_ShowNum(3,6,y, 5);
		 OLED_ShowNum(4,6,z, 5);
     BLE_Printf ("%5d\n",AX);
		 BLE_Printf ("%5d\n",AY);
		 BLE_Printf ("%5d\n",AZ);
		 BLE_Printf ("%5d\n",GX);
		 BLE_Printf ("%5d\n",GY);
		 BLE_Printf ("%5d\n",GZ);
}
