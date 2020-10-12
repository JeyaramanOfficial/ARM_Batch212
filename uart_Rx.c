//2. from PC to MC transmit data
//		a. check the status of RBR in LSR(Line Status Register) 
//		b. Receive the data using RBR

// UART0 ---> p0.0	---> [1:0] --> 01
//						p0.1	---> [3:2] --> 01
#include "../lcd_header.h"
char u0_data;
int main()
{
	PINSEL0 |= (1<<0)|(1<<2);
	PINSEL0 &= ~((1<<1)|(1<<3));
	lcd_config();
	U0LCR |= (1<<7);
	U0DLL = 97;								//for baud rate 9600
	U0DLM = 0;
	U0LCR &= ~(1<<7);
	U0LCR |= (1<<0)|(1<<1);		//word length - 8 bit
	
	while(1)
	{
		while(!(U0LSR & (1<<0)));
		u0_data = U0RBR;
		lcd_data(u0_data);
	}
}
