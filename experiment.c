#include <reg51.h>

sbit led = P2^0;
void delay(unsigned int milli_seconds)
{
	int i, j;
	for(i = 0;i<milli_seconds;i++)
	{
		for(j = 0; j<1275; j++);
	}
}

void main()
{
	led = 0;
	while(1)
	{
		led = 0;
		delay(100);
		led = 1;
		delay(100);
	}
}