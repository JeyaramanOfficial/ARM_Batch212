// r1 r2 r3 r4 ---> p1.21 p1.22 p1.23 p1.24
// c1 c2 c3 c4 ---> p1.17 p1.18 p1.19 p1.20

/* 	intergrating rows and cols
		*/
		
#include "../lcd_header.h"
#define ROWS (0x0F<<21)
#define COLS (0x0F<<17)

void rows(void);
void cols(void);


int main()
{

	lcd_config();
	while(1)
	{
		rows();
		delay(1000);
		lcd_cmd(0x01);
		
	}
}

void rows(void)
{
	int val;

	IODIR1 = IODIR1 & ~ROWS;		//row pins as input
	IODIR1 = IODIR1 | COLS;			//col pins as output
	val = IOPIN1 & ROWS;		/*[24 23 22 21]	=  [1 1 1 1]	--> no key pressed
			= 0x01E00000	*/
	val = val >> 21;/*[24 23 22 21]>>21	= [1 1 1 1]-->[3 2 1 0]	--> no key pressed
			= 0x0F	*/
	switch(val)
	{
		case 0x0E:	lcd_str("r1"); cols();	delay(200); break;
		case 0x0D: 	lcd_str("r2"); cols();	delay(200);	break;
		case 0x0B: 	lcd_str("r3"); cols();	delay(200);	break;
		case 0x07: 	lcd_str("r4"); cols();	delay(200);	break;
	}
}

void cols(void)
{
	int val;
	IODIR1 = IODIR1 & ~COLS;		//col pins as input
	IODIR1 = IODIR1 | ROWS;			//ROWS pins as output
	
	val = IOPIN1 & COLS;		/*[20 19 18 17]	=  [1 1 1 1]	--> no key pressed
		= 0x01E00000	*/
	val = val >> 17;/*[20 19 18 17]>>17	= [1 1 1 1]-->[3 2 1 0]	--> no key pressed
			= 0x0F	*/
	switch(val)
	{
		case 0x0E:	lcd_str("C1");	delay(200); break;
		case 0x0D: 	lcd_str("C2");	delay(200);	break;
		case 0x0B: 	lcd_str("C3");	delay(200);	break;
		case 0x07: 	lcd_str("C4");	delay(200);	break;
	}
}
