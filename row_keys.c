// r1 r2 r3 r4 ---> p1.21 p1.22 p1.23 p1.24
// c1 c2 c3 c4 ---> p1.17 p1.18 p1.19 p1.20

/* 	row_pins as input
		col_pins as output
		*/
		
#include "../lcd_header.h"
#define ROWS (0x0F<<21)
#define COLS (0x0F<<17)

int main()
{
	int val;
//	IODIR1 = IODIR1 & ~((1<<17)|(1<<18)|(1<<19)|(1<<20));
//	IODIR1 = IODIR1 & ~(0x0F<<17);		//row pins as input
//	IODIR1 = IODIR1 | (0x0F<<21);			//col pins as output
	IODIR1 = IODIR1 & ~ROWS;		//row pins as input
	IODIR1 = IODIR1 | COLS;			//col pins as output
	lcd_config();
	while(1)
	{
		val = IOPIN1 & ROWS;		/*[24 23 22 21]	=  [1 1 1 1]	--> no key pressed
			= 0x01E00000	*/
		val = val >> 21;/*[24 23 22 21]>>21	= [1 1 1 1]-->[3 2 1 0]	--> no key pressed
				= 0x0F	*/
		switch(val)
		{
			case 0x0E:	lcd_str("r1");	delay(300); break;
			case 0x0D: 	lcd_str("r2");	delay(300);	break;
			case 0x0B: 	lcd_str("r3");	delay(300);	break;
			case 0x07: 	lcd_str("r4");	delay(300);	break;
		}
	}
}
