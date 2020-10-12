#include<lpc21xx.h>
void delay(int );
void blink_LED(int );
void intr_config(void);
void eint1_isr(void) __irq;
int main()
{
	IODIR1 |= (0xFF<<17);
	intr_config();
	while(1)
	{
		blink_LED(24);
	}
}

void intr_config(void)
{
	PINSEL0 |= (1<<29);
	PINSEL0 &= ~(1<<28);	//p0.14 ---> EINT1
	
	VICIntSelect &= ~(1<<15);		//EINT1 as IRQ
	VICVectCntl1	= (1<<5)| 15;	//slot enable | peripheral
	VICVectAddr1	=	(long)eint1_isr;
	VICIntEnable = 1<<15;
	EXTMODE = (1<<1);		//EINT1	--> Edge triggered(1)
	EXTPOLAR	= (1<<1);		// Rising edge(1)
//	EXTPOLAR	&= ~(1<<1);		// Falling Edge(0)
}

void eint1_isr(void) __irq
{
	blink_LED(17);
	EXTINT  = (1<<1);
	VICVectAddr = 0;
}

void blink_LED(int led)
{
	IOSET1 = 1<<led;
	delay(300);				//count by cpu
	IOCLR1 = 1<<led;
	delay(300);				//count by cpu
}

void delay(int ct)
{
	int i,j;
	for(i=0;i<ct;++i)
	{
		for(j=0;j<6000;++j)				//6000 x 1000 == 1sec (Approx)
		{}
	}
}
