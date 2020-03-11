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
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////     SPI配置   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12;  //SCK and MOSI 参考手册 167页
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
  GPIO_Init(GPIOC, &GPIO_InitStructure);  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;                 //NSS 参考手册 160页
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                 //MISO 参考手册 167页
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //开启AFIO时钟  reference manual   187页
  GPIO_PinRemapConfig(GPIO_Remap_SPI3 , ENABLE); //重映射spi3口  reference manual   181页
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //重映射调试口 只保留SW调试功能184页  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,DISABLE);  //禁止AFIO时钟，以降低功耗
}
void Spi_Reg_User_Config(void)
{
  SPI_InitTypeDef  SPI_InitStructure;	 
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;           //单线发送半双工  
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //主spi   
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   //spi发送8位帧结构 
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                         //串行同步时钟的空闲状态为高电平
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                        //第二个跳变沿数据被采集
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //nss信号由软件控制
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;  //APB2= 1MHz spi时钟=64k
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //数据传输从MSB开始 
  SPI_InitStructure.SPI_CRCPolynomial = 0;  //CRC计算多项式  
  SPI_Init(SPI3, &SPI_InitStructure);  //根据参数设定SPI3寄存器  
  SPI_Cmd(SPI3, ENABLE); //使能spi3通信     
}