#include "stm32f10x.h"
#include "user_config.h"
void User_Init(void)
{
	Rcc_User_Init();
	Gpio_User_Init();
	Spi_User_Init();
	Timer_User_Init();
	OLED_Init();
}
void delay1s(unsigned char t)
{
  unsigned char i;
  unsigned int j;
  for(i=0;i<t;i++)
  {
    for(j=0;j<65535;j++)
    {}
  }
}
void delay1ms(unsigned char t)
{
  unsigned char i;
  unsigned int j;
  for(i=0;i<t;i++)
  {
    for(j=0;j<65535;j++)
    {}
  }
}

void LED_On(void)
{
  GPIO_ResetBits(GPIOE,GPIO_Pin_2);
}
void LED_Off(void)
{
  GPIO_SetBits(GPIOE,GPIO_Pin_2);
}