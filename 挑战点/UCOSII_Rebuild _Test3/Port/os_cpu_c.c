#include "os_cpu.h"

// ϵͳ��ʼ��������ͨ����������Ӳ����ص�����
void SystemInit(){}
// ����յĹ��Ӻ���
void OSInitHookBegin(){}
void OSInitHookEnd(){}
void OSTCBInitHook(){}
void OSTaskCreateHook(){}
void OSTaskIdleHook(){}
void OSTaskReturnHook(){}
void OSTaskSwHook(){}
// �����ջ��ʼ��������Ϊ����������ջ�ռ�
OS_STK *OSTaskStkInit(void (*task)(void *p_arg), void *p_arg, OS_STK *ptos,INT16U opt)
{
	return ptos;
}
// ����1���յ�CPU�쳣ջ����ַ
void OS_CPU_ExceptStkBase(){}
// �����ں˿�ʹ�õ����ȼ��߽�
void OS_KA_BASEPRI_Boundary(){}
