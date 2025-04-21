#include "Task.h"
//#include "LED.h"
#include "usart.h"
#include <os.h>

extern OS_EVENT *LEDON_Sem;
extern OS_EVENT *LEDOFF_Sem;

void TASK1(void *p_arg){
	//LED_Init();
//	INT8U err;
	while(1){
		   //OSSemPend(LEDON_Sem, 0, &err);  // 请求信号量（无限等待）
		   //LED_ON();
		   USART2_SendChar('a');
		   //OSSemPost(LEDOFF_Sem);           // 释放信号量
		   OSTimeDly(1000);

	}
	
	
}

void TASK2(void *p_arg){
//	INT8U err;
	while(1){
		//OSSemPend(LEDOFF_Sem, 0, &err);  // 请求信号量（无限等待）
		//LED_OFF();
		USART2_SendChar('b');
		//OSSemPost(LEDON_Sem);           // 释放信号量
		OSTimeDly(1500);  
		
	}
	
	
}
