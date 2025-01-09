#include <reg51.h>
#define dataport P2

///// THIS CODE IS FOR 8 BIT MODE


sbit rs = P1^0;
sbit rw = P1^1;
sbit e = P1^2;

int s;

void delay(unsigned int msec)
{
	int i, j;
	for(i = 0; i < msec; i+=1)
	{
		for(j = 0; j < 1275; j+=1)
		{
		}
	}
}

/// Function to send command to LCD
void lcd_cmd(unsigned char item)
{
	dataport = item;
	rs = 0;
	rw = 0;
	e = 1;
	delay(1);
	e = 0;
}

//// Fundtion to send data to LCD
void lcd_data(unsigned char item)
{
	dataport = item;
	rs = 1;
	rw = 0;
	e = 1;
	delay(1);
	e = 0;
}

//// Funtiom to send more than one character
void message(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
	}
	
}

//// contain pre_defined manufacturer specified commands to intialize certain flags
void lcdinit()
{
	lcd_cmd(0x38); /// 8 bit. mode
	lcd_cmd(0x06); /// display from left to right
	lcd_cmd(0x0C); /// display ON, cursor hide
	lcd_cmd(0x01); /// clear LCD
}


void main()
{

	while(1)
	{
		lcdinit();
		lcd_cmd(0x90);
		message("I am AI fire");
		delay(1000);
		lcdinit();
		lcd_cmd(0x80);
		message("Welcome to 8051");
		lcd_cmd(0xc0);
		message("Microcontroller");
		lcd_cmd(0x90);
		message("		Dear 	 ");
		lcd_cmd(0xd0);
		message("		Students 	 ");
		delay(1000);
	}
}