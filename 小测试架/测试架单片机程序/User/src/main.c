#include "stm32f10x.h"
#include "user_config.h"
uint8_t temp[8];

int main(void)
{
	User_Init();

//   I2C_ReadSevenByte(0x02,0xe2);
/*
	temp[1] = 0x11;
	temp[2] = 0x12;
	temp[3] = 0x13;
	temp[4] = 0x14;
	temp[5] = 0x15;
	temp[6] = 0x16;
	temp[7] = 0x17;	
	 */


//	temp[2] = 0x1f;	  //最小死区时间	//data2 = 0x1f data3 = 0xf0
//	temp[3] = 0xf0;	  //最小死区时间	//data2 = 0x1f data3 = 0xf0
//	temp[3] = 0xff;	  //最大死区时间    //data3 = 0xff 
//	I2C_WriteSevenByte(0x02,0xe3);
//	I2C_ReadSevenByte(0x02,0xe3);	


  while (1)
  {
	/*
        OLED_8x16Str(10,0,"oh dear!");
 	OLED_8x16Str(0,3,"let us fuck the");
	OLED_8x16Str(0,6,"life inside out.");
*/
  }
}

void TIM3_IRQHandler(void)
{ 

	static u8 sign = 1; 
	if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) == SET)
	{ 
		TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update); 
		if(sign) 
		{  
			sign = 0; 

		} 
		else 
		{  
			sign = 1;  

		} 
	} 

/* 		
	static u8 sign = 0;

		if(sign == 0)
		{
			GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_RESET);	//LED
			GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);//BUZZER
			//GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);//sm72442 reset管脚
			sign =1;	
		}
*/
} 
