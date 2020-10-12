#include<lpc21XX.h>
void delay(int);
void blink_led(int);
void interrupt_config(void);
void eint_isr(void) __irq; // ISR function
int main()
{
	IODIR1 = IODIR1 | (0XFF<<17);
	
	interrupt_config();
	while(1)
	{
	 blink_led(24); 
	}
}

void interrupt_config(void)
{
 PINSEL0 |= (1<<29);
 PINSEL0 &=~(1<<28);
 VICIntSelect &= ~(1<<15); 
 VICVectCntl1 = (	1<<5)|15;	
 VICVectAddr1 = (long)eint_isr;
 VICIntEnable = (1<<15);
 EXTMODE = (1<<1);
 EXTPOLAR = (1<<1); 

}
void eint_isr(void) __irq
{
blink_led(17);
EXTINT = (1<<1); // clear interrupt flag bit
VICVectAddr =  0X00000000;
}
void blink_led(int led)
{
IOSET1 = 1<<led;
delay(300);
IOCLR1 = 1<<led;
delay(300);
}

void delay(int ct)
{int i,j;
{
for(i=0;i<=ct;i++)
for(j=0;j<=6000;++j)
{}
}
}
