#define F_CPU 1000000UL
#include <avr/io.h>
#include <uart.h>
#include <util/delay.h>
#define BUAD 4800
#define BSR ((F_CPU/16/BUAD)-1)

void initUart()
{
	UBRR0H = (BSR>>8);
	UBRR0L = BSR;									 /////// setting the baud rate
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);				//////// Enabling the transmitter and receiver
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);			//////// Setting the frame of 8 bit for character and 1 stop bit.	
}


void sendByte(uint8_t data)
{
	do 
	{
	} while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}


uint8_t receiveByte()
{
	do 
	{} while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}


int main(void)
{
	char share;
	DDRB = 0xff;
	initUart();	 
    while (1) 
    {
		share = receiveByte();
		sendByte(share);
		PORTB = share;
		
    }
	return (0);
}

