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
* Author : С��
* Version: 1.00
* Date   : 2014.2.20
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64�����OLED��ʾ�������ļ����������ڻ����Զ���(heltec.taobao.com)��SD1306����SPIͨ�ŷ�ʽ��ʾ��
*
* Others: none;
*
* Function List:
*
* 2. void OLED_WrDat(unsigned char dat) -- ��OLEDд����
* 3. void OLED_WrCmd(unsigned char cmd) -- ��OLEDд����
* 4. void OLED_SetPos(unsigned char x, unsigned char y) -- ������ʼ������
* 5. void OLED_Fill(unsigned char bmp_dat) -- ȫ�����(0x00��������������0xff��������ȫ������)
* 6. void OLED_CLS(void) -- ����
* 7. void OLED_Init(void) -- OLED��ʾ����ʼ��
* 8. void OLED_6x8Str(unsigned char x, y,unsigned char ch[]) -- ��ʾ6x8��ASCII�ַ�
* 9. void OLED_8x16Str(unsigned char x, y,unsigned char ch[]) -- ��ʾ8x16��ASCII�ַ�
* 10.void OLED_16x16CN(unsigned char x, y, N) -- ��ʾ16x16���ĺ���,����Ҫ����ȡģ�����ȡģ
* 11.void OLED_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- ȫ����ʾ128*64��BMPͼƬ
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
void OLED_WrDat(unsigned char dat)//д����
{
  unsigned char Hdat = dat & 0xf0;
  unsigned char Ldat = dat & 0x0f;
  SPI_Writebyte(0xfa);        
  SPI_Writebyte(Hdat);
  SPI_Writebyte(Ldat);        
}

void OLED_WrCmd(unsigned char cmd)//д����
{
  unsigned char Hcmd = cmd & 0xf0;
  unsigned char Lcmd = cmd & 0x0f;
  SPI_Writebyte(0xf8);        
  SPI_Writebyte(Hcmd);
  SPI_Writebyte(Lcmd);        
}
void OLED_Init(void)
{
  LCD12864_CS(0);  //Ƭѡ���ô�
  delay1ms(100);
  OLED_WrCmd(0x03);//�����趨��ʹ�û���ָ�
  OLED_WrCmd(0x0c);//������ʾ���α�off���α�λ��off
  OLED_WrCmd(0x01);//��DDRAM
  OLED_WrCmd(0x02);//DDRAM��ַ��λ
  OLED_WrCmd(0x80);//�趨DDRAM 7λ��ַ000��0000����ַ������AC
  OLED_WrCmd(0x04);//���趨����ʾ�ַ�/����������λ��DDRAM��ַ�� һ
  OLED_WrCmd(0x0F);//��ʾ�趨������ʾ����ʾ��꣬��ǰ��ʾλ��������
}

void OLED_Display(unsigned char x_add,unsigned char *str) //��ָ��λ����ʾ�����ַ���
{
  OLED_WrCmd(x_add);//1xxx,xxxx �趨DDRAM 7λ��ַxxx,xxxx����ַ������AC
  while(*str != '\0')
  {
    OLED_WrDat(*str);
    str++;
  }
}





/*
void OLED_SetPos(unsigned char x, unsigned char y)//������ʼ������
{
	OLED_WrCmd(0xb0 + y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd(x&0x0f);
}

void OLED_Fill(unsigned char bmp_dat)//ȫ�����
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

void OLED_CLS(void)//����
{
	OLED_Fill(0x00);
}

void OLED_START(void)//OLED ����
{
	OLED_RES_Clr();  //RES����
	for(j=0;j<100;j++)
	{}
	OLED_RES_Set();	 //RES����
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