#include <ucos_ii.h>
#include "Task.h"
#include "usart.h"


OS_STK  TASK1stk[APP_CFG_STARTUP_TASK_STK_SIZE];
OS_STK  TASK2stk[APP_CFG_STARTUP_TASK_STK_SIZE];

//OS_EVENT *LEDON_Sem;
//OS_EVENT *LEDOFF_Sem;

int main(void){

	USART2_Init();

	OSInit();
//配置优先级	
//	INT32U prio;	
//	prio = SCB_SHPR3;
//	prio &= 0x0000FFFF;
//	prio |=  (0xFFFE << 16);
//	LEDON_Sem = OSSemCreate(1);
//	LEDOFF_Sem = OSSemCreate(0);
	
	OSTaskCreate(TASK1,(void*)0,(OS_STK*)&TASK1stk[APP_CFG_STARTUP_TASK_STK_SIZE-1], 5);
	OSTaskCreate(TASK2,(void*)0,(OS_STK*)&TASK2stk[APP_CFG_STARTUP_TASK_STK_SIZE-1], 6);
	OSStart();
	
	
	return(0);
	
}

