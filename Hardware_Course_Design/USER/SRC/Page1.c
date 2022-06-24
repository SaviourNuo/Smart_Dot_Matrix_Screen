#include "main.h"

//void showimage(void); 
//void showhanzi_2424(unsigned int x,unsigned int y,unsigned char index);
//void showhanzi_2020(unsigned int x,unsigned int y,unsigned char index);
//void xianshi(void);
//void xianshi_PageSweepFre(void);
//void xianshi_PageSweepAmp(void);



static void xianshi() 
{   
  showimage(); //显示LOGO图片
	extern u16 BACK_COLOR, POINT_COLOR;//背景色，画笔色
	BACK_COLOR=BLACK;
	POINT_COLOR=BLUE;
	 
//	LCD_ShowString1608(44,8,"Microvue");
//	
//	BACK_COLOR=BLACK;
//	POINT_COLOR=WHITE;
//	
//	
//	LCD_ShowString1608(10,40,"Frequency");
// 
//	LCD_ShowString3216(36,63,"1000 -  9000");

//	POINT_COLOR=YELLOW;
//	LCD_ShowString3216(265,63,"KHz");

//	
//	POINT_COLOR=WHITE;
//	LCD_ShowString1608(10,116,"Hop-Point");
//	 
//	LCD_ShowString3216(22,140,"   4    "); 
//	
//	
//	 
//	
// 
//	LCD_ShowString1608(170,116,"Hop-Rate");
//	LCD_ShowString3216(180,140,"  100  "); 
//	
//	POINT_COLOR=YELLOW;
////	LCD_ShowString3216(265,140,"Hop/s"); 
//	
////	LCD_ShowString3216(265,140,"H/s"); 
//	
//	BACK_COLOR=BLACK; //WHITE;
//	POINT_COLOR=GBLUE	  ;
//	showhanzi_2424(13,203,0);  //频
//	showhanzi_2424(44,203,1);  //率
//	
//	showhanzi_2424(93,203,2);   //步
//	showhanzi_2424(124,203,3);  //进
//	
//	showhanzi_2424(173,203,4);  //跳
//	showhanzi_2424(204,203,5);  //速

//	showhanzi_2424(253,203,6);  //输
//	showhanzi_2424(284,203,7);  //出
//	
	 
} 
void DrawPage(void)
{
	//for (uint8_t i=1;i<8;i++)	DeFocusButton(i);
	xianshi();
}

//  
//   


////画矩形
//void Draw_Rect(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
//{
//	extern u16 BACK_COLOR, POINT_COLOR;//背景色，画笔色
//	  POINT_COLOR=color;	
//    LCD_DrawLine(x1,y1,x2,y1);
//		LCD_DrawLine(x1,y1,x1,y2);
//		LCD_DrawLine(x1,y2,x2,y2);
//    LCD_DrawLine(x2,y1,x2,y2);
//}
// 
//  
//void float_to_str(char *str,double num)
//  {
//		const double eps = 1e-11;
//		    double tp = 0.1;
//     int high;//float_整数部分  
//     double low;//float_小数部分 
//     char *start=str;
//     int n=0;
//     char ch[20];
//     int i;
//     high=(int)num;
//     low=num-high;
//     
//     while(high>0){
//         ch[n++]='0'+high%10;
//         high=high/10;
//     }
//     
//     for(i=n-1;i>=0;i--){
//         *str++=ch[i];
//     }
//     
//     num -= (int)num;
// 
//     *str++='.';
//     
//     while(num > eps){//精度限制 
//         num -= tp * (int)(low * 10);
//         tp /= 10;
//         *str++='0'+(int)(low*10);
//         low=low*10.0-(int)(low*10);
//     }
//     *str='\0';
//     str=start;
//}
// 

