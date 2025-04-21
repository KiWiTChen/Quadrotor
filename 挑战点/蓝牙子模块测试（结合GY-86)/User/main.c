#include "stm32f4xx.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "MYIIC.h"
#include "GY86.h"
#include "ATKBLE01.h"
//蓝牙模块测试：GY-86获取相关信息后通过蓝牙模块发送给上位机

int main(void){
	uint16_t x,y,z;
	int16_t AX, AY, AZ, GX, GY, GZ;
    GY86_Init();
	BLE_Init();
    OLED_Init();
    OLED_Clear();
	 
	 while(1){
				
	   GY86_GetData(&x, &y, &z, &AX, &AY, &AZ, &GX, &GY, &GZ);
//       BLE_Printf ("%5d\n",AX);
//		 BLE_Printf ("%5d\n",AY);
//		 BLE_Printf ("%5d\n",AZ);
//		 BLE_Printf ("%5d\n",GX);
//		 BLE_Printf ("%5d\n",GY);
//		 BLE_Printf ("%5d\n",GZ);
//		 BLE_Printf ("%5d\n",x);
//		 BLE_Printf ("%5d\n",y);
//		 BLE_Printf ("%5d\n",z);
//		 Delay_s(1);
		 
    
		OLED_ShowSignedNum(2, 1, AX, 5);
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);

		
	}

}
