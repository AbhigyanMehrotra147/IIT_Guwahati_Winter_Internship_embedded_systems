#include <reg51.h>
#define dataport P2
//// number of instructions thought to be taking 1 millisecond
#define numb_instruc_milli 1275
//// declarations of the reset, enable and rw pin
sbit rs = P2^0;
sbit rw = P2^1;
sbit e = P2^2;

int x;

//// making the delay function
void delay(unsigned int msec)
{
	int i,j;
	for(i=0;i<msec;i++)
	{
		for(j=0;j<numb_instruc_milli;j++)
		{
		}
	}
}

//// Function to send command to the LCD
void send_cmd_lcd(unsigned char item)
{

	unsigned char a;
	
	
	//// sending higher 4 bits of the command
	a = item & 0xf0; 
	dataport = a;
	rs = 0; //// To specify that a command is being sent not Data
	rw = 0; //// since the LCD is always only display
	e = 1;
	delay(1);
	e = 0;
	
	
	
	//// sending the lower 4 bits of the command
	a = (item<<4)&0xf0;
	dataport = a;
	rs = 0; //// To specify that a command is being sent not Data
	rw = 0; //// since the LCD is always only display
	e = 1;
	delay(1);
	e = 0;
}

//// Function to send Data to LCD
void send_data_lcd(unsigned char item)
{
	unsigned char a;

	
	//// send the higher 4 bits of Data
	a = item & 0xf0;
	dataport = a;
	rs = 1;
	rw = 0;
	e = 1;
	delay(1);
	e = 0;
	
	
	
	//// sending the lower 4 bits of Data
 	a = (item<<4) & 0xf0;
	dataport = a;
	rs = 1;
	rw = 0;	
	e = 1;
	delay(1);
	e = 0;
}

//// sending more than one character of/data

void message(unsigned char *s)
{
	while(*s)
		send_data_lcd(*s++);
}

//// intializing LCD
void lcdinit()
{
	//// commands to say that we are in 4 bit mode
	send_cmd_lcd(0x33);
	send_cmd_lcd(0x32);
	send_cmd_lcd(0x28);

	send_cmd_lcd(0x06); //// display from left to right
	send_cmd_lcd(0x0C); //// display ON, cursor hide
	send_cmd_lcd(0x01); //// clear LCD
}

void main()
{
	lcdinit();
	send_cmd_lcd(0x80); //// Placind the Cursor at (0,0)
	message("Hello Abhigyan");
	delay(100);
	
	while(1)
	{
		send_cmd_lcd(0x01); //// clear LCD
		send_cmd_lcd(0x80); 
		message("Welcome to 8051");
		send_cmd_lcd(0xc0); //// placing cursor at (1,0)
		message("Microcontroller");
		delay(100);
		send_cmd_lcd(0x01);
		delay(100);
	}
}
