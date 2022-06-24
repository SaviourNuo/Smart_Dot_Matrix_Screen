#include "key.h"
#include "common.h"
#include "stm32f10x.h"
#include "systemconfig.h" 
 

//程序说明：按键扫描原理：1、3列对应的IO设置为输出,3行对应的IO设置为输入。
//					2、若无按键按下，3行输入IO，均为高电平（因为有外部上拉电阻）
//					3、若按键按下，对应行IO被拉低（假设为第X行），检测为低电平。按键所在行（X行），被鉴别出来。
//					4、此时，依次改变3列的输出为高，当遇到按键所在列时，第X行电平重新变为高。按键所在列。被鉴别出来。


 
u16 Keycode = 0;												//实时按键信息变量





u32 KeySweep(void)
{
	  Keycode=0;
 
 
	 if(KEY1==0)
	 {
		 Keycode=1;
	 }
	 else if(KEY2==0)
	 {
		 Keycode=2;
	 }
	 else if(KEY3==0)
	 {
		 Keycode=3;
	 }
	  else if(KEY4==0)
	 {
		 Keycode=4;
	 }
	
	
		return Keycode;
}
