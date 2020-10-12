#include<LPC21xx.h>
void blink_led(int );
void delay_ms(int );
int main()
{
	IODIR1 |= (0xFF<<17);
	WDMOD = (1<<0)|(1<<1);
	WDTC = 0xFFFFFF;			//timer constant value
	WDFEED = 0xAA;
	WDFEED = 0x55;
	blink_led(24);			
	while(1)
	{
		if(WDTV <= 0x800000)
		{
				WDFEED = 0xAA;
				WDFEED = 0x55;
		}
		IOSET1 = 1<<17;  // High
		delay_ms(100);
		IOCLR1 = 1<<17;   // Low
		delay_ms(100);
	}
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
