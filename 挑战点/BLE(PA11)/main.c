#include "ATKBLE01.h"
#include "OLED.h"
#include "stm32f4xx_rcc.h"
//�޸ķ�Ƶʱ�Ӻ���������ԣ�����λ����stm32f4xx.h system_stm32f4xx.c,����������9600

int main(void){
	
	

    
	OLED_Init();
	BLE_Init();
	while(1){
		BLE_SendNumber(2025,4);
		
		RCC_ClocksTypeDef RCC_Clocks;

    // ��ȡ��ǰʱ������
    RCC_GetClocksFreq(&RCC_Clocks);
		// ��ӡʱ��Ƶ����Ϣ (����ͨ���������)
   OLED_ShowNum(1,1 ,RCC_Clocks.HCLK_Frequency,10);
   OLED_ShowNum(2,1, RCC_Clocks.SYSCLK_Frequency,10);
   OLED_ShowNum(3,1,RCC_Clocks.PCLK1_Frequency,10);
   OLED_ShowNum(4,1 ,RCC_Clocks.PCLK2_Frequency,10);
	}
}

