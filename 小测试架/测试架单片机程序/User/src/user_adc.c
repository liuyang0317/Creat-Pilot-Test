#include "stm32f10x.h"
#include "user_config.h"
void Adc_User_Init(void)
{
  Adc_Io_User_Config();
  Adc_Reg_User_Config();
}
void Adc_Reg_User_Config(void)
{
  ADC_InitTypeDef ADC_InitStructure;

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//��˫adcģʽ��ʹ�ö���adcģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//�ǵ�ͨ��ģʽ
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ǵ��β���
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 4;//����ͨ��������
  ADC_Init(ADC1, &ADC_InitStructure);//����󲿷��ǳ�ʼ������ͨ����

  ADC_TempSensorVrefintCmd(ENABLE);
  ADC_RegularChannelConfig(ADC1,ADC_Channel_6,1,ADC_SampleTime_13Cycles5);    
  ADC_RegularChannelConfig(ADC1,ADC_Channel_7,2,ADC_SampleTime_13Cycles5);      
  ADC_RegularChannelConfig(ADC1,ADC_Channel_14,3,ADC_SampleTime_13Cycles5);     

  ADC_RegularChannelConfig(ADC1,ADC_Channel_TempSensor,4,ADC_SampleTime_13Cycles5);
  ADC_RegularChannelConfig(ADC1,ADC_Channel_Vrefint,5,ADC_SampleTime_13Cycles5);

  //ADC_InjectedSequencerLengthConfig(ADC1, 1);
  //ADC_InjectedChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_7Cycles5);
  //ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_None);//���ù���ͨ���������
  //Enable automatic injected conversion start after regular one 
  //ADC_AutoInjectedConvCmd(ADC1, ENABLE);


  ADC_DMACmd(ADC1, ENABLE);
  /* Enable ADC1 external trigger */
  //ADC_ExternalTrigConvCmd(ADC1, DISABLE);
  //ADC_ExternalTrigInjectedConvCmd(ADC1, DISABLE);

  ADC_Cmd(ADC1, ENABLE);

  ADC_ResetCalibration(ADC1);

  while(ADC_GetResetCalibrationStatus(ADC1));
  {
    ADC_StartCalibration(ADC1);     
  }
  while(ADC_GetCalibrationStatus(ADC1));
  {}
}
void Adc_Io_User_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//PA6 = �¶Ȳ���  PA7 = CT����  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	      //PC4 = PT����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}