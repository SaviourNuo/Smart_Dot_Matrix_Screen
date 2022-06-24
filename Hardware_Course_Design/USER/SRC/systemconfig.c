
#include  <stm32f10x.h>
#include "systemconfig.h"
#include "common.h"

/*******************************************************************************
* 函数名称       : RCC_Configuration
* 功能描述       : 配置外设时钟.
* 入口参数       : 无
* 出口参数       : 无
*******************************************************************************/
void RCC_Configuration(void)
{
 

	//使能GPIO时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE); 

	//使能复用功能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	//延时初始化
	Delay_Init(); 
					 
}

/*******************************************************************************
* 函数名称       : GPIO_Configuration
* 功能描述       : 配置项目中所有用到的GPIO
* 入口参数       : 无
* 出口参数       : 无
*******************************************************************************/

void Init_ADF435x_Gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//使能SWJ，禁止 JTAG

 	GPIO_InitStructure.GPIO_Pin =0XFFFF; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = 0xFFFF; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;;		 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;;		  
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	PWR_BackupAccessCmd(ENABLE);
  RCC_LSEConfig(RCC_LSE_OFF);
  PWR_BackupAccessCmd(DISABLE);

	//PWR->CR |= 1<<8;//取消备份区写保护
  //RCC->BDCR &= 0xFFFFFFFE; //关闭外部低速振荡器，PC14，PC15成为普通IO  
  //BKP->CR &= 0xFFFFFFFE; //侵入检测TAMPER引脚(PC13)作为通用IO口使用
  //PWR->CR &= 0xFFFFFEFF; //备份区写保护
}



void SystemConfiguration(void)
{	
	RCC_Configuration(); 

  Delay_ms(100);
  Init_ADF435x_Gpio();
 
}



