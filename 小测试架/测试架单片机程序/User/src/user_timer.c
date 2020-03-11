#include "stm32f10x.h"
void Timer_User_Init(void)
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef  NVIC_InitStructure; 

	/**tim3**/ 

	TIM_DeInit(TIM3);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		//��ʱ��3ʱ�ӿ���
	TIM_TimeBaseStructure.TIM_Period=128; //�Զ���װ�ؼĴ�����ֵ  1999
	TIM_TimeBaseStructure.TIM_Prescaler= 65536-1; //Ԥ��Ƶ�� 128Hz	 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//������ʽ 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
	TIM_ClearFlag(TIM3, TIM_FLAG_Update); //�������жϱ�־
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE); //����ʱ��	   ENABLE	    DISABLE


	/*nvic*/ 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //ͨ��TIM3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
}
