/*
 * rxSerial.c
 *  Author: L Sawyer
 */
 
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU   16000000						//my external clock speed
#define BUAD    9600							//my RN42 Bluetooth rate, changed on RN42 from 115200 
#define BRC     ((F_CPU/16/BUAD) - 1)			//Baud Rate Calculator
#include <util/delay.h>
 
volatile uint8_t sentChar = 0;					//volatile allows for varable to be passed between ISR and INT MAIN
  
int main(void)
{
    UBRR0H = (BRC >> 8);						//Baud rate high
    UBRR0L =  BRC;								//Baud rate low
     
    UCSR0B = (1 << RXEN0)  | (1 << RXCIE0);		//Control and Status Register 0 B, enable Receiver, RX Complete Interrupt Enable 0
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);		//Control and Status Register 0 C, Character Size 8- Bit
     
    DDRC = (1 << PORTC3);						//Front LED
     
    sei();										//Global Interrupt Enable
     
    while(1)									//the infinite loop
    {

        if(sentChar == 102)						//if Char 'f' is our recived character
        {
			PORTC |= (1 << PORTC3);				//port C3 front LED on
			_delay_ms(200);
			PORTC &= ~(1 << PORTC3);			//port C3 front LED off
			sentChar = 0;
        }
    }
}
 
ISR(USART_RX_vect)								//Interrupt Service Routine, if data comes in on RX pin, this triggers
{
    sentChar  = UDR0;
}