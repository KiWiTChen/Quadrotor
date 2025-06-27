#include <os.h>

//寄存器地址定义
#define RCC_BASE 0x40023800
#define RCC_AHB1ENR (*(volatile INT32U*)(RCC_BASE + 0x30))
#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*(volatile INT32U*)(GPIOA_BASE + 0x00))
#define GPIOA_OTYPER (*(volatile INT32U*)(GPIOA_BASE + 0x04))
#define GPIOA_OSPEEDER   (*(volatile INT32U*)(GPIOA_BASE + 0x08))
#define GPIOA_BSRR   (*(volatile INT32U*)(GPIOA_BASE + 0x18))
#define GPIOA_ODR   (*(volatile INT32U*)(GPIOA_BASE + 0x14))

void LED_Init() {
    RCC_AHB1ENR |= 0x01;
    GPIOA_MODER &= ~(0x03 << 10);
    GPIOA_MODER |= 0x01 << 10;
	  GPIOA_OTYPER &= ~(1<<5);
	  GPIOA_OSPEEDER |=(0x03 << 10);
	
	
}

void LED_ON(void) {
    GPIOA_BSRR  = (1<<5);     // PA5输出高电平
}

void LED_OFF(void) {
    GPIOA_BSRR = (1 << 21);      // PA5输出低电平
}
