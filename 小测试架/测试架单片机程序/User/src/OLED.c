/************************************************************************************
*  Copyright (c), 2014, HelTec Automatic Technology co.,LTD.
*            All rights reserved.
*
* Http:    www.heltec.cn
* Email:   cn.heltec@gmail.com
* WebShop: heltec.taobao.com
*
* File name: OLED.c
* Project  : HelTec.uvprij
* Processor: STM32F103C8T6
* Compiler : MDK fo ARM
* 
* Author : 小林
* Version: 1.00
* Date   : 2014.2.20
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64点阵的OLED显示屏驱动文件，仅适用于惠特自动化(heltec.taobao.com)的SD1306驱动SPI通信方式显示屏
*
* Others: none;
*
* Function List:
*
* 2. void OLED_WrDat(unsigned char dat) -- 向OLED写数据
* 3. void OLED_WrCmd(unsigned char cmd) -- 向OLED写命令
* 4. void OLED_SetPos(unsigned char x, unsigned char y) -- 设置起始点坐标
* 5. void OLED_Fill(unsigned char bmp_dat) -- 全屏填充(0x00可以用于清屏，0xff可以用于全屏点亮)
* 6. void OLED_CLS(void) -- 清屏
* 7. void OLED_Init(void) -- OLED显示屏初始化
* 8. void OLED_6x8Str(unsigned char x, y,unsigned char ch[]) -- 显示6x8的ASCII字符
* 9. void OLED_8x16Str(unsigned char x, y,unsigned char ch[]) -- 显示8x16的ASCII字符
* 10.void OLED_16x16CN(unsigned char x, y, N) -- 显示16x16中文汉字,汉字要先在取模软件中取模
* 11.void OLED_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- 全屏显示128*64的BMP图片
*
* History: none;
*
*************************************************************************************/

#include "stm32f10x.h"
#include"user_config.h"
//#include "codetab.h"
unsigned char j =0;
unsigned char k =0;
unsigned char v =0;
void LCD12864_CS(unsigned char cs)
{
  if(cs == 1)
  {
    GPIO_SetBits(GPIOA,GPIO_Pin_15);
  }
  if(cs == 0)
  {
    GPIO_ResetBits(GPIOA,GPIO_Pin_15);
  }
}
void OLED_WrDat(unsigned char dat)//写数据
{
  unsigned char Hdat = dat & 0xf0;
  unsigned char Ldat = dat & 0x0f;
  SPI_Writebyte(0xfa);        
  SPI_Writebyte(Hdat);
  SPI_Writebyte(Ldat);        
}

void OLED_WrCmd(unsigned char cmd)//写命令
{
  unsigned char Hcmd = cmd & 0xf0;
  unsigned char Lcmd = cmd & 0x0f;
  SPI_Writebyte(0xf8);        
  SPI_Writebyte(Hcmd);
  SPI_Writebyte(Lcmd);        
}
void OLED_Init(void)
{
  LCD12864_CS(0);  //片选永久打开
  delay1ms(100);
  OLED_WrCmd(0x03);//功能设定，使用基本指令集
  OLED_WrCmd(0x0c);//整体显示，游标off，游标位置off
  OLED_WrCmd(0x01);//清DDRAM
  OLED_WrCmd(0x02);//DDRAM地址归位
  OLED_WrCmd(0x80);//设定DDRAM 7位地址000，0000到地址计数器AC
  OLED_WrCmd(0x04);//点设定，显示字符/光标从左到右移位，DDRAM地址加 一
  OLED_WrCmd(0x0F);//显示设定，开显示，显示光标，当前显示位反白闪动
}

void OLED_Display(unsigned char x_add,unsigned char *str) //在指定位置显示半字字符串
{
  OLED_WrCmd(x_add);//1xxx,xxxx 设定DDRAM 7位地址xxx,xxxx到地址计数器AC
  while(*str != '\0')
  {
    OLED_WrDat(*str);
    str++;
  }
}





/*
void OLED_SetPos(unsigned char x, unsigned char y)//设置起始点坐标
{
	OLED_WrCmd(0xb0 + y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd(x&0x0f);
}

void OLED_Fill(unsigned char bmp_dat)//全屏填充
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x00);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		{
			OLED_WrDat(bmp_dat);
		}
	}
}

void OLED_CLS(void)//清屏
{
	OLED_Fill(0x00);
}

void OLED_START(void)//OLED 启动
{
	OLED_RES_Clr();  //RES拉低
	for(j=0;j<100;j++)
	{}
	OLED_RES_Set();	 //RES拉高
	for(j=0;j<100;j++)
	{}	
}


void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c = ch[j]-32;
		if(x>126)
		{
			x=0;y++;
		}
		OLED_SetPos(x,y);
		for(i=0;i<6;i++)
		{
			OLED_WrDat(F6x8[c][i]);
		}
		x+=6;
		j++;
	}
}

void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120)
		{
			x=0;y++;
		}
		OLED_SetPos(x,y);
		for(i=0;i<8;i++)
		{
			OLED_WrDat(F8X16[c*16+i]);
		}
		OLED_SetPos(x,y+1);
		for(i=0;i<8;i++)
		{
			OLED_WrDat(F8X16[c*16+i+8]);
		}
		x+=8;
		j++;
	}
}

void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
}

void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;
	
  if(y1%8==0)
	{
		y=y1/8;
	}
  else
		y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			OLED_WrDat(BMP[j++]);
		}
	}
}
*/