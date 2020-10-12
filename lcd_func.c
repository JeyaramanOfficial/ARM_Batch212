// function definitions
#include "lcd_header.h"

void lcd_config(void)
{
	IODIR0 |= DATA_PINS|RS|RW|EN; 		//[31 ---[23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8] -----2 1 0]
						//[00000000[1  1  1  1  1  1  1  1  0  1  1  0  1] 000000000]
						//0x007FB400
	lcd_cmd(0x38);	//2 rows and 16 cols, 8 bit data
	lcd_cmd(0x0E);	//Cursor --> display or not
	lcd_cmd(0x01);	//clear existing data on LCD display
	lcd_cmd(0x80);	//pos to display the character
}

void lcd_cmd(char cmd)
{
	IOCLR0 = DATA_PINS;		//clearing 8 bits
	IOSET0 = cmd<<15;  // writing 8 bit cmds //[22 21 20 19 18 17 16 15 ]<---[ 0011 1000 ]
	IOCLR0 = RW;				
	IOCLR0 = RS;		//RS pin to 0
	IOSET0 = EN;
	delay(100);
	IOCLR0 = EN;
}

void lcd_data(char data)
{
	IOCLR0 = DATA_PINS;		//clearing 8 bits
	IOSET0 = data<<15;  // writing 8 bit cmds //[22 21 20 19 18 17 16 15 ]<---[ 0011 1000 ]
	IOCLR0 = RW;				
	IOSET0 = RS;			//RS pin to 1
	IOSET0 = EN;
	delay(100);
	IOCLR0 = EN;
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

//try to display name	
void lcd_str(char str[])
{
	int i;
	for(i=0;str[i]!='\0';++i)
		{
			lcd_data(str[i]);
		}
}

void lcd_str1(char str[])
{
	int i,count=0;
	for(i=0;str[i]!='\0';++i)
		{
			lcd_data(str[i]);
			if(count == 16)
			{
				lcd_cmd(0xC0);
			}
			count++;
		}
}

void lcd_num(int num)
{
	if(num)
	{
		lcd_num(num/10);
		lcd_data(num%10 + 0x30);
	}
}






