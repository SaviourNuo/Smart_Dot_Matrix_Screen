#ifndef __SYSTEMCONFIG_H
#define __SYSTEMCONFIG_H
#include "stm32f10x.h"
#include "bitband.h"
void RCC_Configuration(void);

void GPIO_Configuration(void);

void NVIC_Configuration(void);

void SystemConfiguration(void);

 

void Delay_ms(u16 ms);

void Delay_Init(void);


//-----------------OLED端口定义----------------  					   
//#define OLED_SCLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_2)
//#define OLED_SCLK_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define OLED_SCLK_Clr()  GPIOB->BRR = GPIO_Pin_0
#define OLED_SCLK_Set()  GPIOB->BSRR= GPIO_Pin_0 

//#define OLED_SDIN_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_1)
//#define OLED_SDIN_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define OLED_SDIN_Clr()  GPIOB->BRR = GPIO_Pin_1
#define OLED_SDIN_Set()  GPIOB->BSRR= GPIO_Pin_1 

#define OLED_RST_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_2)
#define OLED_RST_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_2)

//#define OLED_DC_Clr()   GPIO_ResetBits(GPIOB,GPIO_Pin_10)
//#define OLED_DC_Set()   GPIO_SetBits(GPIOB,GPIO_Pin_10)

#define OLED_DC_Clr()  GPIOB->BRR=GPIO_Pin_3
#define OLED_DC_Set()  GPIOB->BSRR=GPIO_Pin_3 
 		     
#define OLED_BLK_Clr()   GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define OLED_BLK_Set()   GPIO_SetBits(GPIOB,GPIO_Pin_5)



#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

 

#define SET_KY1			GPIO_SetBits(GPIOB,GPIO_Pin_12)					//Y3拉高
#define RST_KY1			GPIO_ResetBits(GPIOB,GPIO_Pin_12)					//Y3拉低
#define SET_KY2			GPIO_SetBits(GPIOB,GPIO_Pin_13)					//Y3拉高
#define RST_KY2			GPIO_ResetBits(GPIOB,GPIO_Pin_13)					//Y3拉低
#define SET_KY3			GPIO_SetBits(GPIOB,GPIO_Pin_14)					//Y2拉高
#define RST_KY3			GPIO_ResetBits(GPIOB,GPIO_Pin_14)						//Y2拉低
#define SET_KY4		  GPIO_SetBits(GPIOB,GPIO_Pin_15)						//Y1拉高
#define RST_KY4			GPIO_ResetBits(GPIOB,GPIO_Pin_15)						//Y1拉低

#define KX1_STATUS	 	BIT_ADDR(GPIOB_IDR_Addr,8)							//X4状态
#define KX2_STATUS	 	BIT_ADDR(GPIOB_IDR_Addr,9)							//X3状态
#define KX3_STATUS	 	BIT_ADDR(GPIOB_IDR_Addr,10)							//X2状态
#define KX4_STATUS	 	BIT_ADDR(GPIOB_IDR_Addr,11)	

#define MHZ	 	BIT_ADDR(GPIOC_IDR_Addr,13)							//X4状态
#define KHZ	 	BIT_ADDR(GPIOC_IDR_Addr,14)							//X3状态
#define HZ	 	BIT_ADDR(GPIOC_IDR_Addr,15)							//X2状态

#endif

