#include "../lcd_header.h"


int main()
{
	lcd_config();
	CCR =1<<0;
	PREINT = 456;
	PREFRAC = 25024;
	
	HOUR = 7;
	MIN = 0;
	SEC = 0;
	
	while(1)
	{
		lcd_cmd(0x80);
		lcd_num(HOUR);
		lcd_data(':');
		lcd_cmd(0x83);
		lcd_num(MIN);
		lcd_data(':');
		if(SEC < 9)
		{
			lcd_cmd(0x86);
			lcd_data('0');
			lcd_num(SEC);
		}else{
			lcd_cmd(0x86);
			lcd_num(SEC);
		}
	}
}

