#include "main.h"

int main(void)
{
	
	u8 len; //���������ַ����ĳ��ȣ�ȷ����Ļ��ʾ������
    
    SystemConfiguration();  //ϵͳ��ʼ��
    
    Lcd_Init();  //����LCD��ʼ������	
	LCD_Clear(BLACK,320,240); //���Ʊ�����ɫ����һ������Ϊ������ɫ������������Ϊ��ʼ���ĳߴ�
    OLED_BLK_Set(); //Ƭ��ʼ��
    
	extern u16 BACK_COLOR, POINT_COLOR;//����ɫ������ɫ
	BACK_COLOR=BLACK; 
	POINT_COLOR=RED;
    
    uart_init(9600); //���ڳ�ʼ��
    Delay_ms(100);

    
	while(1)
	{
		if(USART_RX_STA&0x8000)  //��USART_RX_STA�����λ��bit15Ϊ1ʱ����ʾ������ɣ�������ʾ�߼�������һֱ��ѭ��
		{
			len=(u8)(USART_RX_STA&0XFF);  
            /*USART_RX_STA�ĵ�bit0-bit13λΪ����λ���ж�һ�������˶��ٸ����ݣ���&0xFFʱ
            ��ʾ��bit0-bit7��������ȡ������Ҳ�����������ݸ���<=255���Բ���������룬lenΪ���յ����ݵĸ���*/
            
			USART_RX_STA=0;  //�����ձ�־��ʼ����׼��������һ���жϽ���
			LCD_ScrollDisplay(len);  //�����յ����ֵĸ�����Ϊ�������������ʽѡ����
            
		}
	}
}


//���������ʾ������������Ķ�ϰ�ߣ���˲�������ʽ����
///*5.������ʾ���ϵ����ƶ�����Ҫע����ǣ����ڶ�����ʾ����ʱ���ֲ������������ķ�ʽ����
//����޷�ֻ����showhanzi����Ҫ��ȷ�����ص㣬�������õͲ㺯��LCD_WR_DATA��д�߼������⣬�˺���
//ֻ������һ����ʾ�ĺ�����ռ�ݵ���Ļ���ظ߶�С��240��Ҳ��������70���֣���Ϊ�������·��ĺ��ֵ��°벿�ֻ���������Ļ���ϰ벿����ʾ
//������70���֣���ᵼ�����¸���*/
//        for(int y_start = 0;y_start<240;y_start+=4)
//        {//��ֱ�������ѭ����������ֱ������ÿ�������ƶ�4�����ص�  
//            for(int idx = 0;idx<STRING_LENGTH;idx++)
//            {// �Ժ��������ڵ������ַ��±�������              
//                        
//                uint8_t x_off = idx%DISPLAY_MAX_LENGTH; //ָʾ��ǰ��Ŀǰλ����Ҫ��ʾ�ĺ��֣�ȡ�������λ���ھ���λ��
//                uint8_t y_off = idx/DISPLAY_MAX_LENGTH; //ָʾĿǰλ����Ҫ��ʾ�ĺ�������ʾ���������ڲ��ĵڼ��У�����������λ����Ϊ��λ���о���λ��
//                uint16_t x_pos = (x_off*32)%320;  //ָʾĿǰλ������ʾ�ĺ��ֿ�ʼ���Ƶ����ص����λ�ã�Ҳ��һ�����������
//                uint16_t y_pos = (y_start+y_off*32)%240;  //ָʾĿǰλ����ʾ�ĺ��ֿ�ʼ���Ƶ����ص���λ�ã�Ҳ��һ���������ϲ�
//                uint8_t *temp=hanzi_3232+idx*(32*32/8); //��ǰָ��ÿ��ƫ��һ����������ֽ�����Ҳ��32*32/8=72���ֽڣ�ָ��8��bit����ʼbit  
//                Address_set(x_pos,y_pos,MIN(x_pos+31,320),MIN(y_pos+31,240));
//                /*�������Address_set��Ϊ�˿���д��������ʼ����Ϊ��ǰд�����ص����Ͻ�xy����
//                ��ֹ�����ڡ�����һ��������ʾ�߽硱�͡�������Ļ��ʾ�߽硱��ȡ��Сֵ
//                ������������������ʾ���ֺͱ߽��޷���ʾ�������ֵ��������
//                ��������������ʵû��Ӱ�죬��Ϊ��������ʽû�н��к����ƶ���������320�ɱ��ֿ�32����
//                �����������·��ĺ���ypos+31����ִ���240����������ȡ��СֵΪ240��������ʾ���������°벿��        
//                */
//                
//                for(uint8_t i=0;i<32*32/8 ;i++)  //һ������72���ֽڣ����ֽ�Ϊ��λѭ��
//                {//����д�������̣���ײ������ͬ��������break�ж�
//                    if(y_pos+i/(32/8)>=240) break;  
//                    /*��ʾ����ǰ���ֵĳ�ʼ������y_pos+Ӧ�����Ƶĵ�ǰ�ֽ����ڵ�����>=240ʱ���������������߼����㣬����ѭ��
//                    �����·����ֵ��°벿�ֲ��ٻ�������Ӧ���ڴ˻����߼�����Ӧ�ں����if�ж��л���
//                    ����32/8��ʾһ��32��������4���ֽڱ�ʾ����4���ֽڱ�ʾĳ����һ�еĻ������
//                    i/(32/8)�߼����������idx/DISPLAY_MAX_LENGTH�������㵱ǰӦ�û��Ƶ��ֽ��ڹ���һ���������ֵģ�
//                    ���ֽ�Ϊ��λ�ľ����д��ڵڼ��У������������ڶ�λ����*/
//
//                    for(uint8_t j=0;j<8;j++)
//                    {
//                        if((*temp&(1<<j))!=0)
//                            LCD_WR_DATA(RED);
//                        else
//                            LCD_WR_DATA(BLACK); 
//                    }
//                    temp++;
//                }//�������ʱ���ڲ������ڵ����ֽ���ѭ������
//                
//                if(y_pos+31>=240) //�������ƶ������·��޷�������ʾʱ
//                { 
//                    temp=hanzi_3232+idx*(32*32/8);  //��Ӧ���ֵĵ�һ�����Ƶ�
//                    Address_set(x_pos,0,MIN(x_pos+31,320),y_pos+31-240);  
//                    /*�޷�������ʾ������ʼ�������ض�λ�����Ϸ�����ֹ�������MINû��Ҫ
//                    ��ֹ��������Ϊ�޷���ʾ�����ĺ��ֵ��°벿���������ڽ����·��޷���ʾ�����ĺ����°벿��
//                    ӳ�䵽��Ļ���Ϸ���ʾ���ﵽѭ����Ŀ��*/
//                    for(uint8_t i=0;i<32*32/8 ;i++,temp++)  
//                    //temp++�������������������Է���ѭ�������continue��������ѭ��ʱ�޷�++���������
//                    {
//                        if(y_pos+(i/(32/8))<240)  //ͬ�ϣ����������ֵ��ϰ벿�ֲ��ٻ���������
//                            continue;
//                        else 
//                        {
//                            for(uint8_t j=0;j<8;j++)
//                                if((*temp&(1<<j))!=0)   LCD_WR_DATA(RED);
//                                else   LCD_WR_DATA(BLACK); 
//                        }//�°벿������Ļ���Ϸ���ʾ
//                    }
//                }

//            }
//            LCD_Rect_Clear(BLACK,0,y_start,320,MIN(y_start+4,240));
//            /*����֮ǰ��LCD_Clear()�����������ƣ�ֻ�����趨��������ֹ�㣬��ʼ��̶�(0,0),���дLCD_Rect_Clear()����
//            �������Ϊ������ɫ����ʼ/��ֹ���꣬�ӵ�0�У���ǰ��ʾ�п�ʼ�������һ�У�������Ϊ�����ĸ�4�����ص���һ��ʾ�л��240��*/
//        }
