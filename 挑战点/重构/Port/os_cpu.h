#ifndef   OS_CPU_H
#define   OS_CPU_H

//include field
#include "ucos_ii.h"
#include "std_int.h"



typedef INT32U OS_STK;


void OSInitHookBegin(){};

void OSInitHookEnd(){};
void OSIntCtxSw(){};
void OSStartHighRdy(){};
void OSTCBInitHook{};
void OSTaskCreateHook{};
void OSTaskIdleHook(){};
void OSTaskReturnHook(){};
	
OS_STK *OSTaskStkInit(void(*task)(void*p_arg),void *p_arg,OS_STK *ptos,INT16U opt){return ptos;}

#endif
