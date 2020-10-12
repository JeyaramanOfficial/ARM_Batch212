
#include "lcd_header.h"

int main()
{
	char name[] = "Cranes Varsity";
	int pincode =	560001;
	lcd_config();
	lcd_str(name);
	lcd_cmd(0xc0);
	lcd_num(pincode);
	while(1)
	{
		lcd_cmd(0x18);
		delay(500);
	}
}
