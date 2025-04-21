//#include <app_cfg.h>

#ifndef OS_CPU_H
#define OS_CPU_H



#ifdef   OS_CPU_GLOBALS
#define  OS_CPU_EXT
#else
#define  OS_CPU_EXT  extern
#endif

//#ifdef __cplusplus
//extern  "C" {                                    /* See Note #1.                                       */
//#endif

#ifndef  OS_CPU_EXCEPT_STK_SIZE
#define  OS_CPU_EXCEPT_STK_SIZE      256u        /* Default exception stack size is 256 OS_STK entries */
#endif

//��������
typedef unsigned char BOOLEAN; // ���岼������
typedef unsigned char INT8U; // ?����8λ����
typedef signed char INT8S; // �з���8λ����
typedef unsigned short INT16U; // ?����16λ����
typedef signed short INT16S; // �з���16λ����
typedef unsigned int INT32U; // ?����32λ����
typedef signed int INT32S; // �з���32λ����
typedef float FP32; // �����ȸ�����
typedef double FP64; // ˫���ȸ�����
typedef unsigned int OS_STK; // ÿ��ջ��?Ϊ32λ��
typedef unsigned int OS_CPU_SR;// ����CPU״̬�Ĵ�����??��PSR = 32λ��

/*
*********************************************************************************************************
*                                              Cortex-M
*                                      Critical Section Management
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*             NOT IMPLEMENTED
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts.  In other words, if
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section.
*             NOT IMPLEMENTED
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*********************************************************************************************************
*/

#define  OS_CRITICAL_METHOD   3u

#if OS_CRITICAL_METHOD == 3u
                                                 /* Save current BASEPRI priority lvl for exception... */
                                                 /* .. and set BASEPRI to CPU_CFG_KA_IPL_BOUNDARY      */
#define  OS_ENTER_CRITICAL()  do { cpu_sr = OS_CPU_SR_Save(CPU_CFG_KA_IPL_BOUNDARY << (8u - CPU_CFG_NVIC_PRIO_BITS));} while (0)
                                                 /* Restore CPU BASEPRI priority level.                */
#define  OS_EXIT_CRITICAL()   do { OS_CPU_SR_Restore(cpu_sr);} while (0)
#endif


/*
*********************************************************************************************************
*                                        Cortex-M Miscellaneous
*********************************************************************************************************
*/

#define  OS_STK_GROWTH        1u                 /* Stack grows from HIGH to LOW memory on ARM         */

#define  OS_TASK_SW()         OSCtxSw()


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

OS_CPU_EXT  OS_STK   OS_CPU_ExceptStk[OS_CPU_EXCEPT_STK_SIZE];
OS_CPU_EXT  OS_STK  *OS_CPU_ExceptStkBase;

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if OS_CRITICAL_METHOD == 3u                     /* See OS_CPU_A.ASM                                   */
OS_CPU_SR  OS_CPU_SR_Save         (OS_CPU_SR  new_basepri);
void       OS_CPU_SR_Restore      (OS_CPU_SR  cpu_sr);
#endif

void       OSCtxSw                (void);
void       OSIntCtxSw             (void);
void       OSStartHighRdy         (void);

                                                 /* See OS_CPU_C.C                                     */
//void       OS_CPU_SysTickInit     (INT32U     cnts);
//void       OS_CPU_SysTickInitFreq (INT32U     cpu_freq);

void       SysTick_Handler  (void);
void       PendSV_Handler   (void);

//#ifdef __cplusplus
//}                                                /* End of 'extern'al C lang linkage.                  */
//#endif

#endif
