#include <reg51.h>
#define dataport P2
//// number of instructions thought to be taking 1 millisecond
#define numb_instruc_milli 1275
//// declarations of the reset, enable and rw pin
sbit rs = P2^0;
sbit rw = P2^1;
sbit e = P2^2;

sbit IR1 = P1^6; //// Entry Gate Sensor
sbit IR2 = P1^7; //// Exit Gate Sensor

sbit lamp = P1^2; //// lamp pin
sbit AC1 = P1^0;
sbit AC2 = P1^1;

int count = 0; //// number of people in the room 
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

//// Function to display the count of people
void display_count()
{
		int tens; //// variable to store the tenth place of count as a character
	  int ones; //// variable to store the ones place of count as a charcter
		tens = (count/10) + 48;
	  ones = (count%10) + 48;
		send_cmd_lcd(0x80); 
		message("Count = ");
		send_cmd_lcd(0x89); //// display tens at the position (0,9) row column order
		send_data_lcd(tens);
		send_cmd_lcd(0x8a); //// display tens at the position (0,10) row column order
		send_data_lcd(ones);
}

//// Function changes variable count depending on the value of IR1 and IR2
void change_count()
{
	if(IR1 == 1)
	{
		count +=1;
	}
	if(IR2 == 1)
	{
		count -= 1;
	}
}
//// Function prints the initial messages
void initial_print()
{	
	lcdinit();
	send_cmd_lcd(0x80); //// Placind the Cursor at (0,0)
	message("Hello Abhigyan");
	delay(100);
	send_cmd_lcd(0x01); //// clear LCD	
}
//// Function to control lamp
void control_lamp()
{
	if(count >= 1)
	{
		lamp = 1;
	}
	else
	{
		lamp = 0;
	}
}
//// Function to control AC1;
void control_AC1()
{
	if(count >= 1)
	{
		AC1 = 1;
	}
	else
	{
		AC1 = 0;
	}
}

//// Function to control AC2;
void control_AC2()
{
	if(count >= 25)
	{
		AC2 = 1;
	}
	else
	{
		AC2 = 0;
	}
}
void display_load_status()
{
	send_cmd_lcd(0xC0);
	if(lamp == 0)
	{
		message("ALL_Loads_OFF___");
	}
	else
	{
		if(AC2 == 0)
		{
			message("AC1_&_Lamp_ON___");
		}
		else
		{
			message("All_ON__________");
		}
	}
}
void main()
{
	initial_print();
	while(1)
	{	
		change_count();
		display_count();
		control_lamp();
		control_AC1();
		control_AC2();
		display_load_status();
	
	}

}
