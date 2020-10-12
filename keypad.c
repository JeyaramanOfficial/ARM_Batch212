/*  
7 8 9 /
4 5 6 x
1 2 3 -
. 0 = +
*/

// r1 r2 r3 r4 ---> p1.21 p1.22 p1.23 p1.24
// c1 c2 c3 c4 ---> p1.17 p1.18 p1.19 p1.20

/* 	intergrating rows and cols
		*/
		
#include "../lcd_header.h"
#define ROWS (0x0F<<21)
#define COLS (0x0F<<17)

void rows(void);
void col_1(void);
void col_2(void);
void col_3(void);
void col_4(void);

int main()
{

	lcd_config();
	while(1)
	{
		rows();
//		delay(1000);
//		lcd_cmd(0x01);
		
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
		case 0x0E:	 col_1();	delay(200); break;
		case 0x0D: 	 col_2();	delay(200);	break;
		case 0x0B: 	 col_3();	delay(200);	break;
		case 0x07: 	 col_4();	delay(200);	break;
	}
}

void col_1(void)					// r1 [7 8 9 /]
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
		case 0x0E:	lcd_data('7');	delay(200); break;
		case 0x0D: 	lcd_data('8');	delay(200);	break;
		case 0x0B: 	lcd_data('9');	delay(200);	break;
		case 0x07: 	lcd_data('/');	delay(200);	break;
	}
}

void col_2(void)					//r2 [4 5 6 x]
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
		case 0x0E:	lcd_data('4');	delay(200); break;
		case 0x0D: 	lcd_data('5');	delay(200);	break;
		case 0x0B: 	lcd_data('6');	delay(200);	break;
		case 0x07: 	lcd_data('x');	delay(200);	break;
	}
}

void col_3(void)			//r3	[1 2 3 -]
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
		case 0x0E:	lcd_data('1');	delay(200); break;
		case 0x0D: 	lcd_data('2');	delay(200);	break;
		case 0x0B: 	lcd_data('3');	delay(200);	break;
		case 0x07: 	lcd_data('-');	delay(200);	break;
	}
}

void col_4(void)	//r4 [. 0 = +]
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
		case 0x0E:	lcd_data('.');	delay(200); break;
		case 0x0D: 	lcd_data('0');	delay(200);	break;
		case 0x0B: 	lcd_data('=');	delay(200);	break;
		case 0x07: 	lcd_data('+');	delay(200);	break;
	}
}


// build a calculator
