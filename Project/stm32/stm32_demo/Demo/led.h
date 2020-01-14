
#ifndef _LED_H_
#define _LED_H_


//------------------------
//		宏定义
#define LED_OFF()		GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define LED_ON()		GPIO_ResetBits(GPIOB,GPIO_Pin_8)

#define LED2_OFF()		GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define LED2_ON()		GPIO_ResetBits(GPIOB,GPIO_Pin_9)


//------------------------
//		函数声明
void LED_Init(void);


#endif
