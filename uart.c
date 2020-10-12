//3. loop back PC ---> MC ----> PC
//		a. check the status of RBR in LSR(Line Status Register) 
//		b. Receive the data using RBR
//		c. check the status of THR in LSR(Line Status Register) 
//		d. Transmit the data using THR	

// UART0 ---> p0.0	---> [1:0] --> 01
//						p0.1	---> [3:2] --> 01
#include <LPC21xx.h>
char u0_data;
int main()
{
	PINSEL0 |= (1<<0)|(1<<2);				//p0.0 and p0.1
	PINSEL0 &= ~((1<<1)|(1<<3));
	U0LCR |= (1<<7);					//DLAB enable
	U0DLL = 97;								//for baud rate 9600
	U0DLM = 0;
	U0LCR &= ~(1<<7);
	U0LCR |= (1<<0)|(1<<1);		//word length - 8 bit
	
	while(1)
	{
		while(!(U0LSR & (1<<0)));
		u0_data = U0RBR;
		while(!(U0LSR & (1<<5)));
		U0THR = u0_data;
	}
}
