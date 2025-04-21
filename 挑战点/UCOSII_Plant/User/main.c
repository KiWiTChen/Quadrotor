#include "ucos_ii.h"


// �Ĵ�����ַ����
#define RCC_BASE 0x40023800U
#define RCC_AHB1ENR (*(volatile INT32U*)(RCC_BASE + 0x30))
#define RCC_CR (*(volatile INT32U *)(RCC_BASE + 0x00))
#define RCC_PLLCFGR (*(volatile INT32U *)(RCC_BASE + 0x04))
#define RCC_CFGR (*(volatile INT32U *)(RCC_BASE + 0x08))
#define FLASH_ACR (*(volatile INT32U *)(0x40023C00U))
#define SYSTICK_BASE 0xE000E010
#define SYSTICK_CTRL (*(volatile INT32U *)(SYSTICK_BASE + 0x00))
#define SYSTICK_LOAD (*(volatile INT32U *)(SYSTICK_BASE + 0x04))
#define SYSTICK_VAL (*(volatile INT32U *)(SYSTICK_BASE + 0x08))
#define SHPR3 (*(volatile INT32U *)(0xE000ED20U))
	// GPIOA�Ĵ���
#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*(volatile INT32U*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR (*(volatile INT32U*)(GPIOA_BASE + 0x14))
	
//-------------------------------------------------------------------//
//                      ������Ӳ������                                //
//-------------------------------------------------------------------//
#define TASK_STK_SIZE    128     // �����ջ��С
#define TASK1_PRIO       5      // ����1���ȼ�
#define TASK2_PRIO       6      // ����2���ȼ�

OS_STK Task1Stk[TASK_STK_SIZE];   // ����1��ջ
OS_STK Task2Stk[TASK_STK_SIZE];   // ����2��ջ


void LED_Init(void) {
    RCC_AHB1ENR |= 0x01;          // ʹ��GPIOAʱ��
    GPIOA_MODER &= ~(0x03 << 10); // ���PA5ģʽ
    GPIOA_MODER |= 0x01 << 10;    // ����PA5Ϊ���ģʽ
}

void LED_On(void) {
    GPIOA_ODR |= (1 << 5);       // PA5����ߵ�ƽ
}

void LED_Off(void) {
    GPIOA_ODR &= ~(1 << 5);      // PA5����͵�ƽ
}

void Task_LEDOn(void *pdata) {
    while(1) {
        LED_On();                      // ����
        OSTimeDly(500);   // ��ʱ500ms
    }
}

void Task_LEDOff(void *pdata) {
    while(1) {
        LED_Off();                       // ���
        OSTimeDly( 1000);     // ��ʱ500ms
    }
}

//ʱ������
void SystemInit(void)
{
	// 1. ����HSE ���ȴ�����
	RCC_CR |= (1 << 16); // ʹ�� HSE (HSEON=1)
	while (!(RCC_CR & (1 << 17))); // �ȴ� HSERDY=1
	
	// 2. ���� Flash �ȴ����� (84MHz ��Ҫ 2 WS)
	FLASH_ACR = 0x02; // LATENCY=2 (3 CPU cycles)
	
	// 3. ���� PLL ���� (HSE��Ϊ��?)
	RCC_PLLCFGR = 0; // ����Ĵ���
	RCC_PLLCFGR |= (8 << 0); // PLLM = 8 (��Ƶ��?)
	RCC_PLLCFGR |= (336 << 6); // PLLN = 336 (��Ƶ)
	RCC_PLLCFGR |= (1 << 16); // PLLP = 2 (��Ƶ����)
	RCC_PLLCFGR |= (1 << 22); // PLLSRC = HSE
	
	// 4. ��? PLL ���ȴ�����
	RCC_CR |= (1 << 24); // PLLON=1
	while (!(RCC_CR & (1 << 25))); // �ȴ� PLLRDY=1
	
	// 5. �������߷�Ƶ��
	RCC_CFGR = 0;
		RCC_CFGR |= (0 << 4); // HPRE=1 (AHB ����Ƶ)
	RCC_CFGR |= (4 << 10); // PPRE1=2 (APB1 ��Ƶ��?Ϊ2)
	RCC_CFGR |= (0 << 13); // PPRE2=1 (APB2 ����Ƶ)
	RCC_CFGR |= (2 << 0); // SW= PLL ��Ϊϵͳʱ��
	
	// 6. �ȴ�ʱ���л����
	while ((RCC_CFGR & 0xC) != 0x8); // (RCC_CFGR & 0xC) == 0x8
	
	// 7. ���� SysTick��1ms �жϣ�
	SYSTICK_CTRL = 0; // �Ƚ�? SysTick
	SYSTICK_LOAD = 83999; // 84MHz / 1000Hz - 1
	SYSTICK_VAL = 0; // ���������
	SYSTICK_CTRL |= (1 << 2) | // CLKSOURCE=1 (ʹ? HCLK)
	(1 << 1) | // TICKINT=1 (��?�ж�)
	(1 << 0); // ENABLE=1 ������ʱ��
	
	//8�� �����ж����ȼ�
	SHPR3 |= (1<<28);
}

int main()
{
	SystemInit();
	OSInit();                           
    LED_Init(); 
	
    // ��������
    OSTaskCreate(Task_LEDOn, NULL, 
                &Task1Stk[TASK_STK_SIZE-1], TASK1_PRIO); 
    OSTaskCreate(Task_LEDOff, NULL,
                &Task2Stk[TASK_STK_SIZE-1], TASK2_PRIO); 
    
    OSStart();                         // �������������
	return 0;
}
