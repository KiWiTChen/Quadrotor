#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_rcc.h"

RCC_ClocksTypeDef Clocks;

void Delay_us(uint16_t xus)
{
	RCC_GetClocksFreq(&Clocks);
	
	SysTick->LOAD = xus * (Clocks.HCLK_Frequency / 1000000);		//设置重装载值	
	SysTick->VAL = 0x00;		//VAL清零
	SysTick->CTRL |= 0x00000005;		//HCLK时钟1分频，开启SysTick
	while(!(SysTick->CTRL & (1<<16)));		//等待VAL清零COUNTFLAG位置1
	SysTick->CTRL = 0x00000004;		//关闭SysTick
}

void Delay_ms(uint16_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}

void Delay_s(uint16_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
}
