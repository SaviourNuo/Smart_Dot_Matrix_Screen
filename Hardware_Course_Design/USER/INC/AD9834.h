#ifndef __AD9834_H
#define __AD9834_H
#include "stm32f10x.h"
#include "bitband.h"

#define  ad9834_data	  BIT_ADDR(GPIOB_ODR_Addr,11)  
#define  ad9834_clk     BIT_ADDR(GPIOB_ODR_Addr,10)  
#define  ad9834_sync	  BIT_ADDR(GPIOB_ODR_Addr,9) 
#define  ad9834_sleep	  BIT_ADDR(GPIOB_ODR_Addr,8) 

#define  ad9834_fsel	  BIT_ADDR(GPIOC_ODR_Addr,13)
#define  ad9834_psel	  BIT_ADDR(GPIOC_ODR_Addr,14)
#define  ad9834_RESET	  BIT_ADDR(GPIOC_ODR_Addr,15)
void	ad9834_start(void);
void  ad9834_Write(u16 cfword);
 
void  ad9834_contrlreg(void);
void  ad9834_datain(double freq, double phase);
void  ad9834_reset(void);
#endif
