#include "stm32f10x.h"
void Rcc_User_Init(void)
{	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  rcc_configration
  ErrorStatus  HSEStartUpStatus;
  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_ON);
  HSEStartUpStatus = RCC_WaitForHSEStartUp();	
  if(HSEStartUpStatus == SUCCESS)        //SUCCESS��HSE�����ȶ��Ҿ���
  {        
     //////////////////////////////////////////////////////////////////////////////     system clk config    
      RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);          //datasheet 101ҳ
      RCC_PLL2Config(RCC_PLL2Mul_8);                               //datasheet 101ҳ
      RCC_PLL3Config(RCC_PLL3Mul_10);                              //datasheet 101ҳ
      
      RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2,RCC_PREDIV1_Div5);  //datasheet 101ҳ
      RCC_PREDIV2Config(RCC_PREDIV2_Div5);                         //datasheet 101ҳ
     
      RCC_PLLCmd(ENABLE);                                          //1�����໷����          
      RCC_PLL2Cmd(ENABLE);                                         //2�����໷����    
      RCC_PLL3Cmd(ENABLE);                                         //3�����໷����  ����ʱ��
      while (RCC_GetFlagStatus(RCC_FLAG_PLL3RDY) == RESET)
      {}
      /* Get PLL3 clock on PA8 pin (MCO) */
      RCC_MCOConfig(RCC_MCO_PLL3CLK);
    ///////////////////////////////////////////////////////////////////////////////          
  }
  ///////////////////////////////////////////////////////////////////////////////   AHB and APB config
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);                      //reference manual   126ҳ   HSI = 8MHz
  RCC_HCLKConfig(RCC_SYSCLK_Div8);                             //reference manual   126ҳ   HCLK = 1MHz
  RCC_PCLK1Config(RCC_HCLK_Div1);                              //APB1ʱ��= HCLK             APB1 = APB2= 1MHz
  RCC_PCLK2Config(RCC_HCLK_Div1);                              //APB2ʱ��= HCLK
///////////////////////////////////////////////////////////////////////////////		
  while(RCC_GetSYSCLKSource() != 0x00)                        //0x00��HSI��Ϊϵͳʱ��
  {}  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  
  


}
