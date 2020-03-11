#include "stm32f10x.h"
#include "user_config.h"
void Spi_User_Init(void)
{
  Spi_Io_User_Config();
  Spi_Reg_User_Config();
}
void SPI_Writebyte(unsigned char data)
{
  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET)
  {	
  }
  SPI_I2S_SendData(SPI3, data); 
}
void Spi_Io_User_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////     SPI����   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12;  //SCK and MOSI �ο��ֲ� 167ҳ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
  GPIO_Init(GPIOC, &GPIO_InitStructure);  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;                 //NSS �ο��ֲ� 160ҳ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                 //MISO �ο��ֲ� 167ҳ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //����AFIOʱ��  reference manual   187ҳ
  GPIO_PinRemapConfig(GPIO_Remap_SPI3 , ENABLE); //��ӳ��spi3��  reference manual   181ҳ
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //��ӳ����Կ� ֻ����SW���Թ���184ҳ  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,DISABLE);  //��ֹAFIOʱ�ӣ��Խ��͹���
}
void Spi_Reg_User_Config(void)
{
  SPI_InitTypeDef  SPI_InitStructure;	 
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;           //���߷��Ͱ�˫��  
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //��spi   
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   //spi����8λ֡�ṹ 
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                         //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                        //�ڶ������������ݱ��ɼ�
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //nss�ź����������
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;  //APB2= 1MHz spiʱ��=64k
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //���ݴ����MSB��ʼ 
  SPI_InitStructure.SPI_CRCPolynomial = 0;  //CRC�������ʽ  
  SPI_Init(SPI3, &SPI_InitStructure);  //���ݲ����趨SPI3�Ĵ���  
  SPI_Cmd(SPI3, ENABLE); //ʹ��spi3ͨ��     
}