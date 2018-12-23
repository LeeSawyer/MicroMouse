/*
 *  Written in AVR Studio 5 / AVR Studio 6
 *  Compiler: AVR GNU C Compiler (GCC)
 *
 *  Author: AVR Tutorials
 *  Website: www.AVR-Tutorials.com
*/
 
#include<avr/io.h>
 
int main()
{
	DDRC &= ~0b00100000;		//configure portB as input
	DDRD = 0x03;		//configure portC as output
	DDRD &= ~0b00000100;		//configure portC as output
	
 
	while(1)
	{
//		PORTD1 = PIND2;
        if (PIND & (1<<PIND2))    // (1<<PINC2) is 00000100,PINC & 00000100 looks for button
        PORTD |= (1<<PIND1);  // see comment #3, turn on
        else
        PORTD &= ~(1<<PIND1); // see comment #4, turn off
//		PORTD0 = PINC5;
        if (PINC & (1<<PINC5))    // (1<<PINC2) is 00000100,PINC & 00000100 looks for button
        PORTD |= (1<<PIND0);  // see comment #3, turn on
        else
        PORTD &= ~(1<<PIND0); // see comment #4, turn off
	}
	return 0;
}

// #include<avr/io.h>
// 
// int main()
// {
// 	DDRB = 0xFF;		//configure portB as input
// 	DDRC &= ~(1 << PINC2);        		//configure portC as output
// 	
// 	while(1)
// 	{
//         if (PINC & (1<<PINC2))    // (1<<PINC2) is 00000100,PINC & 00000100 looks for button
//         PORTB |= (1<<PINB2);  // see comment #3, turn on 
//         else
//         PORTB &= ~(1<<PINB2); // see comment #4, turn off
// 	}
// 	return 0;
// }


