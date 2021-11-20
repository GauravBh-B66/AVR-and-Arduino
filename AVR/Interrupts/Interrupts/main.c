/*
 * Interrupts.c
 *
 * Created: 2/17/2020 9:15:17 PM
 * Author : PC_KGSS
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


ISR (INT0_vect)
{
	if (PIND & (1<<2))
	{
		PORTB |= (1<<PINB7);
		//PORTB &= ~(1<<PINB6);
		//_delay_ms(200);
	}
	else
	{
		PORTB &= ~(1<<PINB7);
		//PORTB |= (1<<PINB6);
		//_delay_ms(200);
	}
}


void initInt0(void)
{
	EIMSK |= (1<<INT0);
	EICRA |= (1<<ISC00);
	sei();
}

int main(void)
{
    
	DDRB = 0xff;					//Port B as output port
	PORTD |= (1<<PIND2);			//Port D5 for taking the input from the push button switch.
	initInt0();
	
    while (1) 
    {
		_delay_ms(100);
		/*if (PIND & (1<<2))
		{
			PORTB |= (1<<PINB7);
			//PORTB &= ~(1<<PINB6);
			//_delay_ms(200);
		}
		else
		{
			PORTB &= ~(1<<PINB7);
			//PORTB |= (1<<PINB6);
			//_delay_ms(200);
		}*/
		PORTB ^= ( 1 << PINB6);			
    }
}

