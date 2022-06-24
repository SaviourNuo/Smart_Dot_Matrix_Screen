#include "main.h"
//#include "task_manage.h"
//#include "oled.h"
//#include "stm32f10x.h"
//#include "common.h"
//#include "AD9834.h" 
//#include "page.h"
 
 
//u8 channelselect=0;
//u8 channelselected=8;
//double frevalue=0;
//u16 Phasvalue=0;
//u8 InputIndex=0;
//u8 InputIndexP=0;
//u8 InputIndexS=0;

 

u8 FrePointFlag=0;
u8 PhasePointFlag=0; 

u8 SetFreq=1;
u8 SetHopFreq=1;
u8 SetHopPoint=1;
u8 SetHopRate=1;
u8 SetPhase=0;

u8 Outputing=0;

unsigned char freq[15]="100000"; 
unsigned char phase[5]="     "; 
 

double OutFre;
double OutPhase;
 
u8   num_outfre;
double OutPhr;
double NMEA_Str2float(u8 *buf);
u8 intnumber(u32 a);
void 	clearfre(void);
void  clearphase(void);
void task_inputfre(void) 
{
 
  switch(Keycode)
	  { 
			case 0:  break;
		  case 1:    //功能键1
			 SetFreq=1;
		   Outputing=0;
		   FrePointFlag=0;
	     FocusButton(1);
		   FocusButton(7);
		   DeFocusButton(2);
			 DeFocusButton(3);
		   DeFocusButton(4);	
       DeFocusButton(5);		
		    
		   POINT_COLOR=WHITE;
			 SetHopFreq++;
			
		 
				 if (SetHopFreq>4)
					 SetHopFreq=1;
			   switch(SetHopFreq)
	      { 
			    case 0:  break;
		      case 1:
						LCD_ShowString3216(36,63,"1000 -  9000");
					  
            break;	
          case 2:
						LCD_ShowString3216(36,63,"2000 - 10000");
					  
            break;		
          case 3:
						LCD_ShowString3216(36,63,"4000 - 12000");
					  
            break;		
					 case 4:
						LCD_ShowString3216(36,63,"8000 - 16000");
					  
            break;		
        }
				
		   Delay_ms(200);
		   break;
		 
		  case 2:  //功能键2
				
			 FocusButton(2);
			 FocusButton(5);
		  
		   DeFocusButton(1);
		   DeFocusButton(3);
		   DeFocusButton(4);
		   DeFocusButton(6);
		   DeFocusButton(7);
		    
		   SetHopPoint++;
		   
				 POINT_COLOR=WHITE;
				 if (SetHopPoint>3)
					 SetHopPoint=1;
			   switch(SetHopPoint)
	      { 
			    case 0:  break;
		      case 1:
						LCD_ShowString3216(22,140,"   4    ");
					  
            break;	
          case 2:
						LCD_ShowString3216(22,140,"   8    ");
					  
            break;		
          case 3:
						LCD_ShowString3216(22,140,"  16    ");
					  
            break;		
        }
		 
       Delay_ms(200);
		   break;
		  case 3:  //功能键3
				 DeFocusButton(1);
		     DeFocusButton(2);
			   FocusButton(3);
		     DeFocusButton(4);	
         DeFocusButton(5);
         FocusButton(6);
         DeFocusButton(7);
        
		 
			  SetHopRate++;
			 POINT_COLOR=WHITE;
			 
				 if (SetHopRate>4)
					 SetHopRate=1;
			   switch(SetHopRate)
	      { 
			    case 0:  break;
		      case 1:
						LCD_ShowString3216(180,140,"  100  ");
					  
            break;	
          case 2:
						LCD_ShowString3216(180,140,"  200  ");
					  break;		
          case 3:
						LCD_ShowString3216(180,140,"  400  ");
					  break;	
					case 4:
						LCD_ShowString3216(180,140,"  800  ");
					  break;		
        }
			
		   Delay_ms(200);
		   break;
		   
		   
		case 4:    //功能键4
		   DeFocusButton(1);
		   DeFocusButton(2);
		   DeFocusButton(3);
		   FocusButton(4);
		   DeFocusButton(5);
		   DeFocusButton(6);
		   DeFocusButton(7);
		   //ad9833_datain(OutFre,OutPhase,SetLevel);
		
	  	ad9834_start();
		  
		   Delay_ms(200);
		   break;	 
	 }
 }

 
 void FocusButton(u16 number)
{  
 
	switch(number)
	  { 
			case 0:  break;
		  case 1:  
        Draw_Rect(2,190,78,239,RED);
		    Draw_Rect(3,189,77,238,RED);
		    break;
      case 2:  
        Draw_Rect(82,190,158,239,RED);
		    Draw_Rect(83,189,157,238,RED);
		    break;
      case 3:  
        Draw_Rect(162,190,238,239,RED);
		    Draw_Rect(163,189,237,238,RED);
		    break;
      case 4:  
        Draw_Rect(242,190,318,239,RED);
		    Draw_Rect(243,189,317,238,RED);
		    break;
			case 5:  
        Draw_Rect(2,108,157,181,YELLOW);  //level框
		    break;
		    
			case 6:  
        Draw_Rect(163,108,318,181,YELLOW);  //phase框
			  break;
			case 7:  
        Draw_Rect(2,32,318,102,YELLOW);  //fequency框
		    break;
			 
		}

	}

void DeFocusButton(u16 number)
{  
	 switch(number)
	  { 
			case 0:  break;
		  case 1:  
        Draw_Rect(2,190,78,239,GBLUE);
		    Draw_Rect(3,189,77,238,GBLUE);
		    break;
      case 2:  
        Draw_Rect(82,190,158,239,GBLUE);
		    Draw_Rect(83,189,157,238,GBLUE);
		    break;
      case 3:  
        Draw_Rect(162,190,238,239,GBLUE);
		    Draw_Rect(163,189,237,238,GBLUE);
		    break;
      case 4:  
        Draw_Rect(242,190,318,239,GBLUE);
		    Draw_Rect(243,189,317,238,GBLUE);
		    break;
			case 5:  
        Draw_Rect(2,108,157,181,BRRED);  //level框
		    break;
			case 6:  
   			Draw_Rect(163,108,318,181,BRRED); //phase框
		    break;
			case 7:  
   			Draw_Rect(2,32,318,102,BRRED);  //fequency框
		    break;
		
		}

}
 

  
 
