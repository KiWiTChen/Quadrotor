#ifndef __TASK_H_
#define __TASK_H_

#include "ucos_ii.h"
// 定义信号量和互斥量，声明为extern
extern OS_EVENT *PPM_Sem;   
extern OS_EVENT *Data_Mutex;

void TASK_ShowGY86Data(void *p_arg);
void TASK_ChangeMotor(void *p_arg);
#endif
