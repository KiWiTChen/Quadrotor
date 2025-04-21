#include "stm32f4xx.h"                  // Device header
#include "Delay.h"

void MyIIC_Init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = 	GPIO_OType_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9);
}

//封装发送字节，8比特
void MyIIC_W_SCL(int BitValue){
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, BitValue);
	Delay_us(10);
}

void MyIIC_W_SDA(int BitValue){
	GPIO_WriteBit(GPIOB, GPIO_Pin_9, BitValue);
	Delay_us(10);
}

uint8_t MyIIC_R_SCL(){
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8);
	Delay_us(10);
	return BitValue;
}


uint8_t MyIIC_R_SDA(){
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
	Delay_us(10);
	return BitValue;
}

void MyIIC_Start(void){
	MyIIC_W_SDA(1);
	MyIIC_W_SCL(1);
	MyIIC_W_SDA(0);
	MyIIC_W_SCL(0);
}

void MyIIC_Stop(void){
	MyIIC_W_SDA(0);
	MyIIC_W_SCL(1);
	MyIIC_W_SDA(1);

}
	
void MyIIC_SendByte(uint8_t Byte){
	for(uint8_t i = 0; i< 8; i++){
		MyIIC_W_SDA(Byte & (0x80 >> i));
		MyIIC_W_SCL(1);
		MyIIC_W_SCL(0);
		
	}
	
}

uint8_t MyIIC_ReceiveByte(){
	uint8_t Byte = 0x00;
	MyIIC_W_SDA(1);
	for(uint8_t i = 0; i< 8; i++){
		MyIIC_W_SCL(1);
		if(MyIIC_R_SDA() ==1){
			Byte |= (0x80 >> i);
		}
		MyIIC_W_SCL(0);
	}
	return Byte;
	
}

void MyIIC_SendACK(uint8_t AckBit){
	MyIIC_W_SDA(AckBit);
	MyIIC_W_SCL(1);
	MyIIC_W_SCL(0);
	
}

uint8_t MyIIC_ReceiveACK(){
	uint8_t AckBit;
  MyIIC_W_SDA(1);
	MyIIC_W_SCL(1);
	AckBit = MyIIC_R_SDA();
	MyIIC_W_SCL(0);
	
	return AckBit;
	
}


