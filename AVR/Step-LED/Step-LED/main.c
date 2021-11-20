#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define time 10

int main(void)
{
	int i=0;
    DDRD = 0xff;
	DDRC =0x00;
	PORTC = 0xff;  
    while (1) 
	{ 
		if((PINC & (1<<5)))
		{
			for (i=1;i<8;i+=2)
			{
				PORTD |=(1 << i);
				_delay_ms(time);
			}
			
			for (i=1;i<8;i+=2)
			{
				PORTD &= ~(1<<i);
				_delay_ms(time);
			}
			
			for (i=7;i>=0;i-=2)
			{
				PORTD |=(1<<i);
				_delay_ms(time);
			}
			
			for (i=7;i>=0;i-=2)
			{
				PORTD &=~(1<<i);
				_delay_ms(time);
			}
		}
		else
		{
			for (i=0;i<8;i+=2)
			{
				PORTD |=(1 << i);
				_delay_ms(time);
			}
			
			for (i=0;i<8;i+=2)
			{
				PORTD &= ~(1<<i);
				_delay_ms(time);
			}
			
			for (i=6;i>=0;i-=2)
			{
				PORTD |=(1<<i);
				_delay_ms(time);
			}
			
			for (i=6;i>=0;i-=2)
			{
				PORTD &=~(1<<i);
				_delay_ms(time);
			}
		}
		/*else
		{
			PORTD = (1<<PORTD5);
			_delay_ms(10);
			PORTD =(0<<PORTD5);
			_delay_ms(10);
		}*/
	}
		
}

