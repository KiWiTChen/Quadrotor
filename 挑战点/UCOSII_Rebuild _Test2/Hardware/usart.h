#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include <stdint.h>  // keil�����Դ���һ���⣬�������������͵Ķ���

// USART1��ʼ��
void USART2_Init(void);

// �����ַ�
void USART2_SendChar(uint8_t ch);

// �����ַ�
//uint8_t USART2_ReceiveChar(void);

// �����ַ���
void USART2_SendStr(char *str);

// �������֣�baseΪ����
void USART2_SendNumber(int32_t num, uint8_t base);

// �����ַ���
//void USART2_ReceiveString(char *buf, uint32_t max_len);

//// ��ȡϵͳʱ��Դ
//const char* get_sysclk_source(void);

//// ��ȡ��Ƶϵ������
//const char* get_prescaler_desc(uint32_t reg_val, uint32_t shift, uint32_t mask);

//// ����ʱ��Ƶ��
//void calculate_clocks(uint32_t hse_freq, uint32_t *sysclk, uint32_t *hclk, uint32_t *pclk1, uint32_t *pclk2);
#endif
