#define F_CPU 1000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h> 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#define BR 4800
#define BAUD ((F_CPU/16/BR)-1)
//#define step 5;
//#define PULSE 2500;

void initInterrupt()
{
	PCICR = (1<<PCIE1);					//ENABLING THE INTERRUPT FROM PINS IN BANK-C
	PCMSK1 = (1<<PCINT4);				//ENABLING THE INTERRUPT FROM PIN4 IN BANK-C
	sei();
}

void initTimer(void)
{
	TCCR1A = (1<<COM1A1) | (1<<WGM11);								//TO RESET OCR1A WHEN THE MATCH OCCURS
	TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS10);					//TO SET THE WGM TO FAST PWM	
	ICR1 = 20000;										//PROVIDED THAT A SINGLE TICK IS 1 MICROSECOND,20 MS IS SET AS 20000
	//DDRB = 0xff;										//SETTING THE OCIA PIN AS OUTPUT PIN
}

void initUART()
{
	UBRR0H = (BAUD >> 8);					//SETTING THE BAUD RATE	
	UBRR0L =  BAUD;							//SETTING THE BAUD RATE
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);       //ENABLING THE TRANSMITTER AND RECEIVER
	
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);     //SETTING THE CHARACTER SIZE TO BE 8-BIT
}

void tx(uint8_t byte)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = byte;
}

uint8_t rx(void)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

void servoCheck()
{
	int i=500;
	
	for (i=500; i<2500;i++)
	{
		PORTB = (1<<PINB1);
		_delay_us(i);
		PORTB = (0<<PINB1);
		_delay_us(25000-i);
	}
	
	for (i=2500; i>=000;i--)
	{
		PORTB = (1<<PINB1);
		_delay_us(i);
		PORTB = (0<<PINB1);
		_delay_us(25000-i);
	}	
}

int servoControl(int pos)
{
	char key;
	//int value;
	
	key = rx();
	tx(key);
	if(key == 0b01110111)					//w
	{
		PORTC = (1<<PINC5);
		TCNT1 = 0x0000;
		OCR1A = pos ;
		pos +=10;
		return pos;
		//_delay_ms(1000);
	}
	else if (key == 0b01110011)				//s
	{
		PORTC = (1<<PINC4);
		TCNT1 = 0x0000;
		OCR1A = pos;
		pos -= 10;
		return pos;
		//_delay_ms(1000);
	}
	else
	{
		PORTB = (1<<PINB3);
	}	
	return  pos;
}

int main(void)
{	
	int step = 10;
	initTimer();
	initUART();
	int lr = 1500;
	int ud = 1500;
	int ud2 = 1500;
	int max = 2500;
	int min = 100;
	uint8_t key;
	DDRB = 0xff;
	//DDRC = 0xff;	
    while (1) 
    {
		if(lr < min){lr=100;}
		else if (lr>max){lr=2500;}
		
		if (ud < min){ud=100;}
		else if (ud > max){ud = 2500;}	
			
		//value = servoControl(value);
		//servoCheck;
		key = rx();
		PORTC = key;
		
		switch (PORTC)
		{
			case (0b01100001):					//key a is pressed
			{	
				OCR1B = 65000;
				tx(key);			
				DDRB = (1<<PINB1);				//HORIZONTAL CONTROL SERVO IS CONNECTED TO PIN B1
				TCNT1 = 0x0000;
				OCR1A = lr;					
				lr+=step;
				break;
			}
			case (0b01100100):					//key d is pressed
			{
				OCR1B = 65000;
				tx(key);
				DDRB = (1<<PINB1);
				TCNT1 = 0x0000;
				OCR1A = lr;
				lr -=step;
				break;
			}
			case (0b01110111):					//key w is pressed
			{
				OCR1A = 65000;
				tx(key);
				DDRB = (1<<PINB2);				//VERTICAL CONTROL SERVO CONNECTED TO PIN B2
				TCNT1 = 0x0000;
				OCR1B = ud;
				ud+=step;
				break;
			}
			case (0b01110011):					//key s is pressed
			{
				OCR1A = 65000;
				tx(key);
				DDRB = (1<<PINB2);
				TCNT1 = 0x0000;
				OCR1B = ud;
				ud -=step;
				break;
			}
			case (0b00100000):					//SPACE IS PRESSED
			{
				PORTB |= (1<<PINB3);			//FINGER SERVO IS CONNECTED TO PINB3
				_delay_us(1500);
				PORTB &= ~(1<<PINB3);
				_delay_us(25000-1500);
				
				_delay_ms(1000);
				
				PORTB |= (1<<PINB3);
				_delay_us(500);
				PORTB &= ~(1<<PINB3);
				_delay_us(20000);
				break;	
			}
			case(0b01010111):					//CAPITAL W IS PRESSED 
			{
				PORTB |= (1<<PINB4);			//VERTICAL CONTROLLER 2 IS CONNECTED TO PIN-B4
				_delay_us(ud2);
				PORTB &= ~(1<<PINB4);
				_delay_us(25000-ud2);
				ud2+=10;
				break;
			}
			case(0b01010011):					//CAPITAL S IS PRESSED
			{
				PORTB |= (1<<PINB4);			
				_delay_us(ud2);
				PORTB &= ~(1<<PINB4);
				_delay_us(25000-ud2);
				ud2-=10;
				break;
			}
			
			default:
			{
				DDRB = 0x00;
				break;
			}
				
		}
		
    }
	return (0);
}

