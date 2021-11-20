#define F_CPU 1000000UL
#define BR 4800
#define BRC (F_CPU/16/BR)
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>


void initUSART(void) 
{											/* requires BAUD */
	UBRR0H = (BRC>>8);										/* defined in setbaud.h */
	UBRR0L = BRC;
																/* Enable USART transmitter/receiver */
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);						 /* 8 data bits, 1 stop bit */
}
void transmitByte(uint8_t data) {
																/* Wait for empty transmit buffer */
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;												/* send data */
}

uint8_t receiveByte(void) {
	loop_until_bit_is_set(UCSR0A, RXC0);						/* Wait for incoming data */
	return UDR0;												 /* return register value */
}
															// Example of a useful printing command
void printString(const char myString[]) {
	uint8_t i = 0;
	while (myString[i]) {
		transmitByte(myString[i]);
		i++;
	}
}

void initTimer (void)
{
	TCCR1B = (1<<CS11) | (1<<CS10);                       //This bit-set sets the prescalar to be 64.
	
}


int main(void)
{
	char byte;
	uint16_t timerValue;
	
	initUSART();
	initTimer();
	DDRB = 0xff;
	DDRC = 0x00;
	PORTC = (1<<PINC5);
	
	
	printString("\r\nReaction Timer:\r\n");
	printString("---------------\r\n");
	
    
	
    while (1) 
    {
		PORTB &= ~(1<<PINB0);                         //TURN OFF THE LED INITIALLY
		printString("Let's do it guych...\r\n");
		byte = receiveByte();
		printString("Get ready...\r\n");
		_delay_ms(1000);                   
		PORTB = (1<<PINB0);				   //LIGHT UP THE LED ONCE THE SETUP IS READY TO TAKE THE INPUT FROM THE USER
		if(!(PINC & (1 << PINC5)))
		{
			printString("Cheater\r\n");
			printString("-----------------\r\n");
		}
		else
		{
			TCNT1 = 0;
			do 
			{
			} while ((1<<PINC5) & PINC );
			timerValue = (TCNT1 >> 4);
		}
		transmitByte(timerValue);
		
		
    }
}

