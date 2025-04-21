#include "usart.h"

#define    PA2  TX
#define    PA3  RX

#define RCC_CR          *(volatile uint32_t *)(RCC_BASE + 0x00)
#define RCC_PLLCFGR     *(volatile uint32_t *)(RCC_BASE + 0x04)
#define RCC_CFGR        *(volatile uint32_t *)(RCC_BASE + 0x08)

#define SYSTICK_BASE    0xE000E010U
#define SYSTICK_CTRL    *(volatile uint32_t *)(SYSTICK_BASE + 0x00)
#define SYSTICK_LOAD    *(volatile uint32_t *)(SYSTICK_BASE + 0x04)

#define RCC_BASE        0x40023800
#define RCC_APB1ENR     *(volatile uint32_t*)(RCC_BASE + 0x40)  
#define RCC_AHB1ENR     *(volatile uint32_t*)(RCC_BASE + 0x30)  


#define GPIOA_BASE      0x40020000
#define GPIOA_MODER     *(volatile uint32_t*)(GPIOA_BASE + 0x00)
#define GPIOA_AFRL      *(volatile uint32_t*)(GPIOA_BASE + 0x20)


#define USART2_BASE     0x40004400
#define USART2_SR       *(volatile uint32_t*)(USART2_BASE + 0x00) // 状态寄存器
#define USART2_DR       *(volatile uint32_t*)(USART2_BASE + 0x04) // 数据寄存器
#define USART2_BRR      *(volatile uint32_t*)(USART2_BASE + 0x08) // 波特率寄存器
#define USART2_CR1      *(volatile uint32_t*)(USART2_BASE + 0x0C) // 控制寄存器1

void USART2_Init(void) {
    // 1. 开启时钟
    RCC_AHB1ENR |= (1 << 0);      // 使能GPIOA时钟
    RCC_APB1ENR |= (1 << 17);      // 使能USART2时钟

    // 2. 配置GPIO复用模式（PA2=TX, PA3=RX）
	GPIOA_MODER &= ~(0x03 << (2 * 2));  // 清除PA2模式
    GPIOA_MODER |=  (0x02 << (2 * 2));  // 复用功能模式
    GPIOA_AFRL &= ~(0xF << (4 * 2));  // 清除AFRL2
    GPIOA_AFRL |=  (0x7 << (4 * 2));  // AF7（USART2

    // 3. 配置波特率（假设APB1时钟频率为42MHz）
    USART2_BRR = 0x1117;

    // 4. 启用USART功能
    USART2_CR1 |= (1 << 13) |    // UE（使能USART）
                   (1 << 3);      // TE（使能发送）
}

// 阻塞式发送单个字符
void USART2_SendChar(uint8_t ch) 
{
    while (!(USART2_SR & (1 << 7))); // 等待TXE标志置位
    USART2_DR = (ch & 0xFF);
}

//发送字符串
void USART2_SendStr(char *str)
{
	while(*str)
	{
		USART2_SendChar(*str++);
	}
}

void USART2_SendNumber(int32_t num, uint8_t base) {
    char buffer[32];  // 缓冲区大小足够处理32位二进制数
    uint8_t i = 0;
    uint8_t is_negative = 0;

    // 参数校验
   

    // 处理负数（仅限十进制）
    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }

    // 处理0的特殊情况
    if (num == 0) {
        USART2_SendChar('0');
        return;
    }

    // 数字转字符（逆序存储）
    while (num > 0) {
        uint32_t rem = num % base;
        buffer[i++] = (rem < 10) ? (rem + '0') : (rem - 10 + 'A');
        num /= base;
    }

    // 添加负号
    if (is_negative) {
        buffer[i++] = '-';
    }

    // 逆序发送字符
    while (i > 0) {
        USART2_SendChar(buffer[--i]);
    }
}

