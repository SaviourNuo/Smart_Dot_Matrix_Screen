#include "AD9834.h"
#include "stm32f10x.h"

void	ad9834_start(void)
{
  ad9834_contrlreg();
  ad9834_datain(50000,0);
}
void  ad9834_reset(void)
{
	ad9834_Write(0x2100);
	
}
void ad9834_datain(double freq, double phase)
 {
 u16 freq_LSB, freq_MSB, Phase_data;
 double freq_step;
	 u32 freq_hex;
	 freq_step=268435456/50;
	 freq_step=freq_step/1000000;
	 freq_step=freq_step*freq;
	 freq_hex=freq_step;
	 
	 freq_LSB=freq_hex;
	 freq_LSB=freq_LSB&0x3fff;
	 
	 freq_MSB=freq_hex>>14;
	 freq_MSB=freq_MSB&0x3fff;
	 
	 freq_LSB = freq_LSB | 0x4000;
	 freq_MSB = freq_MSB | 0x4000;
	 
	 Phase_data=phase;
	 Phase_data=Phase_data | 0xc000;
 	 ad9834_Write(freq_LSB);
	 ad9834_Write(freq_MSB);
	 ad9834_Write(Phase_data);
	 
 }	 
void ad9834_contrlreg(void)
	{
	  u16 ctrl_reg;
		u16 op_mode_div2;
		u16 sleep12;
//		u16 reset;
    u16 fpselect;

  //config AD9834 control register
   ctrl_reg = 0x2000;	
		//D0: RESERVED SET TO 0;
	  //D1: Mode ;  MODE=1: TRIANGLE WAVE MODE=0: SINUSOIDAL WAVE
		//D2: RESERVED SET TO 0;
		//D3: DIV2; When DIV2 = 1, the MSB of the DAC data is passed directly to the VOUT pin. 
		          //When DIV2 = 0, the MSB/2 of the DAC data is output at the VOUT pin.
		//D4: RESERVED SET TO 0;
		//D5: OPBITEN 
	  //D6: SLEEP12 :  1: POWER DOWN THE DAC; 0: ACTIVE DAC;
		//D7: SLEEP1: 1: DISABLED INTERNAL MCLK; 0: MCLK ENABLED
		//D8: RESET: 1: RESETS INTERNAL REGISTER TO 0; 0: DISABLED RESET;
		//D9: RESERVED SET TO 0;
		//D10: PSELECT 1:
		//D11: FSELECT
		//D12: HLB
		//D13: B28
	//switch(waveform)
	 // { 
	//		case 0:  break;
//		case 1:
//			op_mode_div2=0x0;    //0x00: sinusoid; 
//		  break;
 //   case 2:
//			op_mode_div2=0x02;    //0x02: triangle 
//		  break;
 //   case 3:
//			op_mode_div2=0x28;   //0x20: DAC data MSB/2    //0x28: DAC data MSB square
//			break;
//		}
	    
	op_mode_div2=0x0;                       
												
	ctrl_reg = ctrl_reg | op_mode_div2;
	
	sleep12=0x00;           //0x00: No power down
                         	//0x01: DAC power 
                          //0x02: internal clock disabled
                          //0x03: both the DAC power down and the internal click disabled
	ctrl_reg = ctrl_reg | (sleep12 << 6);
	
	fpselect =0x00;    //0x00: FREQ0, PHASE0
	                   //0x01: FREQ0, PHASE1
	                   //0x02: FREQ1, PHASE0
	                   //0x03: FREQ1, PHASE1
	ctrl_reg = ctrl_reg | (fpselect << 10);
	
	ad9834_Write(ctrl_reg);

}
	
void ad9834_Write(u16 cfword)
{
u16 w;
u16 i;
	
	
w=cfword;
	
ad9834_sync=0;
ad9834_clk=1;

for(i=16;i>0;i--)
{
	
ad9834_data=(w>>(i-1))&0x01;
 
ad9834_clk=0;
 
ad9834_clk=1;
 
}
 
ad9834_sync=1;

}
