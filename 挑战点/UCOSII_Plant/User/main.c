#include "ucos_ii.h"


// 寄存器地址定义
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
	// GPIOA寄存器
#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*(volatile INT32U*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR (*(volatile INT32U*)(GPIOA_BASE + 0x14))
	
//-------------------------------------------------------------------//
//                      任务与硬件配置                                //
//-------------------------------------------------------------------//
#define TASK_STK_SIZE    128     // 任务堆栈大小
#define TASK1_PRIO       5      // 任务1优先级
#define TASK2_PRIO       6      // 任务2优先级

OS_STK Task1Stk[TASK_STK_SIZE];   // 任务1堆栈
OS_STK Task2Stk[TASK_STK_SIZE];   // 任务2堆栈


void LED_Init(void) {
    RCC_AHB1ENR |= 0x01;          // 使能GPIOA时钟
    GPIOA_MODER &= ~(0x03 << 10); // 清除PA5模式
    GPIOA_MODER |= 0x01 << 10;    // 设置PA5为输出模式
}

void LED_On(void) {
    GPIOA_ODR |= (1 << 5);       // PA5输出高电平
}

void LED_Off(void) {
    GPIOA_ODR &= ~(1 << 5);      // PA5输出低电平
}

void Task_LEDOn(void *pdata) {
    while(1) {
        LED_On();                      // 开灯
        OSTimeDly(500);   // 延时500ms
    }
}

void Task_LEDOff(void *pdata) {
    while(1) {
        LED_Off();                       // 灭灯
        OSTimeDly( 1000);     // 延时500ms
    }
}

//时钟配置
void SystemInit(void)
{
	// 1. 启动HSE 并等待就绪
	RCC_CR |= (1 << 16); // 使能 HSE (HSEON=1)
	while (!(RCC_CR & (1 << 17))); // 等待 HSERDY=1
	
	// 2. 配置 Flash 等待周期 (84MHz 需要 2 WS)
	FLASH_ACR = 0x02; // LATENCY=2 (3 CPU cycles)
	
	// 3. 配置 PLL 参数 (HSE作为输?)
	RCC_PLLCFGR = 0; // 清零寄存器
	RCC_PLLCFGR |= (8 << 0); // PLLM = 8 (分频输?)
	RCC_PLLCFGR |= (336 << 6); // PLLN = 336 (倍频)
	RCC_PLLCFGR |= (1 << 16); // PLLP = 2 (分频因子)
	RCC_PLLCFGR |= (1 << 22); // PLLSRC = HSE
	
	// 4. 启? PLL 并等待就绪
	RCC_CR |= (1 << 24); // PLLON=1
	while (!(RCC_CR & (1 << 25))); // 等待 PLLRDY=1
	
	// 5. 配置总线分频器
	RCC_CFGR = 0;
		RCC_CFGR |= (0 << 4); // HPRE=1 (AHB 不分频)
	RCC_CFGR |= (4 << 10); // PPRE1=2 (APB1 分频因?为2)
	RCC_CFGR |= (0 << 13); // PPRE2=1 (APB2 不分频)
	RCC_CFGR |= (2 << 0); // SW= PLL 作为系统时钟
	
	// 6. 等待时钟切换完成
	while ((RCC_CFGR & 0xC) != 0x8); // (RCC_CFGR & 0xC) == 0x8
	
	// 7. 配置 SysTick（1ms 中断）
	SYSTICK_CTRL = 0; // 先禁? SysTick
	SYSTICK_LOAD = 83999; // 84MHz / 1000Hz - 1
	SYSTICK_VAL = 0; // 清零计数器
	SYSTICK_CTRL |= (1 << 2) | // CLKSOURCE=1 (使? HCLK)
	(1 << 1) | // TICKINT=1 (启?中断)
	(1 << 0); // ENABLE=1 启动定时器
	
	//8、 配置中断优先级
	SHPR3 |= (1<<28);
}

int main()
{
	SystemInit();
	OSInit();                           
    LED_Init(); 
	
    // 创建任务
    OSTaskCreate(Task_LEDOn, NULL, 
                &Task1Stk[TASK_STK_SIZE-1], TASK1_PRIO); 
    OSTaskCreate(Task_LEDOff, NULL,
                &Task2Stk[TASK_STK_SIZE-1], TASK2_PRIO); 
    
    OSStart();                         // 启动任务调度器
	return 0;
}
