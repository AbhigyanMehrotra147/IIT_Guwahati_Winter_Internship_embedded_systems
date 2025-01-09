#include <reg51.h>
#define dataport P1

sbit IR1 = P2^6;
sbit IR2 = P2^7;

sbit AC1 = P2^0;
sbit AC2 = P2^1;
sbit light = P2^2;

sbit rs = P1^0;
sbit rw = P1^1;
sbit e = P1^2;

int count = 0;
int state1 = 0;
int state2 = 0;
int pos = 0;

int x,a,b;


void delay(unsigned int msec)
{
	int i,j;
	for(i=0;i<msec;i+=1)
	{
		for(j=0;j<msec;j+=1)
		{}
	}
}

//// Funtion to send command to LCD
void lcd_cmd(unsigned char item)
{
	//// sending upper nibble
	unsigned char a;
	a = item & 0xf0;
	dataport = a;
	rs = 0;
	rw = 0;
	e = 1;
	delay(1);
	e = 0;
		
	//// sending lower nibble
	a = (item<<4) & 0xf0;
	dataport = a;
	rs = 0;
	rw = 0;
	e = 1;
	delay(1);
	e = 0;
}

//// Funtion to send Data to LCD
void lcd_data(unsigned char item)
{
	//// sending upper nibble
	unsigned char a;
	a = item & 0xf0;
	dataport = a;
	rs = 1;
	rw = 0;
	e = 1;
	delay(1);
	e = 0;
		
	//// sending lower nibble
	a = (item<<4) & 0xf0;
	dataport = a;
	rs = 1;
	rw = 0;
	e = 1;
	delay(1);
	e = 0;
}

//// Function to send more that one character at a time
void message(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
	}
}

void lcd_init()
{
	lcd_cmd(0x32);
	lcd_cmd(0x33);
	lcd_cmd(0x28);
	lcd_cmd(0x06);
	lcd_cmd(0x0C);
}


void main()
{
	IR1 = IR2 = 1;
	AC1 = 0;
	AC2 = 0;
	light = 0;
	lcd_init();
	lcd_cmd(0x80);/// command to postion cursor 
	message(" Load Control ");
	lcd_cmd(0xc0); /// command to position cursor
	message(" Device ");
	delay(100);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	message("Visitors=");
	lcd_cmd(0x89);


	while(1)
	{
		if(IR1==0 && IR2==1 && pos==0)
		{
			count+=1;
			a = ((count/10) + 48);
			b = ((count%10) + 48);
			lcd_cmd(0x89);
			lcd_data(a);
			lcd_cmd(0x8a);
			lcd_data(b);
			delay(100);
			pos=1;
			if (count >= 1 && state1 == 0)
			{
				AC1 = 1;
				AC2 = 0;
				light = 1;
				state1 = 1;
				lcd_cmd(0xC0);
				message("ON: AC-1 & Light");
			}
			else if (count < 1 && state1 == 0)
			{
				AC1 = 0;
				AC2 = 0;
				light = 0;
				state1 = 0;
				lcd_cmd(0xC0);
				message("OFF: All Loads");
			}
			else if (count > 25 && state2 == 0)
			{
				AC1 = 1;
				AC2 = 1;
				light = 1;
				state2 = 1;
				lcd_cmd(0xC0);
				message("ON: All Loads");
			}
			else if (count < 25 && state2 == 1)
			{
				AC1 = 1;
				AC2 = 0;
				light = 1;
				state1 = 0;
				lcd_cmd(0xC0);
				message("ON: AC-1 & Light");
			}
		}
		else if(IR1==1 && IR2==0 && pos==0)
		{
			count-=1;
			a = ((count/10) + 48);
			b = ((count%10) + 48);
			lcd_cmd(0x89);
			lcd_data(a);
			lcd_cmd(0x8a);
			lcd_data(b);
			delay(100);
			pos=1;
			if (count >= 1 && state1 == 0)
			{
				AC1 = 1;
				AC2 = 0;
				light = 1;
				state1 = 1;
				lcd_cmd(0xC0);
				message("ON: AC-1 & Light");
			}
			else if (count < 1 && state1 == 0)
			{
				AC1 = 0;
				AC2 = 0;
				light = 0;
				state1 = 0;
				lcd_cmd(0xC0);
				message("OFF: All Loads");
			}
			else if (count > 25 && state2 == 0)
			{
				AC1 = 1;
				AC2 = 1;
				light = 1;
				state2 = 1;
				lcd_cmd(0xC0);
				message("ON: All Loads");
			}
			else if (count < 25 && state2 == 1)
			{
				AC1 = 1;
				AC2 = 0;
				light = 1;
				state1 = 0;
				lcd_cmd(0xC0);
				message("ON: AC-1 & Light");
			}
		}
		else if(IR1==1 && IR2==1)
		{
			count = count;
			a = ((count/10) + 48);
			b = ((count%10) + 48);
			lcd_cmd(0x89);
			lcd_data(a);
			lcd_cmd(0x8a);
			lcd_data(b);
			delay(100);
			pos=1;
			if (count >= 1 && state1 == 0)
			{
				AC1 = 1;
				AC2 = 0;
				light = 1;
				state1 = 1;
				lcd_cmd(0xC0);
				message("ON: AC-1 & Light");
			}
			else if (count < 1 && state1 == 0)
			{
				AC1 = 0;
				AC2 = 0;
				light = 0;
				state1 = 0;
				lcd_cmd(0xC0);
				message("OFF: All Loads");
			}
			else if (count > 25 && state2 == 0)
			{
				AC1 = 1;
				AC2 = 1;
				light = 1;
				state2 = 1;
				lcd_cmd(0xC0);
				message("ON: All Loads");
			}
			else if (count < 25 && state2 == 1)
			{
				AC1 = 1;
				AC2 = 0;
				light = 1;
				state1 = 0;
				lcd_cmd(0xC0);
				message("ON: AC-1 & Light");
			}
		}
		else if(IR1==0 && IR2==0 && pos==0)
		{
			count+=1;
			a = ((count/10) + 48);
			b = ((count%10) + 48);
			lcd_cmd(0x89);
			lcd_data(a);
			lcd_cmd(0x8a);
			lcd_data(b);
			delay(100);
			pos=1;
			if (count >= 1 && state1 == 0)
			{
				AC1 = 1;
				AC2 = 0;
				light = 1;
				state1 = 1;
				lcd_cmd(0xC0);
				message("ON: AC-1 & Light");
			}
			else if (count < 1 && state1 == 0)
			{
				AC1 = 0;
				AC2 = 0;
				light = 0;
				state1 = 0;
				lcd_cmd(0xC0);
				message("OFF: All Loads");
			}
			else if (count > 25 && state2 == 0)
			{
				AC1 = 1;
				AC2 = 1;
				light = 1;
				state2 = 1;
				lcd_cmd(0xC0);
				message("ON: All Loads");
			}
			else if (count < 25 && state2 == 1)
			{
				AC1 = 1;
				AC2 = 0;
				light = 1;
				state1 = 0;
				lcd_cmd(0xC0);
				message("ON: AC-1 & Light");
			}
		}
	}
}