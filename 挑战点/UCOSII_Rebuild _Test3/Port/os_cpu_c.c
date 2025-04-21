#include "os_cpu.h"

// 系统初始化函数，通常用于设置硬件相关的设置
void SystemInit(){}
// 定义空的钩子函数
void OSInitHookBegin(){}
void OSInitHookEnd(){}
void OSTCBInitHook(){}
void OSTaskCreateHook(){}
void OSTaskIdleHook(){}
void OSTaskReturnHook(){}
void OSTaskSwHook(){}
// 任务堆栈初始化函数，为新任务分配堆栈空间
OS_STK *OSTaskStkInit(void (*task)(void *p_arg), void *p_arg, OS_STK *ptos,INT16U opt)
{
	return ptos;
}
// 定义1个空的CPU异常栈基地址
void OS_CPU_ExceptStkBase(){}
// 设置内核可使用的优先级边界
void OS_KA_BASEPRI_Boundary(){}
