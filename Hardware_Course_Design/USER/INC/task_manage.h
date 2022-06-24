#ifndef __task_manage_H
#define __task_manage_H
#include "stm32f10x.h"

void task_inputfre(void);
void task_inputphase(void);
 
void float_to_str(char *str,double num);
void Int_To_Str(int x, u8 *Str);

//
void FocusKey1(void);
void DeFocusKey1(void); 
void FocusKey2(void);
void DeFocusKey2(u16 x1, u16 y1, u16 x2, u16 y2); 

void FocusButton(u16 number);
void DeFocusButton(u16 number);

extern u16 Keycode;
extern u8 FrePageSelected;
extern u8 PowerPageSelected;
extern u8 AmpPageSelected;



#endif
