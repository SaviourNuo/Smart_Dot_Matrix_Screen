#include "key.h"
#include "common.h"
#include "stm32f10x.h"
#include "systemconfig.h" 
 

//����˵��������ɨ��ԭ��1��3�ж�Ӧ��IO����Ϊ���,3�ж�Ӧ��IO����Ϊ���롣
//					2�����ް������£�3������IO����Ϊ�ߵ�ƽ����Ϊ���ⲿ�������裩
//					3�����������£���Ӧ��IO�����ͣ�����Ϊ��X�У������Ϊ�͵�ƽ�����������У�X�У��������������
//					4����ʱ�����θı�3�е����Ϊ�ߣ�����������������ʱ����X�е�ƽ���±�Ϊ�ߡ����������С������������


 
u16 Keycode = 0;												//ʵʱ������Ϣ����





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
