#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "USART.h"
#include "Receiver.h"



int main(void){
	REC_Init();
	Serial_Init();
	OLED_Init();

	OLED_Clear();
	
	 while(1){
		 Serial_Printf("CH1:  %16d\r\n", RE_Data[1]);   
	   Serial_Printf("CH2:  %16d\r\n", RE_Data[2]);  
	   Serial_Printf("CH3:  %16d\r\n", RE_Data[3]);
	   Serial_Printf("CH4:  %16d\r\n", RE_Data[4]);
	   Serial_Printf("CH5:  %16d\r\n", RE_Data[5]);
	   Serial_Printf("CH6:  %16d\r\n", RE_Data[6]);
	   Serial_Printf("CH7:  %16d\r\n", RE_Data[7]);
	   Serial_Printf("CH8:  %16d\r\n", RE_Data[8]);    
		 Delay_s(1);		 
		 
//	 	Rc.ROLL = Rc_Val[1];
//	 	Rc.PITCH = Rc_Val[2];
//	 	Rc.THROTTLE = Rc_Val[3];
//	 	Rc.YAW = Rc_Val[4];
//	 	Rc.AUX1 = Rc_Val[5];
//	 	Rc.AUX2 = Rc_Val[6];
//	 	Rc.AUX3 = Rc_Val[7];
//	 	Rc.AUX4 = Rc_Val[8];
	 

 }
}

