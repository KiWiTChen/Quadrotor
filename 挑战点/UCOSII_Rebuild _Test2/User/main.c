#include <ucos_ii.h>
#include "Task.h"
#include "usart.h"


OS_STK  TASK1stk[APP_CFG_STARTUP_TASK_STK_SIZE];
OS_STK  TASK2stk[APP_CFG_STARTUP_TASK_STK_SIZE];


int main(void){

	USART2_Init();

	OSInit();
	
	OSTaskCreate(TASK1,(void*)0,(OS_STK*)&TASK1stk[APP_CFG_STARTUP_TASK_STK_SIZE-1], 5);
	OSTaskCreate(TASK2,(void*)0,(OS_STK*)&TASK2stk[APP_CFG_STARTUP_TASK_STK_SIZE-1], 6);
	OSStart();
	
	
	//return(0);
	
}
