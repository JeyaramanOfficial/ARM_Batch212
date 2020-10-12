// MAster Transmitter mode

// P0.2 [5:4] 01 -->SDA and 
// P0.3 [7:6] 01---> SCL

#include "../lcd_header.h"
void i2c_init(void);
void i2c_Start(void);
void i2c_tx_data(char );
char i2c_rx_data(void);
void i2c_stop(void);

int main()
{	
	char i2c_rdata;
	lcd_config();
	i2c_init();
	
	i2c_Start();
	i2c_tx_data(0xA0);			
	i2c_tx_data(0x01);			//memory Address
	
	I2CONSET = (1<<2);			//Assert Ack
	
	i2c_Start();						//Repeat Start
	i2c_tx_data(0xA1);			//Slave Address (1010 000) + 1 ---> read data from slave
	
	i2c_rdata = i2c_rx_data();
	lcd_data(i2c_rdata);		//C
	i2c_rdata = i2c_rx_data();
	lcd_data(i2c_rdata);		//R
	i2c_rdata = i2c_rx_data();
	lcd_data(i2c_rdata);		//A
	i2c_rdata = i2c_rx_data();
	lcd_data(i2c_rdata);		//N
	i2c_rdata = i2c_rx_data();
	lcd_data(i2c_rdata);		//E
	i2c_rdata = i2c_rx_data();
	lcd_data(i2c_rdata);		//S
	
	i2c_stop();
//	| 0 | 0xA1 | 0x01 | A | B | C | D | 1 |
	lcd_cmd(0xC0);
	lcd_str("Data from EEPROM");
}

void i2c_init(void)
{
	PINSEL0 |= (1<<4)|(1<<6);
	PINSEL0 &= ~((1<<5)|(1<<7));		//p0.2,p0.3
	I2CONSET = 1<<6;								//I2c Enable
	I2SCLH = 75;										//Bit transfer rate
	I2SCLL = 75;
}

void i2c_Start(void)
{
	I2CONCLR = (1<<3);		//make sure SI flag is cleared
	I2CONSET = (1<<5);			// start bit
	while(!(I2CONSET &(1<<3)));
	I2CONCLR = (1<<5);			// clear start bit for rem frames
	I2CONCLR = (1<<3);			// clear flag bit
}

void i2c_tx_data(char idata)
{
	I2DAT = idata;
	while(!(I2CONSET &(1<<3)));
	I2CONCLR = (1<<3);			// clear flag bit
}

char i2c_rx_data(void)
{
	char recv_data;
	while(!(I2CONSET &(1<<3)));
	I2CONCLR = (1<<3);
	recv_data = I2DAT;
	return recv_data;
}

void i2c_stop(void)
{
	I2CONSET = (1<<4);
}
