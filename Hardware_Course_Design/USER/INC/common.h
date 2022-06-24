#ifndef __COMMON_H
#define __COMMON_H

#include "bitband.h"
 #include "stm32f10x.h"
 
void RCC_Configuration(void);

void GPIO_Configuration(void);

void NVIC_Configuration(void);

void SystemConfiguration(void);

 
void Delay_us(u32 us);
void Delay_ms(u16 ms);

void Delay_Init(void);



//-----------------OLED¶Ë¿Ú¶¨Òå----------------  					   
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



#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý

 
 
#define KX4_STATUS	 	BIT_ADDR(GPIOB_IDR_Addr,11)	

#define KEY1	 	BIT_ADDR(GPIOB_IDR_Addr,12)							//X4×´Ì¬
#define KEY2	 	BIT_ADDR(GPIOB_IDR_Addr,13)							//X3×´Ì¬
#define KEY3	 	BIT_ADDR(GPIOB_IDR_Addr,14)							//X2×´Ì¬
#define KEY4	 	BIT_ADDR(GPIOB_IDR_Addr,15)							//X2×´Ì¬



#endif




