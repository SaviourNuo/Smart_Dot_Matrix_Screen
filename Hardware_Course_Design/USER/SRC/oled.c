#include "main.h"
#include "oledfont.h" 

#define STRING_LENGTH 100 //������ʾ�ı�Ӱdemo�й���100����
#define DISPLAY_MAX_LENGTH 10  //�����Ǻ�����������ʾ��һ�л�һ�е����������Ϊ10
u16 BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ����

char LCD_ChineseData[180] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                            0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x16};
//������һλ��ʶ��һ�����Դ��������Ϊ180���֣����ܳ�����USART_REC_LEN���Ƶ������ٸ��־ͽ��䶪������ʵûʲô��
//���һ����ĿǰΪ0x16��ԭ���ǣ���ģ����ı��Ϊ22����Ϊһ���ո�����Ϊ���Դ���ĵ�һ����־λ��׼��


//��������д�룬�൱�ڴ���Ŀ����ײ���ײ�ĺ�����ִ��һ�κ�д��һ�ֽ�����
static void LCD_Writ_Bus(uint8_t dat)  
{	
	u8 i;			  
	for(i=0;i<8;i++)  //ÿ�η���1�������ݣ�1�ֽڼ�8�����أ���ѭ������Ϊ8
	{			  
		OLED_SCLK_Clr();  //SDA���ݷ���λֻ��SCLKʱ�ӵ�ƽ�ɵͱ��ʱ�Ž������ݵķ��ͣ������ÿ�η���ǰ��ʱ������
		if(dat&0x80)  //dataÿ�κʹ���������1���ֽڵ����λ����0x10000000���������㣬ȡ���������λ�������λΪ1
			 OLED_SDIN_Set();  //��SDA���ߣ�������������
		else 
		   OLED_SDIN_Clr();  //�����λΪ0�����õ͵�ƽ
		OLED_SCLK_Set();  //ʱ��SCLK���ߣ�ʱ�ӹ��������أ����һ�����ݷ���
		dat<<=1;   //����������һλ�����е�λ�Ƚ����½���ѭ��
	}			
}

//���㺯������װ����ײ��LCD_Writ_Bus�������˺������ڷ��������ֽڵ�����
void LCD_WR_DATA(int16_t da)
{
	OLED_DC_Set(); //DCΪ����/����ָʾλ��set�ߵ�ƽʱ��������
	LCD_Writ_Bus(da>>8); //���ȸ߰�λ����   
	LCD_Writ_Bus(da);  //�Ͱ�λ����
}	  

//���㺯������װ����ײ��LCD_Writ_Bus�������˺������ڷ���һ���ֽڵ�����
static void LCD_WR_REG(char da)
{	
	OLED_DC_Clr();  //DC�õ�λCLrʱ��ʾ��������
	LCD_Writ_Bus(da);  //����һ���ֽڵ�����
}

//���㺯������װ����ײ��LCD_Writ_Bus�������˺������ڷ���һ���ֽڵ�����
static void LCD_WR_DATA8(char da) 
{	
    OLED_DC_Set();
 	LCD_Writ_Bus(da);  
}  

//LCD��ʼ������
void Lcd_Init(void)
{
    OLED_RST_Clr();  
	Delay_ms(20);
	OLED_RST_Set();  //LCD��ʼ��ʱRESET���ߵ�ƽ���г�ʼ��
	Delay_ms(20);
	//	OLED_BLK_Set();
		
	//************* Start Initial Sequence **********// 
	/*LCD_WR_REG(0xCF);  
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0xD9); 
	LCD_WR_DATA8(0X30); 
	 
	LCD_WR_REG(0xED);  
	LCD_WR_DATA8(0x64); 
	LCD_WR_DATA8(0x03); 
	LCD_WR_DATA8(0X12); 
	LCD_WR_DATA8(0X81); 
	 
	LCD_WR_REG(0xE8);  
	LCD_WR_DATA8(0x85); 
	LCD_WR_DATA8(0x10); 
	LCD_WR_DATA8(0x78); 
	 
	LCD_WR_REG(0xCB);  
	LCD_WR_DATA8(0x39); 
	LCD_WR_DATA8(0x2C); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x34); 
	LCD_WR_DATA8(0x02); 
	 
	LCD_WR_REG(0xF7);  
	LCD_WR_DATA8(0x20); 
	 
	LCD_WR_REG(0xEA);  
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x00); */
	//��ʼ���ú���������Ҫ֪��ʲô��˼����ILI9341 DataSheet���Դ��� 
	LCD_WR_REG(0xC0);    //Power control 
	LCD_WR_DATA8(0x21);   //VRH[5:0] Set the GVDD level, which is a reference level for the VCOM level and the grayscale voltage level. 21: GVDD=4.45V
	 
	LCD_WR_REG(0xC1);    //Power control 
	LCD_WR_DATA8(0x12);   //SAP[2:0];BT[3:0] 
	 
	LCD_WR_REG(0xC5);    //VCom control 
	LCD_WR_DATA8(0x32);   //VMH[6:0] Set the VCOMH voltage.
	LCD_WR_DATA8(0x3C);   //VML[6:0] Set the VCOML voltage.
	 
	LCD_WR_REG(0xC7);    //VCM control2 
	LCD_WR_DATA8(0xC1); 
	 
	LCD_WR_REG(0x36);    // Memory Access Control 
	LCD_WR_DATA8(0x68);  //0xa8: horizontal display  0x08:vertical display
											 //0x68: ���� ��ת180��
	LCD_WR_REG(0x3A);   //Pixel Format Set
	LCD_WR_DATA8(0x55); 

	LCD_WR_REG(0xB1);   //Frame Rate Control
	LCD_WR_DATA8(0x00);   
	LCD_WR_DATA8(0x18); 
	 
	 

	LCD_WR_REG(0xB6);    // Display Function Control 
	LCD_WR_DATA8(0x0A); 
	LCD_WR_DATA8(0xA2); 

	 
	 
	LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
	LCD_WR_DATA8(0x00); 
	 
	LCD_WR_REG(0x26);    //Gamma curve selected 
	LCD_WR_DATA8(0x01); 
	 
	LCD_WR_REG(0xE0);    //Set Gamma 
	LCD_WR_DATA8(0x0F); 
	LCD_WR_DATA8(0x20); 
	LCD_WR_DATA8(0x1E); 
	LCD_WR_DATA8(0x09); 
	LCD_WR_DATA8(0x12); 
	LCD_WR_DATA8(0x0B); 
	LCD_WR_DATA8(0x50); 
	LCD_WR_DATA8(0XBA); 
	LCD_WR_DATA8(0x44); 
	LCD_WR_DATA8(0x09); 
	LCD_WR_DATA8(0x14); 
	LCD_WR_DATA8(0x05); 
	LCD_WR_DATA8(0x23); 
	LCD_WR_DATA8(0x21); 
	LCD_WR_DATA8(0x00); 
	 
	LCD_WR_REG(0XE1);    //Set Gamma 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x19); 
	LCD_WR_DATA8(0x19); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x12); 
	LCD_WR_DATA8(0x07); 
	LCD_WR_DATA8(0x2D); 
	LCD_WR_DATA8(0x28); 
	LCD_WR_DATA8(0x3F); 
	LCD_WR_DATA8(0x02); 
	LCD_WR_DATA8(0x0A); 
	LCD_WR_DATA8(0x08); 
	LCD_WR_DATA8(0x25); 
	LCD_WR_DATA8(0x2D); 
	LCD_WR_DATA8(0x0F); 
	 
	LCD_WR_REG(0x11);    //Exit Sleep 
	Delay_ms(120); 
	LCD_WR_REG(0x29);    //Display on 
}

//���㺯����LCD�����������������Ϊ�����ı�����ɫ�������ĳߴ�
void LCD_Clear(u16 Color, u16 W, u16 H)  
{
	u16 i,j;  	
	Address_set(0,0,W-1,H-1);  //�ڲ��洢���Դ��ӳ��д�뺯�������������ֲ�ʵ��
    for(i=0;i<W;i++)
	  for (j=0;j<H;j++)
        	LCD_WR_DATA(Color);	 //���ö��㺯������ָ�����ط�Χ�����ֽ�Ϊ��λд�����ݣ�������ɫ		 
}

//����������������������ʼ���꣬ʵ���˾��ο�����
void LCD_Rect_Clear(u16 Color, uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)  
{
	u16 i,j;  	
	Address_set(x1,y1,x2-1,y2-1);  //�ڲ��洢���Դ��ӳ��д�뺯�������������ֲ�ʵ��
    for(i=y1;i<y2;i++)
	  for (j=x1;j<x2;j++)
        	LCD_WR_DATA(Color);	 //���ö��㺯������ָ�����ط�Χ�����ֽ�Ϊ��λд�����ݣ�������ɫ		 
}

//չʾ24*24���غ��֣��������Ϊ����λ��x,y����������index���Դ�����ɫ�ͻ���ɫ�����ĺ�����ʾ����
void showhanzi_2424_color(unsigned int x,unsigned int y,unsigned char index,uint16_t point_color ,uint16_t bg_color)
{  
	unsigned char i,j;
	unsigned char *temp=hanzi_2424; //����*tempΪָ��������hanzi_2424��ָ�룬���ָ���ָʾ�����һ���������֣���ʼλ��Ϊ����ͷ��   
	Address_set(x,y,x+23,y+23);  //��������
	temp+=index*(24*24/8); //��ѭ���ⲿÿ��ָ��ƫ�ƶ���һ����
 	for(j=0;j<72 ;j++)  //һ������ռ72���ֽ���ʾ
	{
		for(i=0;i<8;i++)  //ÿ���ֽ�8����
		{ 		     
		 	if((*temp&(1<<i))!=0) //ָ���1����iλ���ֽ����������룬������ľ���ָ�뵱ǰָʾ�ı��أ��Ǿ��൱�ڽ���һλ����ȡ���ж�
			{
				LCD_WR_DATA(point_color); //�к������ݵ�ĵط����Ի�����ɫ���
			} 
			else
			{
				LCD_WR_DATA(bg_color); //û�к��ֵ����Ա�����ɫ���
			}   
		}
		temp++; //ָ��ƫ����ѭ���ڲ�ֻ����һ�����ص�ƫ��
	 }
}

//չʾ32*32���غ��֣��������Ϊ����λ��x,y����������index���Դ�����ɫ�ͻ���ɫ�����ĺ�����ʾ����
void showhanzi_3232_color(uint16_t x,uint16_t y,uint8_t index,uint16_t point_color ,uint16_t bg_color)
{
	unsigned char i,j;
	unsigned char *temp=hanzi_3232;    
    Address_set(x,y,x+31,y+31);  
	temp+=index*(32*32/8); 
 	for(j=0;j<128 ;j++)
	{
		for(i=0;i<8;i++)
		{
		 	if((*temp&(1<<i))!=0)
			{
				LCD_WR_DATA(point_color);
			} 
			else
			{
				LCD_WR_DATA(bg_color);
			}   
		}
		temp++;
	 }
}

//��ַ���ú�������ѯ�ֲ��֪16���������庬�壬x1,x2�����е���ֹ����y1,y2�����е���ֹ����
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)  
{ 
   LCD_WR_REG(0x2a); //0x2aΪILI9341����оƬ�е��е�ַ����������ڶ���֡�洢��������MCU�ܷ��ʵ�������
   LCD_WR_DATA8(x1>>8);
   LCD_WR_DATA8(x1);
   LCD_WR_DATA8(x2>>8);
   LCD_WR_DATA8(x2);
  
   LCD_WR_REG(0x2b);  //0x2bΪILI9341����оƬ�е�ҳ��ַ�������������Ϊ�����е�ַ���ã����ڶ���֡�洢��������MCU�ܷ��ʵ�������
   LCD_WR_DATA8(y1>>8);
   LCD_WR_DATA8(y1);
   LCD_WR_DATA8(y2>>8);
   LCD_WR_DATA8(y2);

   LCD_WR_REG(0x2C);  //0x2c���ڴ�MCU�������ݵ�֡�洢���������ʸ�ָ��ʱ���мĴ������мĴ���������Ϊ��ʼ��/�е�ַ��λ���ݱ�����֡�洢���У��˺���/�мĴ�����ֵ������1
	//0x2c Memory Write: This command is used to transfer data from MCU to frame memory.		 						 
  //When this command is accepted, the column register and the page register are reset to the Start Column/Start Page positions.
  //0x3c Write Memory Continue: This command transfers image data from the host processor to the display module`s frame memory 
	//continuing from the pixel location following the previous write_memory_continue or write_memory_start command.
}

//�����յ��ģ���ʾ��ģ�еڼ����ֵ����µ�16������d���밴���ʾ��LCD_ChineseData�����У�������һλ��־λ                           
void LCD_WRChinese(u8 i, char d) 
{
	LCD_ChineseData[i] = d;
}

//�˺������ڸ���LCD_ChineseData�е�bit0��־λѡ�������ʽ
void LCD_ScrollDisplay(u8 length) 
{
    if(LCD_ChineseData[0] == 0xF0) //����LCD_ChineseData�ĵ�һλ��ʶ���жϹ�����ʽ���������ʾʱ����һλҪע�����
		LCD_ScrollDisplayLeft(length);
	else if (LCD_ChineseData[0] == 0xF1)
		LCD_ScrollDisplayRight(length);
    else if (LCD_ChineseData[0] == 0xF2)
		LCD_ScrollDisplayUp(length);
    else if (LCD_ChineseData[0] == 0xF3)
		LCD_ScrollDisplayDown(length);
    else if (LCD_ChineseData[0] == 0xF4)
		LCD_ScrollDisplayMultiUp();
}

//1.������������ƶ�
void LCD_ScrollDisplayLeft(u8 length)
{
    //��������
    LCD_Rect_Clear(BLACK,0,0,320,240);
    
    //ѭ����ʾ
    while(USART_RX_STA==0)
    {
        uint8_t idx_temp;
    
               
        for(int idx = 0;idx<length;idx++) 
        /*����ѭ������㣬idx����������Ļ���Ͻ���ʾ�ĵ�һ������
        ���ѭ������������ʾ�ĺ����ܳ����൱��idx����1��ʾָ��������һ������ʹ�������Ͻ���ʾ
        ���ں���������ѭ������idxָʾ�ַ���a��Ϊb
        �����ڿ�����δ���ʾabcde����ʾbcdef�Ĵ�ѭ�����Ӷ�����������ʾ����*/
        {
            for(int x_idx_offset=0; x_idx_offset<DISPLAY_MAX_LENGTH; x_idx_offset++) 
            /*����ѭ���е��ڲ㣬���ڴ�����ʾ���ڲ�ѭ�������ڳ���Ϊ������Ļ����ͬʱ��ʾ�ĺ���������
            x_idx_offsetÿ������1ָʾ��ǰ��Ļ����Ҫ��ʾ�ĵ�x_idx_offset������
            ���ں�����ʾ��ѭ�������ڿ�����ΰ�˳��д��abcde*/
            {
                idx_temp = (idx+x_idx_offset)%length;
                /*idx_tempָʾ��ǰ�����ڵĵ�x_idx_offset��λ��Ӧ��ʾ�ĺ���
                ����ʾ�ĺ�������Ϊ���Ͻ���ʾ�ĺ��ּ��ڲ�ƫ������Ӧ�ַ������е�λ��
                ����%STRING_LENGTH��Ϊ���ڳ���һ�л������ڿɹ���ʾ�ĺ��ֳ���
                ���ڴ����Ͻ�idxָʾ�ĺ��ֿ�ʼ������ַ�����ʣ�຺�ֵ����ʱ
                �ܽ��޷������ĳ����ַ����鳤�ȵĲ��֣�ģ�����鿪ͷ���γ�ѭ��������ʾ*/
                if (idx_temp == 0) idx_temp=179; //������ʾ��һ����־������ôֱ����ʾ�ո�
          
                showhanzi_3232_color((x_idx_offset*32)%320,0,LCD_ChineseData[idx_temp],RED,BLACK);
                /*x_idx_offset*32��ʾÿ����ʾ���Ϊһ��������ģ���ȣ�%320Ϊ������LCD������ʾ�����ر߽�*/
                
            }
            Delay_ms(1000);  //��Ļ�����ٶ�
        }
    }
}

//2.����������ҹ���
void LCD_ScrollDisplayRight(u8 length)
{
    //��������
    LCD_Rect_Clear(BLACK,0,0,320,240);
    
    //ѭ����ʾ
    while(USART_RX_STA==0)
    {
        uint8_t idx_temp;
        for(int idx = length;idx>0;idx--)
        {
            for(int x_idx_offset=0; x_idx_offset<DISPLAY_MAX_LENGTH; x_idx_offset++)
            {
                idx_temp = (idx+x_idx_offset)%length;
                if (idx_temp == 0) idx_temp=179;
                showhanzi_3232_color(( x_idx_offset*32)%320,0,LCD_ChineseData[idx_temp],RED,BLACK ); 
            }
            Delay_ms(1000);
        }
              
    }
}

//3.������µ����ƶ�,ԭ������������ȫһ�£������ظ�ע�ͣ�ֻ�轫x_idx_offset��Ϊy_idx_offset���̶�x����ֻ��yƫ��   
void LCD_ScrollDisplayUp(u8 length)
{
    LCD_Rect_Clear(BLACK,0,0,320,240);
    while(USART_RX_STA==0)
    {
        uint8_t idx_temp;
        for(int idx = 0;idx<length;idx++)
        {
            for(int y_idx_offset=0; y_idx_offset<DISPLAY_MAX_LENGTH; y_idx_offset++)
            {
                idx_temp = (idx+y_idx_offset)%length;
                if (idx_temp == 0) idx_temp=179; 
                showhanzi_2424_color(0,(y_idx_offset*24)%240,LCD_ChineseData[idx_temp],RED,BLACK); 
            }
            Delay_ms(1000);
        }
    }
}

//4.������ϵ����ƶ� 
void LCD_ScrollDisplayDown(u8 length)
{
    LCD_Rect_Clear(BLACK,0,0,320,240);
    while(USART_RX_STA==0)
    {
        uint8_t idx_temp;
        for(int idx = length;idx>0;idx--)
        {
            for(int y_idx_offset=0; y_idx_offset<DISPLAY_MAX_LENGTH; y_idx_offset++)
            {
                idx_temp = (idx+y_idx_offset)%length;
                if (idx_temp == 0) idx_temp=179; 
                showhanzi_2424_color(0,(y_idx_offset*24)%240,LCD_ChineseData[idx_temp],RED,BLACK); 
            }
            Delay_ms(1000);
        }
    }
}

//5.������ʾ���µ����ƶ���������ʾ��Ӱdemo����չʾ�ܹ��洢����100����
void LCD_ScrollDisplayMultiUp()
{
    LCD_Rect_Clear(BLACK,0,0,320,240);
    while(USART_RX_STA==0)
    {
        for(int y_start = 0;y_start>=-640;y_start-=4)
        {/*��ֱ�������ѭ����������ֱ������ÿ�������ƶ�4�����ص㣬����ʹ��-640����Ϊÿ������32����32�����ص㣬���������ʾ200������
         ��ô��Ҳ����������������ĺ����˰ɣ�����ʹ�õ��ı�Ϊ������ġ���Ӱ��ѡ�Σ����Ͽո�ͱ�����Ϊ130���֣���ʼ��ʱʹ���һ������
         ��Ļ���Ϸ���ʾ���Ķν��й�640�����ص�����ƫ�ƺ�����ˢ�£����Ķ���ʾ�����Ϸ�*/  
            for(int idx = 0;idx<STRING_LENGTH;idx++)
            {// �Ժ��������ڵ������ַ��±�������
                        
                uint8_t x_off = idx%DISPLAY_MAX_LENGTH; //ָʾ��ǰ��Ŀǰλ����Ҫ��ʾ�ĺ��֣�ȡ�������λ���ڵ��о���λ��
                uint8_t y_off = idx/DISPLAY_MAX_LENGTH; //ָʾĿǰλ����Ҫ��ʾ�ĺ�������ʾ���������ڲ��ĵڼ��У�����������λ����Ϊ��λ���о���λ��
                uint16_t x_pos = (x_off*32)%320;  //ָʾĿǰλ������ʾ�ĺ��ֿ�ʼ���Ƶ����ص����λ�ã�Ҳ��һ�����������
                
//              uint16_t y_pos = ((y_start+y_off*32)>=0)?(y_start+y_off*32):240+(y_start+y_off*32);  
                /*ָʾĿǰλ����ʾ�ĺ��ֿ�ʼ���Ƶ����ص�����Ļ�ϵ���λ�ã��������ѡ������������ֱ��ȡģ
                ��Ϊ���жϵ�ǰҪ���Ƶĺ������ϲ��Ƿ񳬳�����Ļ�ϲ࣬��δ������ú���������������
                ���������λ��ӳ�䵽��Ļ�����·���ʾ���ﵽ����ȡģ��Ŀ�ģ�������y_start�л�������������
                �޷�ֱ��ȡģ��������̫��С��û�뵽ɶ�У��������y_posҲû�����ϰ���*/
                
                uint8_t *temp=hanzidemo_3232+idx*(32*32/8); //��ǰָ��ÿ��ƫ��һ����������ֽ�����Ҳ��32*32/8=72���ֽڣ�ָ��ú��ֵ���ʼbit  
                Address_set(x_pos,MAX(y_start+y_off*32,0),MIN(x_pos+31,320),y_start+y_off*32+31);
                /*�������Address_set��Ϊ�˿���д��������ʼ���������겻�䣬�������꣺���ú��ֵ����ϲ�δ������Ļ�ϱ��� ����������ʾ
                ���Ѿ�<0���������ϱ�Ե��˵���������ʾ��ȫ�ˣ���ô��������ʹ���Ļ�ϱ��ؿ��٣����޷�������ʾ�ĺ��ֽؿ���ͬʱ��ֹ����
                ֱ�Ӽ���һ�����ֵĸ߶ȣ���������������������Ϊ��Ļ�ϱ��ؿ�ʼ�Ŀ�320���أ��߲���һ�����ֵ�����*/
                
                
                for(uint8_t i=0;i<32*32/8 ;i++,temp++)  //һ������72���ֽڣ����ֽ�Ϊ��λѭ����ѭ����ɼ�д��һ������
                {/*����д�������̣���ײ������ͬ,���ѭ����Ϊ�˴����������⣺
                 1.��������Ļ�ڲ�������ʾ�ĺ���
                 2.�ƶ�����Ļ�Ϸ�ʱ�޷�������ʾ�ĺ��֣����ֻ���ƿ�����ʾ�������°벿��*/
                    
                    if(y_start+y_off*32+i/(32/8)<0) continue;                      
                    /*��ʾ����ǰ�������л���ʱ�����е���������ȻС���㣬��������Ļ�ϱ��أ���ֱ����������ѭ��������
                    ����ʱҪ���Ƶĺ����޷�������ʾʱֻ����������ʾ���°벿��
                    ����32/8��ʾһ��32��������4���ֽڱ�ʾ����4���ֽڱ�ʾĳ����һ�еĻ������
                    i/(32/8)�߼����������idx/DISPLAY_MAX_LENGTH�������㵱ǰӦ�û��Ƶ��ֽ��ڹ���һ���������ֵģ�
                    ���ֽ�Ϊ��λ�ľ����д��ڵڼ��У������������ڶ�λ����*/
                    
                    for(uint8_t j=0;j<8;j++)
                    {
                        if((*temp&(1<<j))!=0)
                            LCD_WR_DATA(RED);
                        else
                            LCD_WR_DATA(BLACK); 
                    }
                    
                    
                }//�������ʱ���ڲ������ڵ����ֽ���ѭ������
                
                if(y_start+y_off*32+31>=240)
                {/*�˺������ڽ����Ļ���·��ĺ����޷�������ʾ�����⣬if�жϵ�ǰ�ĺ��ֻ��Ƶ�������һ�������Ƿ񳬳�240����Ļ����
                  ��������������ж�*/
                    temp=hanzidemo_3232+idx*(32*32/8);  //ָ���Ӧ���ֵĵ�һ�����Ƶ�          
                    Address_set(x_pos,y_start+y_off*32,MIN(x_pos+31,320),240); 
                    /*�޷�������ʾʱ�����ٵ�ַ�ռ䣬��ʼ�е�ַΪ��ǰ�ĺ���������һ�����ص���λ�ã���ֹ�е�ַ��Ϊ240
                    ��ʾ�ú��ֵ��ϰ벿�ֻ�������*/
                    
                    for(uint8_t i=0;i<32*32/8;i++,temp++)  
                    //temp++�������������������Է���ѭ�������continue��������ѭ��ʱ�޷�++���������
                    {
                        if(y_start+y_off*32+i/(32/8)>=240)  //ͬ�ϣ����������ֵ��°벿�ֲ��ٻ���������
                            continue;
                        else 
                        {
                            for(uint8_t j=0;j<8;j++)
                                if((*temp&(1<<j))!=0)   LCD_WR_DATA(RED);
                                else   LCD_WR_DATA(BLACK); 
                        }//�ϰ벿������Ļ���·���ʾ
                    }
                   
                }
                

            }
            LCD_Rect_Clear(BLACK,0,y_start+((int)(ceil(STRING_LENGTH/10)))*32,320,y_start+((int)(ceil(STRING_LENGTH/10)))*32+4);
            /*���ô�0-320��������������Ϊ���һ�����ֵ�������һ�����ؿ�ʼ�������ֵĵ�ĩβ��ʼ������ÿ����4�����صĿ�ȣ���д����
            ����������Ҫ�����ԣ����ʹ��STRING_LENGTH�궨�嶨λ���һ�����֣�����ڳ���ÿһ�е�10���ֺ���Ҫ����ȡ�������ʹ��math.h
            �е�ceil��������ceil����ֵΪdouble���ͣ������Ҫint����ǿ��ת��*/
        }
            

	}
	
}

