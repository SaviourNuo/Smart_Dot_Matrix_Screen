#include "main.h"
#include "oledfont.h" 

#define STRING_LENGTH 100 //用于演示的背影demo中共有100个字
#define DISPLAY_MAX_LENGTH 10  //不管是横向还是纵向显示，一行或一列的最大字数都为10
u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色变量

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
//连带第一位标识符一共可以传入的数据为180个字，不能超过，USART_REC_LEN限制的是两百个字就将其丢弃，其实没什么用
//最后一个字目前为0x16的原因是，字模里面的编号为22的字为一个空格，这是为忽略传入的第一个标志位做准备


//串行数据写入，相当于此项目中最底层最底层的函数，执行一次后写入一字节数据
static void LCD_Writ_Bus(uint8_t dat)  
{	
	u8 i;			  
	for(i=0;i<8;i++)  //每次发送1比特数据，1字节即8个比特，故循环次数为8
	{			  
		OLED_SCLK_Clr();  //SDA数据发送位只在SCLK时钟电平由低变高时才进行数据的发送，因此在每次发送前将时钟拉低
		if(dat&0x80)  //data每次和待发送数据1个字节的最高位，即0x10000000进行与运算，取出数据最高位，若最高位为1
			 OLED_SDIN_Set();  //则将SDA拉高，发送数据数据
		else 
		   OLED_SDIN_Clr();  //若最高位为0，则置低电平
		OLED_SCLK_Set();  //时钟SCLK拉高，时钟构成上升沿，完成一次数据发送
		dat<<=1;   //将数据左移一位，进行低位比较重新进入循环
	}			
}

//二层函数，封装了最底层的LCD_Writ_Bus函数，此函数用于发送两个字节的数据
void LCD_WR_DATA(int16_t da)
{
	OLED_DC_Set(); //DC为命令/数据指示位，set高电平时发送数据
	LCD_Writ_Bus(da>>8); //首先高八位发送   
	LCD_Writ_Bus(da);  //低八位发送
}	  

//二层函数，封装了最底层的LCD_Writ_Bus函数，此函数用于发送一个字节的命令
static void LCD_WR_REG(char da)
{	
	OLED_DC_Clr();  //DC置低位CLr时表示发送命令
	LCD_Writ_Bus(da);  //发送一个字节的数据
}

//二层函数，封装了最底层的LCD_Writ_Bus函数，此函数用于发送一个字节的数据
static void LCD_WR_DATA8(char da) 
{	
    OLED_DC_Set();
 	LCD_Writ_Bus(da);  
}  

//LCD初始化函数
void Lcd_Init(void)
{
    OLED_RST_Clr();  
	Delay_ms(20);
	OLED_RST_Set();  //LCD初始化时RESET拉高电平进行初始化
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
	//初始化用函数，不需要知道什么意思，是ILI9341 DataSheet中自带的 
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
											 //0x68: 横屏 旋转180度
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

//三层函数，LCD清屏函数，输入参数为清屏的背景颜色和清屏的尺寸
void LCD_Clear(u16 Color, u16 W, u16 H)  
{
	u16 i,j;  	
	Address_set(0,0,W-1,H-1);  //内部存储到显存的映射写入函数，查阅数据手册实现
    for(i=0;i<W;i++)
	  for (j=0;j<H;j++)
        	LCD_WR_DATA(Color);	 //调用二层函数，在指定像素范围内以字节为单位写入数据，控制颜色		 
}

//矩形清屏函数，增加了起始坐标，实现了矩形框清屏
void LCD_Rect_Clear(u16 Color, uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)  
{
	u16 i,j;  	
	Address_set(x1,y1,x2-1,y2-1);  //内部存储到显存的映射写入函数，查阅数据手册实现
    for(i=y1;i<y2;i++)
	  for (j=x1;j<x2;j++)
        	LCD_WR_DATA(Color);	 //调用二层函数，在指定像素范围内以字节为单位写入数据，控制颜色		 
}

//展示24*24像素汉字，输入参数为坐标位置x,y和文字索引index，自带背景色和画笔色参数的汉字显示函数
void showhanzi_2424_color(unsigned int x,unsigned int y,unsigned char index,uint16_t point_color ,uint16_t bg_color)
{  
	unsigned char i,j;
	unsigned char *temp=hanzi_2424; //定义*temp为指向汉字数组hanzi_2424的指针，这个指针的指示间隔是一个完整汉字，初始位置为数组头部   
	Address_set(x,y,x+23,y+23);  //设置区域
	temp+=index*(24*24/8); //大循环外部每次指针偏移都是一个字
 	for(j=0;j<72 ;j++)  //一个汉字占72个字节显示
	{
		for(i=0;i<8;i++)  //每个字节8比特
		{ 		     
		 	if((*temp&(1<<i))!=0) //指针和1左移i位的字节内数据相与，正好与的就是指针当前指示的比特，那就相当于将这一位单独取出判断
			{
				LCD_WR_DATA(point_color); //有汉字数据点的地方，以画笔颜色填充
			} 
			else
			{
				LCD_WR_DATA(bg_color); //没有汉字点则以背景颜色填充
			}   
		}
		temp++; //指针偏移在循环内部只进行一个比特的偏移
	 }
}

//展示32*32像素汉字，输入参数为坐标位置x,y和文字索引index，自带背景色和画笔色参数的汉字显示函数
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

//地址设置函数，查询手册可知16进制数具体含义，x1,x2定义列的起止区域，y1,y2定义行的起止区域
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)  
{ 
   LCD_WR_REG(0x2a); //0x2a为ILI9341驱动芯片中的列地址设置命令，用于定义帧存储器的区域（MCU能访问到的区域）
   LCD_WR_DATA8(x1>>8);
   LCD_WR_DATA8(x1);
   LCD_WR_DATA8(x2>>8);
   LCD_WR_DATA8(x2);
  
   LCD_WR_REG(0x2b);  //0x2b为ILI9341驱动芯片中的页地址设置命令，可以认为就是行地址设置，用于定义帧存储器的区域（MCU能访问到的区域）
   LCD_WR_DATA8(y1>>8);
   LCD_WR_DATA8(y1);
   LCD_WR_DATA8(y2>>8);
   LCD_WR_DATA8(y2);

   LCD_WR_REG(0x2C);  //0x2c用于从MCU传输数据到帧存储器，当访问该指令时，列寄存器和行寄存器被设置为开始列/行地址，位数据保存在帧存储器中，此后列/行寄存器的值都递增1
	//0x2c Memory Write: This command is used to transfer data from MCU to frame memory.		 						 
  //When this command is accepted, the column register and the page register are reset to the Start Column/Start Page positions.
  //0x3c Write Memory Continue: This command transfers image data from the host processor to the display module`s frame memory 
	//continuing from the pixel location following the previous write_memory_continue or write_memory_start command.
}

//将接收到的，表示字模中第几个字的最新的16进制数d存入按序表示的LCD_ChineseData数组中，包括第一位标志位                           
void LCD_WRChinese(u8 i, char d) 
{
	LCD_ChineseData[i] = d;
}

//此函数用于根据LCD_ChineseData中的bit0标志位选择滚动方式
void LCD_ScrollDisplay(u8 length) 
{
    if(LCD_ChineseData[0] == 0xF0) //根据LCD_ChineseData的第一位标识符判断滚动方式，因此在显示时，第一位要注意忽略
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

//1.横向从右向左移动
void LCD_ScrollDisplayLeft(u8 length)
{
    //清屏函数
    LCD_Rect_Clear(BLACK,0,0,320,240);
    
    //循环显示
    while(USART_RX_STA==0)
    {
        uint8_t idx_temp;
    
               
        for(int idx = 0;idx<length;idx++) 
        /*两层循环的外层，idx用于索引屏幕左上角显示的第一个汉字
        最多循环次数与需显示的汉字总长度相当，idx自增1表示指针移向下一个汉字使其在左上角显示
        属于汉字索引的循环，若idx指示字符由a变为b
        则用于控制如何从显示abcde到显示bcdef的大循环，从而滑动汉字显示窗口*/
        {
            for(int x_idx_offset=0; x_idx_offset<DISPLAY_MAX_LENGTH; x_idx_offset++) 
            /*两层循环中的内层，用于窗口显示的内部循环，窗口长度为横向屏幕可以同时显示的汉字最大个数
            x_idx_offset每次自增1指示当前屏幕上需要显示的第x_idx_offset个汉字
            属于汉字显示的循环，用于控制如何按顺序写出abcde*/
            {
                idx_temp = (idx+x_idx_offset)%length;
                /*idx_temp指示当前窗口内的第x_idx_offset个位置应显示的汉字
                其显示的汉字索引为左上角显示的汉字加内部偏移量对应字符数组中的位置
                这里%STRING_LENGTH是为了在出现一行滑动窗口可供显示的汉字长度
                大于从左上角idx指示的汉字开始计算的字符数组剩余汉字的情况时
                能将无法索引的超出字符数组长度的部分，模到数组开头，形成循环滚动显示*/
                if (idx_temp == 0) idx_temp=179; //若该显示第一个标志符，那么直接显示空格
          
                showhanzi_3232_color((x_idx_offset*32)%320,0,LCD_ChineseData[idx_temp],RED,BLACK);
                /*x_idx_offset*32表示每次显示间隔为一个汉字字模长度，%320为不超过LCD横向显示的像素边界*/
                
            }
            Delay_ms(1000);  //屏幕更新速度
        }
    }
}

//2.横向从左向右滚动
void LCD_ScrollDisplayRight(u8 length)
{
    //清屏函数
    LCD_Rect_Clear(BLACK,0,0,320,240);
    
    //循环显示
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

//3.纵向从下到上移动,原理与横向滚动完全一致，不再重复注释，只需将x_idx_offset改为y_idx_offset，固定x坐标只在y偏移   
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

//4.纵向从上到下移动 
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

//5.多排显示从下到上移动，用于演示背影demo，并展示能够存储超过100个字
void LCD_ScrollDisplayMultiUp()
{
    LCD_Rect_Clear(BLACK,0,0,320,240);
    while(USART_RX_STA==0)
    {
        for(int y_start = 0;y_start>=-640;y_start-=4)
        {/*竖直方向滚动循环遍历，竖直方向汉字每次整体移动4个像素点，这里使用-640是因为每个汉字32个高32个像素点，因此正好显示200个汉字
         怎么着也不会输入比这个还多的汉字了吧，现在使用的文本为朱自清的《背影》选段，加上空格和标点符号为130个字，初始化时使其第一个字在
         屏幕最上方显示，文段进行过640个像素的向上偏移后，重新刷新，将文段显示在最上方*/  
            for(int idx = 0;idx<STRING_LENGTH;idx++)
            {// 对汉字数组内的所有字符下标做遍历
                        
                uint8_t x_off = idx%DISPLAY_MAX_LENGTH; //指示当前行目前位置需要显示的汉字，取余操作定位行内的列绝对位置
                uint8_t y_off = idx/DISPLAY_MAX_LENGTH; //指示目前位置需要显示的汉字在显示汉字区域内部的第几行，除法操作定位以行为单位的行绝对位置
                uint16_t x_pos = (x_off*32)%320;  //指示目前位置需显示的汉字开始绘制的像素点的列位置，也即一个汉字最左侧
                
//              uint16_t y_pos = ((y_start+y_off*32)>=0)?(y_start+y_off*32):240+(y_start+y_off*32);  
                /*指示目前位置显示的汉字开始绘制的像素点在屏幕上的行位置，这里采用选择语句而非如上直接取模
                是为了判断当前要绘制的汉字最上测是否超出了屏幕上侧，若未超出则该汉字仍能完整绘制
                否则则将这个位置映射到屏幕的最下方显示，达到类似取模的目的，而由于y_start中混杂正负数，故
                无法直接取模（至少我太弱小了没想到啥招）不过这个y_pos也没有用上罢了*/
                
                uint8_t *temp=hanzidemo_3232+idx*(32*32/8); //当前指针每次偏移一个字所需的字节数，也即32*32/8=72个字节，指向该汉字的起始bit  
                Address_set(x_pos,MAX(y_start+y_off*32,0),MIN(x_pos+31,320),y_start+y_off*32+31);
                /*这里调用Address_set是为了开辟写入区域，起始坐标列坐标不变，而行坐标：若该汉字的最上侧未超出屏幕上边沿 ，则正常显示
                若已经<0，即超过上边缘，说明这个字显示不全了，那么开辟区域就从屏幕上边沿开辟，把无法完整显示的汉字截开，同时终止坐标
                直接加上一个汉字的高度，则正负抵消。开辟区域为屏幕上边沿开始的宽320像素，高不足一个汉字的区域*/
                
                
                for(uint8_t i=0;i<32*32/8 ;i++,temp++)  //一个汉字72个字节，以字节为单位循环，循环完成即写入一个汉字
                {/*正常写汉字流程，与底层基本相同,这个循环是为了处理两个问题：
                 1.可以在屏幕内部完整显示的汉字
                 2.移动到屏幕上方时无法完整显示的汉字，如何只绘制可以显示出来的下半部分*/
                    
                    if(y_start+y_off*32+i/(32/8)<0) continue;                      
                    /*表示若当前汉字逐行绘制时若该行的行坐标仍然小于零，即超出屏幕上边沿，则直接跳过本次循环不画点
                    即此时要绘制的汉字无法完整显示时只绘制其能显示的下半部分
                    这里32/8表示一行32个像素用4个字节表示，即4个字节表示某汉字一行的画点规律
                    i/(32/8)逻辑类似上面的idx/DISPLAY_MAX_LENGTH，即计算当前应该绘制的字节在构成一个完整汉字的，
                    以字节为单位的矩阵中处于第几行，除法操作用于定位行数*/
                    
                    for(uint8_t j=0;j<8;j++)
                    {
                        if((*temp&(1<<j))!=0)
                            LCD_WR_DATA(RED);
                        else
                            LCD_WR_DATA(BLACK); 
                    }
                    
                    
                }//其余情况时，内部正常在单个字节内循环画点
                
                if(y_start+y_off*32+31>=240)
                {/*此函数用于解决屏幕最下方的汉字无法完整显示的问题，if判断当前的汉字绘制的最下面一行像素是否超出240的屏幕边沿
                  若超出，则进入判断*/
                    temp=hanzidemo_3232+idx*(32*32/8);  //指针对应汉字的第一个绘制点          
                    Address_set(x_pos,y_start+y_off*32,MIN(x_pos+31,320),240); 
                    /*无法完整显示时，开辟地址空间，起始行地址为当前的汉字最上面一行像素的行位置，终止行地址即为240
                    表示该汉字的上半部分绘制区域*/
                    
                    for(uint8_t i=0;i<32*32/8;i++,temp++)  
                    //temp++放在括号内是由于若仍放在循环最后，则continue跳过本次循环时无法++，程序出错
                    {
                        if(y_start+y_off*32+i/(32/8)>=240)  //同上，不完整汉字的下半部分不再画出，跳过
                            continue;
                        else 
                        {
                            for(uint8_t j=0;j<8;j++)
                                if((*temp&(1<<j))!=0)   LCD_WR_DATA(RED);
                                else   LCD_WR_DATA(BLACK); 
                        }//上半部分在屏幕最下方显示
                    }
                   
                }
                

            }
            LCD_Rect_Clear(BLACK,0,y_start+((int)(ceil(STRING_LENGTH/10)))*32,320,y_start+((int)(ceil(STRING_LENGTH/10)))*32+4);
            /*设置从0-320列清屏，行清屏为最后一行文字的最下面一行像素开始，即文字的的末尾开始清屏，每次清4个像素的宽度，先写后清
            这里由于需要泛用性，因此使用STRING_LENGTH宏定义定位最后一行文字，因此在除以每一行的10个字后需要向上取整，因此使用math.h
            中的ceil函数，但ceil返回值为double类型，因此需要int类型强制转换*/
        }
            

	}
	
}

