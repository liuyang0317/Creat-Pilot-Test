#include "stm32f10x.h"
void Gpio_User_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;          //LED
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;   
  GPIO_Init(GPIOE, &GPIO_InitStructure);  



  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //PA15= spi3_cs    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);  //PE2= LED 
     
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);	        
        
        
/*
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;     //IIC¿ÚÏß
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
*/
}
