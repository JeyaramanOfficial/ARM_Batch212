// using PLL produce the Freq as 36MHz. ---> P =4 and M = 3
// PSEL[6:5] 						MSEL[4:0] = (M-1)
//  00[6:5]  = 1
//  01[6:5]  = 2
//  10[6:5]  = 4
//  11[6:5]  = 8

#include<LPC21xx.h>
void pll_48MHz(void);
void pll_36MHz(void);
void pll_12MHz(void);
void blink_led(int );
void delay_ms(int );
int count = 0;

int main()
{
	IODIR1 |= (0xFF<<17);
	while(1)
	{
		IOSET1 = 0xFF<<17;			//15 MHz
		delay_ms(500);
		IOCLR1 = 0xFF<<17;
		delay_ms(500);
		count++;
		if(count >= 10 && count<20)
		{
			pll_36MHz();					//9 MHz
		}
		if (count >= 20 && count<25)
		{ 
			pll_12MHz();				//3 MHz
		} else if(count >= 25)
		{
			pll_48MHz();
		}
	
	}
}
// 12 MHz
void pll_36MHz(void)
{
	PLLCON = 1<<0; 				//Enable PLL
	PLLFEED = 0xAA;
	PLLFEED = 0x55;				//start clock pulse at 12 MHz
	PLLCFG = (1<<6)| 2;	//36MHz config
	PLLCFG &= ~(1<<5);
	while(!(PLLSTAT & (1<<10)));			//PLOCK Status
	PLLCON = (1<<1)|(1<<0);			//Connect to 36 MHZ
	PLLFEED = 0xAA;
	PLLFEED = 0x55;				//start clock pulse at 36 MHz
}

void pll_48MHz(void)
{
	PLLCON = 1<<0; 				//Enable PLL
	PLLFEED = 0xAA;
	PLLFEED = 0x55;				//start clock pulse at 12 MHz
	PLLCFG = (1<<5)| 3;	//36MHz config
	PLLCFG &= ~(1<<5);
	while(!(PLLSTAT & (1<<10)));			//PLOCK Status
	PLLCON = (1<<1)|(1<<0);			//Connect to 48 MHZ
	PLLFEED = 0xAA;
	PLLFEED = 0x55;				//start clock pulse at 36 MHz
}

void pll_12MHz(void)
{
	PLLCON = 1<<0; 				//Enable PLL
	PLLFEED = 0xAA;
	PLLFEED = 0x55;				//start clock pulse at 12 MHz
	PLLCFG = (1<<6)| (1<<5) | 0;	//12MHz config
	while(!(PLLSTAT & (1<<10)));			//PLOCK Status
	PLLCON = (1<<1)|(1<<0);			//Connect to 12 MHZ
	PLLFEED = 0xAA;
	PLLFEED = 0x55;				//start clock pulse at 36 MHz
}


void blink_led(int led)
{
		IOSET1 = 1<<led;  // High
		delay_ms(100);
		IOCLR1 = 1<<led;   // Low
		delay_ms(100);
}

void delay_ms(int ct)
{
	int i,j;
	for(i=0;i<ct;++i)
	{
		for(j=0;j<6000;++j)
		{}
	}
}
