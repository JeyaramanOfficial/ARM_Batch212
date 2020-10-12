// ADC - Potentiometer
// P0.27 ---> channel0	--> PISEL1 --> [23:22] = [01] 
// Burst Mode configuration


#include "../lcd_header.h"

int main()
{
	int res;
	PINSEL1 |= (1<<22);
	PINSEL1 &= ~(1<<23);												// P0.27  as ADC channel0
	lcd_config();
	ADCR = (1<<0)|(0x04<<8)|(1<<16)|(1<<21);   //channel0 | CLKDIV | Burst mode | Power ON
	ADCR &= ~(0x07<<17);												//[000] ---> 10 bit conversion
	while(1)
	{
		while(!(ADDR & (1<<31)));						//check conversion
		res = ADDR & (0x3FF<<6);						//  [15 14 ---------- 8 7 6] >>6 == 
		res = res >> 6;	
		lcd_num(res);
		delay(1000);
		lcd_cmd(0x01);
	}
}
