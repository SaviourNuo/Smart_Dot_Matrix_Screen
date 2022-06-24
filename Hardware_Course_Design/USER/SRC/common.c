#include "stm32f10x.h"
#include "stdio.h"
#include "common.h"

static u8  fac_us=0; //us��ʱ������
static u16 fac_ms=0; //ms��ʱ������


/*******************************************************************************
* ��������       :  
* ��������       : Printf֧�ִ���   printf("����a��ֵ��: %d\r\n\r\n",a);
* ��ڲ���       : ��
* ���ڲ���       : ��
*******************************************************************************/
#if 1
#pragma import(__use_no_semihosting)             
                
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
 
void _sys_exit(int x) //����_sys_exit()�Ա���ʹ�ð�����ģʽ   
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)//�ض���fputc���� 
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif 

/*******************************************************************************
* ��������       : Delay_Init
* ��������       : ��ʱ��ʼ������
* ��ڲ���       : ��
* ���ڲ���       : ��
*******************************************************************************/
void Delay_Init(void)
{
	SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK/8
	fac_us=9;		    
	fac_ms=(u16)fac_us*1000;
}								    

/*******************************************************************************
* ��������       : DelayMs
* ��������       : ��ʱ������72M������ms<=1864
* ��ڲ���       : ms ��ʱ��С
* ���ڲ���       : ��
*******************************************************************************/
void Delay_ms(u16 ms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)ms*fac_ms; //ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;            //��ռ�����
	SysTick->CTRL=0x01 ;           //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); //�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;                //�رռ�����
	SysTick->VAL =0X00;                //��ռ�����	  	    
}   

/*******************************************************************************
* ��������       : DelayUs
* ��������       : ��ʱ������72M������ms<=1864000
* ��ڲ���       : us ��ʱ��С
* ���ڲ���       : ��
*******************************************************************************/
void Delay_us(u32 us)
{		
	u32 temp;	    	 
	SysTick->LOAD=us*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); //�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;                //�رռ�����
	SysTick->VAL =0X00;                //��ռ�����	 
}

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

void Init_Gpio(void)
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
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;  
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;;		 
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
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

 
  Init_Gpio();
 
}
 
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

  TIM_Cmd(TIM3, DISABLE);  //ʹ��TIMx		
	//TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}


