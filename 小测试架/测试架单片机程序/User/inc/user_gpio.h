#ifndef __USER_GPIO_H
#define __USER_GPIO_H

//#define LED_On()  GPIO_ResetBits(GPIOA,GPIO_Pin_2)
//#define LED_Off() GPIO_SetBits(GPIOA,GPIO_Pin_2)
  
#define BUZZER_On()  GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define BUZZER_Off() GPIO_ResetBits(GPIOA,GPIO_Pin_1)

#define SM72442_On()  GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define SM72442_Off() GPIO_ResetBits(GPIOC,GPIO_Pin_13)

void Gpio_User_Init(void);
#endif
