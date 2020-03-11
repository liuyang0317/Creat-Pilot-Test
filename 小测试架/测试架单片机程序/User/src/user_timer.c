#include "stm32f10x.h"
void Timer_User_Init(void)
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef  NVIC_InitStructure; 

	/**tim3**/ 

	TIM_DeInit(TIM3);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		//定时器3时钟开启
	TIM_TimeBaseStructure.TIM_Period=128; //自动重装载寄存器的值  1999
	TIM_TimeBaseStructure.TIM_Prescaler= 65536-1; //预分频数 128Hz	 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//计数方式 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
	TIM_ClearFlag(TIM3, TIM_FLAG_Update); //清除溢出中断标志
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE); //开启时钟	   ENABLE	    DISABLE


	/*nvic*/ 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //通道TIM3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //副优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
}
