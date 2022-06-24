
#include  <stm32f10x.h>
#include "systemconfig.h"
#include "common.h"

/*******************************************************************************
* ��������       : RCC_Configuration
* ��������       : ��������ʱ��.
* ��ڲ���       : ��
* ���ڲ���       : ��
*******************************************************************************/
void RCC_Configuration(void)
{
 

	//ʹ��GPIOʱ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE); 

	//ʹ�ܸ��ù���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	//��ʱ��ʼ��
	Delay_Init(); 
					 
}

/*******************************************************************************
* ��������       : GPIO_Configuration
* ��������       : ������Ŀ�������õ���GPIO
* ��ڲ���       : ��
* ���ڲ���       : ��
*******************************************************************************/

void Init_ADF435x_Gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//ʹ��SWJ����ֹ JTAG

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

	//PWR->CR |= 1<<8;//ȡ��������д����
  //RCC->BDCR &= 0xFFFFFFFE; //�ر��ⲿ����������PC14��PC15��Ϊ��ͨIO  
  //BKP->CR &= 0xFFFFFFFE; //������TAMPER����(PC13)��Ϊͨ��IO��ʹ��
  //PWR->CR &= 0xFFFFFEFF; //������д����
}



void SystemConfiguration(void)
{	
	RCC_Configuration(); 

  Delay_ms(100);
  Init_ADF435x_Gpio();
 
}



