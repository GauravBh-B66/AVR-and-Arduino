#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>


static inline void initADC0(void)
{
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADPS1) | (1<<ADPS0);
	ADCSRA |= (1<<ADEN); 
}

int main(void)
{
	uint8_t ledValue;
	uint16_t adcValue;
	uint8_t i;
	initADC0();
	DDRB = 0xff;
	
	while(1)
	{
		ADCSRA |= (1<<ADSC);
		do{}while((ADCSRA & (1<<ADSC)));
		adcValue = ADC;
		ledValue = (adcValue >> 7);
		PORTB = 0;
		for (i=0; i <=ledValue ; i++)
		{
			
			PORTB |= (1<<i);
			_delay_ms(10);
		}
		_delay_ms(50);
	}
	return (0);
	
}