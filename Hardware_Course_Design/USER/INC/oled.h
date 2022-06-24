#ifndef __OLED_H
#define __OLED_H	

#include "stm32f10x.h"

#define LCD_W 320 //����LCD����
#define LCD_H 240 //����LCD����


//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ
#define LBBLUE           0X2B12 //ǳ����ɫ


//ƫ�ײ㺯��
void LCD_Clear(u16 Color, u16 W, u16 H);
void LCD_Rect_Clear(u16 Color, uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void Lcd_Init(void);
void LCD_WRChinese(u8 i, char d);
void LCD_WR_DATA(int16_t da);

//��ʾ�������ֵ��ú���
void showhanzi_2424_color(unsigned int x,unsigned int y,unsigned char index,uint16_t bg_color,uint16_t point_color);
void showhanzi_3232_color(uint16_t x,uint16_t y,uint8_t index,uint16_t point_color ,uint16_t bg_color);

//��ʾ��ʽ�����л�����
void LCD_ScrollDisplay(u8 length);
void LCD_ScrollDisplayLeft(u8 length);
void LCD_ScrollDisplayRight(u8 length);
void LCD_ScrollDisplayUp(u8 length);
void LCD_ScrollDisplayDown(u8 length);
void LCD_ScrollDisplayMultiUp(void);

//�����ڲ�����
extern unsigned char freq[15];
extern unsigned char phase[5];
extern double OutFre;
extern double OutPhr;

#endif
