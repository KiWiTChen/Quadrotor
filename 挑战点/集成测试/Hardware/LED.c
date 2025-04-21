#include "LED.h"



int32_t LED_Config(void){
	RCC->AHB1ENR |= (1ul);
  
	GPIOA->MODER &=~ (3ul<<10);
	GPIOA->MODER |= (1ul<<10);
	GPIOA->OTYPER &=~ (1ul<< 5);	
  GPIOA->OSPEEDR |=  ((1ul << 10));

	return (0);
	

}

void LED_On (void) {

    GPIO_SetBits(GPIOA, GPIO_Pin_5);
}

void LED_Off (void) {
      
   GPIO_ResetBits(GPIOA, GPIO_Pin_5);
 
}

