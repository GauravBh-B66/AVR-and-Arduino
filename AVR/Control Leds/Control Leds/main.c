#define F_CPU 1000000UL
#define LED_PORT PORTB
#define LED_DDR  DDRB
#define LED_PIN  PINB	

#define BAUD_RATE 4800
#define BR ((F_CPU/16/BAUD_RATE)-1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


static inline void pi_enable()
{
	PCICR  = (1<<PCIE1);
	PCMSK1 = 0xff;
	sei();
}

ISR (PCINT1_vect)
{
	if (PORTC == (0b01110111))          //w   0b01110111
	{
		sendChar('w');
		LED_PORT = (1<<PINB0) | (1<<PINB1);
		_delay_ms(10);
		PORTC = 0;
	}
	else if (PORTC == (0b01110011))     // s  0b01110011
	{
		sendChar('s');
		LED_PORT = (1<<PINB7) | (1<<PINB6);
		_delay_ms(10);
		PORTC = 0;
	}
	else if (PORTC == (0b01100100))    //d   0b01100100
	{
		sendChar('d');
		LED_PORT = (1<<PIND2) | (1<<PIND3);
		_delay_ms(10);
		PORTC = 0;
	}
	else if (PORTC == (0b01100001))    //a   0b01100110
	{
		sendChar('a');
		LED_PORT = (1<<PIND4) | (1<<PIND5);
		_delay_ms(10);
		PORTC = 0;
	}
	else
	{
		sendChar('n');
		PORTC = 0x00;
	}
	_delay_ms(50);
}


static inline void initUART()
{
	UBRR0H = (BR >> 8);          //SET THE BAUD RATE TO 4800
	UBRR0L = BR;
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);    // ENABLE THE TRANSMITTER AND RECEIVER
	
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);  // SETTING THE BIT CHARACTER SIZE TO BE 8 AND 1 STOP BIT
}


void sendChar(uint8_t data)
{
	do 
	{
	} while (!(UCSR0A &(1<<UDRE0)));
	UDR0 = data;
}


static inline uint8_t receiveChar()
{
	do{}while(!(UCSR0A & (1<<RXC0)));
		return UDR0;
} 




int main(void)
{
	
	LED_DDR  = 0xff;
	LED_PORT = 0x00;
	//pi_enable();
	initUART();
	
	
    while (1) 
    {
		_delay_ms(500);
		PORTB = 0x00;
		char data;
		data = receiveChar();
		sendChar(data);
		PORTC = data; 
			if (PORTC == (0b01110111))          //w   0b01110111
			{
				sendChar('w');
				LED_PORT = (1<<PINB0) | (1<<PINB1);
				_delay_ms(10);
			}
			else if (PORTC == (0b01110011))     // s  0b01110011
			{
				sendChar('s');
				LED_PORT = (1<<PINB7) | (1<<PINB6);
				_delay_ms(10);
			}
			else if (PORTC == (0b01100100))    //d   0b01100100
			{
				sendChar('d');
				LED_PORT = (1<<PIND2) | (1<<PIND3);
				_delay_ms(10);
			}
			else if (PORTC == (0b01100001))    //a   0b01100110
			{
				sendChar('a');
				LED_PORT = (1<<PIND4) | (1<<PIND5);
				_delay_ms(10);
			}
			else
			{
				sendChar('n');
				PORTC = 0x00;
			}
		_delay_ms(50);
    }
}

