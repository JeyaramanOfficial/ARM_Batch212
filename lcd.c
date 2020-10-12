//Control pins --> (RS, RW, EN ) --> (p0.10, p0.12, p0.13)
//data pins ---> (D0 -- D7) --> (p0.15 to p0.22)


#include<lpc21xx.h>
#define RS (1<<10)
#define RW (1<<12)
#define EN (1<<13)
#define DATA_PINS (0xFF<<15)

void lcd_config(void);
void lcd_cmd(char);
void lcd_data(char);
void lcd_str(char []);
void lcd_str1(char []);
void delay(int);

int main()
{
//		char name[] = "CRANES Varsity Bangalore Karnataka-560001";
//		char name[] = "CRANES Varsity";
//		char address[] = "Bangalore";
		int num = 8,res,quotient,remainder;  	//48 ---> 0 // 0x30 ---> 0
		res = 66 + 33;
		lcd_config();	
		quotient = res/10;
		remainder = res%10;
		lcd_data(quotient +	0x30);
		lcd_data(remainder + 0x30);
	
//		lcd_data('0');
//		lcd_data(num + 0x30);
//		lcd_data(num + 48);
//		lcd_data(num + '0');
//		lcd_str(name);
//		lcd_cmd(0xc0);
//		lcd_str(address);
}

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








