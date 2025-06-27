//main.c
#include <ucos_ii.h>
#include "Task.h"
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "OLED.h"
#include "PPM.h"
#include "PWM.h"
#include "Delay.h"
#include "MYIIC.h"
#include "GY86.h"
#include "ATKBLE01.h"
#include "stdio.h"
#include "SEGGER_SYSVIEW.h"

#define  OS_TRACE_INIT()                             SEGGER_SYSVIEW_Conf()
INT8U *pname;
INT8U err;

OS_STK  TASK_ShowGY86Datastk[APP_CFG_STARTUP_TASK_STK_SIZE];
OS_STK  TASK_ChangeMotorstk[APP_CFG_STARTUP_TASK_STK_SIZE];

OS_EVENT *PPM_Sem;    // 用于通知任务有新数据

int main(void){
	//硬件初始化
	PPM_Init();
	PWM_Init();
    GY86_Init();  
	BLE_Init();
	OLED_Init();
	
	OS_TRACE_INIT(); //systemview初始化
	OS_TRACE_START(); //开始记录
	OSInit();
	
	
	//电调解锁
    PWM_SetCompareAll(1000);
	Delay_s(1);
	
	//任务创建
	OSTaskCreate(TASK_ChangeMotor,(void*)0,(OS_STK*)&TASK_ChangeMotorstk[APP_CFG_STARTUP_TASK_STK_SIZE-1], 5);
	OSTaskCreate(TASK_ShowGY86Data,(void*)0,(OS_STK*)&TASK_ShowGY86Datastk[APP_CFG_STARTUP_TASK_STK_SIZE-1],6);
	
	// 设置任务名
	OSTaskNameSet(5, (INT8U *)"Change_task", &err);
	OSTaskNameSet(6, (INT8U *)"Show_task", &err);
	
	//获得任务名并将其传给Systemview
	OSTaskNameGet(5, &pname, &err);
	SEGGER_SYSVIEW_NameResource((U32)OSTCBPrioTbl[5], (const char *)pname);
	OSTaskNameGet(6, &pname, &err);
	SEGGER_SYSVIEW_NameResource((U32)OSTCBPrioTbl[6], (const char *)pname);
	OSStart();
	
	return 0;
	
}
