#ifndef __TASK_H_
#define __TASK_H_

#include "ucos_ii.h"
// �����ź����ͻ�����������Ϊextern
extern OS_EVENT *PPM_Sem;   
extern OS_EVENT *Data_Mutex;

void TASK_ShowGY86Data(void *p_arg);
void TASK_ChangeMotor(void *p_arg);
#endif
