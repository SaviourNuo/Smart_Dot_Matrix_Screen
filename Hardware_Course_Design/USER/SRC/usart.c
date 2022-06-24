#include "sys.h"
#include "usart.h"	  
#include "oled.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

//FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
//void _sys_exit(int x) 
//{ 
//	x = x; 
//} 
//�ض���fputc���� 
//int fputc(int ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void uart_init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ���Լ����ù���ʱ��
     //USART1_TX   PA.9  ������RXD���Ӱ��ӵ�TXD
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10  ������TXD���Ӱ��ӵ�RXD
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 

}
//USART_RX_STA�ǽ���״̬��־��bit0-13���ڼ�������ʾ�յ��˼������ݣ�bit14Ϊ0x0d��־λ��bit15Ϊ������ɱ�־λ
//(���յ������ݱ�����0x0d 0x0a��β������ǹ̶��Ļس�����)
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����жϣ��жϴ����Ƿ���յ�����
	{
	
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//Res���ڶ�ȡ���յ�����������
		if((USART_RX_STA&0x8000)==0)//����״̬��־�����λҲ��bit15Ϊ1ʱ��ʾ����������ϣ��������δ���
		{//����ȡ���λ�ж�Ϊ0ʱ˵�����ջ�δ���
			if(USART_RX_STA&0x4000)//bit14Ϊ0x0d�Ľ��ձ�־λ��Ϊ1ʱ��ʾ���յ���0x0d����ʱ��0x4000���뼴ȡ��bit14�����жϣ�����׼������0x0a״̬
			{
				if(Res!=0x0a)USART_RX_STA=0;//���ڽ��յ�0x0d�����һ���ֽڲ���0x0a������մ���,��USART_RX_STA�������¿�ʼ
				else
				{
					USART_RX_STA|=0x8000;	//��0x0d��0x0a���������գ��������ɣ�����߱�־λ��1������λ����
                   
					return;
				}
			}
			else //������δ�����δ���յ�0X0dʱ
			{	
				if(Res==0x0d)//��ʱ�������յ�������Ϊ0x0d������н�����ɵ�׼������bit14��Ϊ1������λ����
					USART_RX_STA|=0x4000;
				else//֮ǰû���յ�0x0d��current����������Ҳ���ǣ��Ǿͼ������գ�˵��û�С��س���־��
				{
					//USART_RX_BUF[USART_RX_STA&0X3FFF]=Res;
					LCD_WRChinese(USART_RX_STA&0XFF, Res);
					USART_RX_STA++;//�����жϽ��յ�һ���ֽں��ÿ������1
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ɽ��յ���������������¿�ʼ���� 
				}		 
			}
		}   		 
    } 
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntExit();  											 
#endif
} 
#endif	
/*��������һ�����ʣ�����������������͵ľ���0x0d����0x0a����������Ч����Ӧ����δ��������������Ͽ�֪��ascii����0x0d��0x0aǰ�߱�ʾ�س�\r�����߱�ʾ����\n��
ע��س�ֻ�ǰѹ���ƶ������е���λ�ã�����ֻ�ǽ�����ƶ�����һ�ж��в��䣬ƽ��ϰ�ߵġ��س������൱�ڶ��ߵ���ϣ�����������У�Ŀǰ������ģ��0x0d��0x0a��������
������֣����Ŀǰ�����յ�������0x0d����ϣ��������ʾ0x0d,0x0a����������ʱ�����Ŀǰ���뵽�ķ����Ǹɴ�Ͱ�0x0d��0x0a��һ�������õ����ַ�������*/

