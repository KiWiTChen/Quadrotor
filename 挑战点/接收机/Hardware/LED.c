#include "LED.h"



void LED_Config(void){
	RCC->AHB1ENR |= 1;
  
	GPIOA->MODER &=~ (3ul<<10);
	GPIOA->MODER |= (1ul<<10);
	GPIOA->OTYPER &=~ (1ul<< 5);	
  GPIOA->OSPEEDR |=  ((1ul << 10));
	

}

void LED_On (void) {

   GPIOA->ODR |= 1<<5;
}

void LED_Off (void) {
      
   GPIOA->ODR |= 0<<5;
 
}

