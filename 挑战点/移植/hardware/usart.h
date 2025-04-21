#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include <stdint.h>  // keil工程自带的一个库，里面有数据类型的定义

// USART1初始化
void USART2_Init(void);

// 发送字符
void USART2_SendChar(uint8_t ch);

// 接收字符
//uint8_t USART2_ReceiveChar(void);

// 发送字符串
void USART2_SendStr(char *str);

// 发生数字，base为进制
void USART2_SendNumber(int32_t num, uint8_t base);

// 接收字符串
//void USART2_ReceiveString(char *buf, uint32_t max_len);

//// 获取系统时钟源
//const char* get_sysclk_source(void);

//// 获取分频系数描述
//const char* get_prescaler_desc(uint32_t reg_val, uint32_t shift, uint32_t mask);

//// 计算时钟频率
//void calculate_clocks(uint32_t hse_freq, uint32_t *sysclk, uint32_t *hclk, uint32_t *pclk1, uint32_t *pclk2);
#endif
