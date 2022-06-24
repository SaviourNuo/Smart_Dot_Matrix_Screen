#ifndef __KEY_H
#define __KEY_H	
#include "stm32f10x.h" 
 	


void Read_KX(u16 x);
void Read_KY(u16 x);
void ResetAllKY(void);
void KX_AllStatus(void);
void Set_KY(u16 x);
void Rst_KY(u16 x);
u32 KeySweep(void);
extern u16 Keycode;
#endif
