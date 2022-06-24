#include "stm32f10x.h"
#include "stdio.h"
#include "common.h"

static u8  fac_us=0; //us延时倍乘数
static u16 fac_ms=0; //ms延时倍乘数


/*******************************************************************************
* 函数名称       :  
* 功能描述       : Printf支持代码   printf("变量a的值是: %d\r\n\r\n",a);
* 入口参数       : 无
* 出口参数       : 无
*******************************************************************************/
#if 1
#pragma import(__use_no_semihosting)             
                
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
 
void _sys_exit(int x) //定义_sys_exit()以避免使用半主机模式   
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)//重定义fputc函数 
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif 

/*******************************************************************************
* 函数名称       : Delay_Init
* 功能描述       : 延时初始化函数
* 入口参数       : 无
* 出口参数       : 无
*******************************************************************************/
void Delay_Init(void)
{
	SysTick->CTRL&=0xfffffffb;//bit2清空,选择外部时钟  HCLK/8
	fac_us=9;		    
	fac_ms=(u16)fac_us*1000;
}								    

/*******************************************************************************
* 函数名称       : DelayMs
* 功能描述       : 延时函数，72M条件下ms<=1864
* 入口参数       : ms 延时大小
* 出口参数       : 无
*******************************************************************************/
void Delay_ms(u16 ms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)ms*fac_ms; //时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;            //清空计数器
	SysTick->CTRL=0x01 ;           //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); //等待时间到达   
	SysTick->CTRL=0x00;                //关闭计数器
	SysTick->VAL =0X00;                //清空计数器	  	    
}   

/*******************************************************************************
* 函数名称       : DelayUs
* 功能描述       : 延时函数，72M条件下ms<=1864000
* 入口参数       : us 延时大小
* 出口参数       : 无
*******************************************************************************/
void Delay_us(u32 us)
{		
	u32 temp;	    	 
	SysTick->LOAD=us*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); //等待时间到达   
	SysTick->CTRL=0x00;                //关闭计数器
	SysTick->VAL =0X00;                //清空计数器	 
}

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

void Init_Gpio(void)
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

	//PWR->CR |= 1<<8;//取消备份区写保护
  //RCC->BDCR &= 0xFFFFFFFE; //关闭外部低速振荡器，PC14，PC15成为普通IO  
  //BKP->CR &= 0xFFFFFFFE; //侵入检测TAMPER引脚(PC13)作为通用IO口使用
  //PWR->CR &= 0xFFFFFEFF; //备份区写保护
}



void SystemConfiguration(void)
{	
	RCC_Configuration(); 

 
  Init_Gpio();
 
}
 
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

  TIM_Cmd(TIM3, DISABLE);  //使能TIMx		
	//TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}


