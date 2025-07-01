#include <ucos_ii.h>
#include "Task.h"
#include "usart.h"
#include "LED.h"
#include "SEGGER_SYSVIEW.h"

OS_STK  TASK1stk[APP_CFG_STARTUP_TASK_STK_SIZE];
OS_STK  TASK2stk[APP_CFG_STARTUP_TASK_STK_SIZE];

INT8U *pname;
INT8U err;

int main(void){

	USART2_Init();
	LED_Init();

	OS_TRACE_INIT(); //systemview初始化
	OS_TRACE_START(); //开始记
	OSInit();
	
	OSTaskCreate(TASK1,(void*)0,(OS_STK*)&TASK1stk[APP_CFG_STARTUP_TASK_STK_SIZE-1], 5);
	OSTaskCreate(TASK2,(void*)0,(OS_STK*)&TASK2stk[APP_CFG_STARTUP_TASK_STK_SIZE-1], 6);
	
	
	// 设置任务名
	OSTaskNameSet(5, (INT8U *)"LED_ON", &err);
	OSTaskNameSet(6, (INT8U *)"LED_OFF", &err);
	
	//获得任务名并将其传给Systemview
	OSTaskNameGet(5, &pname, &err);
	SEGGER_SYSVIEW_NameResource((U32)OSTCBPrioTbl[5], (const char *)pname);
	OSTaskNameGet(6, &pname, &err);
	SEGGER_SYSVIEW_NameResource((U32)OSTCBPrioTbl[6], (const char *)pname);
	
	OSStart();
	//return(0);
	
}
