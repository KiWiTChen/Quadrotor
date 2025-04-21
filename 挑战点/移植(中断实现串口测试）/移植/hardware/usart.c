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
#define USART2_SR       *(volatile uint32_t*)(USART2_BASE + 0x00) // ״̬�Ĵ���
#define USART2_DR       *(volatile uint32_t*)(USART2_BASE + 0x04) // ���ݼĴ���
#define USART2_BRR      *(volatile uint32_t*)(USART2_BASE + 0x08) // �����ʼĴ���
#define USART2_CR1      *(volatile uint32_t*)(USART2_BASE + 0x0C) // ���ƼĴ���1

void USART2_Init(void) {
    // 1. ����ʱ��
    RCC_AHB1ENR |= (1 << 0);      // ʹ��GPIOAʱ��
    RCC_APB1ENR |= (1 << 17);      // ʹ��USART2ʱ��

    // 2. ����GPIO����ģʽ��PA2=TX, PA3=RX��
	GPIOA_MODER &= ~(0x03 << (2 * 2));  // ���PA2ģʽ
    GPIOA_MODER |=  (0x02 << (2 * 2));  // ���ù���ģʽ
    GPIOA_AFRL &= ~(0xF << (4 * 2));  // ���AFRL2
    GPIOA_AFRL |=  (0x7 << (4 * 2));  // AF7��USART2

    // 3. ���ò����ʣ�����APB1ʱ��Ƶ��Ϊ42MHz��
    USART2_BRR = 0x1117;

    // 4. ����USART����
    USART2_CR1 |= (1 << 13) |    // UE��ʹ��USART��
                   (1 << 3);      // TE��ʹ�ܷ��ͣ�
}

// ����ʽ���͵����ַ�
void USART2_SendChar(uint8_t ch) 
{
    while (!(USART2_SR & (1 << 7))); // �ȴ�TXE��־��λ
    USART2_DR = (ch & 0xFF);
}

//�����ַ���
void USART2_SendStr(char *str)
{
	while(*str)
	{
		USART2_SendChar(*str++);
	}
}

void USART2_SendNumber(int32_t num, uint8_t base) {
    char buffer[32];  // ��������С�㹻����32λ��������
    uint8_t i = 0;
    uint8_t is_negative = 0;

    // ����У��
   

    // ������������ʮ���ƣ�
    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }

    // ����0���������
    if (num == 0) {
        USART2_SendChar('0');
        return;
    }

    // ����ת�ַ�������洢��
    while (num > 0) {
        uint32_t rem = num % base;
        buffer[i++] = (rem < 10) ? (rem + '0') : (rem - 10 + 'A');
        num /= base;
    }

    // ��Ӹ���
    if (is_negative) {
        buffer[i++] = '-';
    }

    // �������ַ�
    while (i > 0) {
        USART2_SendChar(buffer[--i]);
    }
}

