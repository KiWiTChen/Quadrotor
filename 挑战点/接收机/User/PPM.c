#include "stm32f4xx.h"                  // Device header

uint8_t Rc_channel = 1; 
uint16_t Rc_Val[9];

struct RC{
	uint16_t ROLL;
	uint16_t PITCH;
	uint16_t THROTTLE;
	uint16_t YAW;
	uint16_t AUX1;
	uint16_t AUX2;
	uint16_t AUX3;
	uint16_t AUX4;
};
struct RC Rc;

void PPM_Init(){
	

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM5_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef TIM5_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	
	TIM5_TimeBaseInitStructure.TIM_ClockDivision=0; //设定时钟分割，为0
	TIM5_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//设定计数模式：向上计数
	TIM5_TimeBaseInitStructure.TIM_Period = 65536-1;    //定时器计数自动重装，ACC值
	TIM5_TimeBaseInitStructure.TIM_Prescaler = 84-1; //预分频器
	TIM_TimeBaseInit(TIM5, &TIM5_TimeBaseInitStructure);
  
  
  TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2; //选择捕获通道
	TIM5_ICInitStructure.TIM_ICFilter = 0x0a;    //配置输入滤波器，选择不滤波
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //选择上升沿捕获
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//配置预分频器
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射选择TI2
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM5, TIM_TS_TI2FP2);
	TIM_SelectSlaveMode(TIM5, TIM_SlaveMode_Reset);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; //选择中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          //选择中断使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //从占优先级0级
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM5, TIM_IT_Update|TIM_IT_CC2, ENABLE); //允许更新中断，允许CC2捕获中断
	
	TIM_Cmd(TIM5, ENABLE);
	
		
}

//中断函数
//void TIM5_IRQHandler(){
//	 	if((Capture_Flag&0X80)==0)//还未成功捕获	
//	{	  
//		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)		 
//		{	    
//			if(Capture_Flag&0X40)//已经捕获到高电平了
//			{
//				if((Capture_Flag&0X3F)==0X3F)//高电平太长了
//				{
//					Capture_Flag|=0X80;//标记成功捕获了一次
//					Capture_val=0XFFFF;
//				}else Capture_Flag++;
//			}	 
//		}
//	if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)//捕获1发生捕获事件
//		{	
//			if(Capture_Flag&0X40)		//捕获到一个下降沿 		
//			{	  			
//				Capture_Flag|=0X80;		//标记成功捕获到一次上升沿
//				Capture_val=TIM_GetCapture2(TIM5);
//		   	TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC2P=0 设置为上升沿捕获
//			}else  								//还未开始,第一次捕获上升沿
//			{
//				Capture_Flag=0;			//清空
//				Capture_val=0;
//	 			TIM_SetCounter(TIM5,0);
//				Capture_Flag|=0X40;		//标记捕获到了上升沿
//		   	TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC2P=1 设置为下降沿捕获
//			}		    
//		}			     	    					   
// 	}
// 
//    TIM_ClearITPendingBit(TIM5, TIM_IT_CC2|TIM_IT_Update); //清除中断标志位
//
//}

