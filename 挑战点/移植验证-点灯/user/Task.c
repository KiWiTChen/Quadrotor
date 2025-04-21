#include "Task.h"
#include "LED.h"
#include "usart.h"
#include <os.h>


void TASK1(void *p_arg){
	while(1){
		   LED_ON();
		   OSTimeDly(1000);

	}
	
	
}

void TASK2(void *p_arg){
	while(1){
		LED_OFF();
		OSTimeDly(1500);  
		
	}
	
	
}
