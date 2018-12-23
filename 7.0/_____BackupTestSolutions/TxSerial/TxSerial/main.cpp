/*
 * txSerial.c
 *  Author: L Sawyer
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define F_CPU	16000000UL						//my external clock speed
#define BUAD	9600							//my RN42 Bluetooth rate, changed on RN42 from original 115200 
#define BRC		((F_CPU/16/BUAD) - 1)			//Baud Rate Calculator

#include <util/delay.h>

int main(void)
{
	UBRR0L = BRC;								//Baud rate low
	UCSR0B = (1 << TXEN0);						//Control and Status Register 0 B, enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);		//Control and Status Register 0 C, Character Size 8- Bit
	
    while(1)									//the infinite loop
    {		
		while ( !( UCSR0A & (1<<UDRE0)) );		// If USART Data Register is not Empty
			UDR0 = 102;							// sends the data 
		_delay_ms(2000);
    }
}
