//p0.8 ---> as single edge PWM
//MR0 --> TT and MR4 --->duty cycle

// Double edge PWM ---> rising edge --> MR3
											//Falling edge --> MR4
#include<LPC21xx.h>
void delay_ms(int);
int main()
{
//	PINSEL0 = 0x00020000;
	PINSEL0 |= (1<<17);
	PINSEL0 &= ~(1<<16);				//p0.8
	PWMPR = 14;
	PWMMR0 = 10000;							//Total Time period
	PWMLER = (1<<0);
	PWMMCR = (1<<1);						//Reset 
	PWMPCR |= (1<<12)|(1<<4);					//PWM output enable | PWM double edge
	PWMTCR = (1<<0) | (1<<3);		//timer | PWM enable
	while(1)
	{
			PWMMR3 = 3000;			//rising edge 
			PWMMR4 = 5500;			//falling edge  ---> 25% duty cycle
			PWMLER = (1<<3)|(1<<4);
			delay_ms(1000);
			PWMMR3 = 3000;			//rising edge 
			PWMMR4 = 7000;			//falling edge  ---> 50% duty cycle
			PWMLER = (1<<3)|(1<<4);
			delay_ms(1000);
	}	
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
