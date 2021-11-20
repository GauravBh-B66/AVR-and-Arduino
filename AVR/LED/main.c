#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL
int i=0;


int main(void)
{
	DDRC=0b11111111;
	while (1)
	{
		while(i<=3)
		{
			PORTC = (1<<i);
			i++;
			_delay_ms(100);
		}
		while (i>=0)
		{
			PORTC= (1<<i);
			i--;
			_delay_ms(100);
		}
	}
	return 0;
}