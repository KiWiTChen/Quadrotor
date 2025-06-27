#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"


//struct RC{
//	uint16_t ROLL;
//	uint16_t PITCH;
//	uint16_t THROTTLE;
//	uint16_t YAW;
//	uint16_t AUX1;
//	uint16_t AUX2;
//	uint16_t AUX3;
//	uint16_t AUX4;
//};
//struct RC Rc;

void PPM_Init(){
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //开启GOIOA通道
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   //开启时钟
	
	//初始化GPIOA
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;   //复用模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
	
	//初始化时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler = 84 -1;                //分频系数，选用系统时钟频率为84MHZ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数方式，向上计数
	TIM_TimeBaseStructure.TIM_Period = 65536 -1;                //时段ARR
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //时钟分频系数
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
  
	//初始化输入捕获通道
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;            //捕获通道
	TIM_ICInitStructure.TIM_ICFilter = 0xF;                    //滤波值，选最大
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //向上捕获
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       //不分频
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //捕获映射，直接映射
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
  //选择捕获事件源
	TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);     //选择中断源捕获，映射到TI2FP2
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);  //从模式选择复位模式
	
	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);          //中断源捕获事件2使能
	
	TIM_Cmd(TIM2,ENABLE);
	
	//初始化中断
  NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;           //中断源选择TIM2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;         //从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
