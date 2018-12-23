/*
 *  Written in AVR Studio 5 / AVR Studio 6
 *  Compiler: AVR GNU C Compiler (GCC)
 *
 *  Author: AVR Tutorials
 *  Website: www.AVR-Tutorials.com
*/
 
//#include<avr/io.h>
 
int leftButton()
{
        if (PINC & (1<<PINC5))    // (1<<PINC2) is 00000100,PINC & 00000100 looks for button		
		return 1;
        else
		return 0;
}
 
int rightButton()
{
	//DDRC &= ~0b00100000;		//configure portB as input
	//DDRD = 0x03;		//configure portC as output
	//DDRD &= ~0b00000100;		//configure portC as output
	
	//while(1)
	//{
//		PORTD1 = PIND2;
        if (PIND & (1<<PIND2))    // (1<<PINC2) is 00000100,PINC & 00000100 looks for button	
		return 1;
		//PORTD |= (1<<PIND1);  // turn on LED
        else
		return 0;
	    //PORTD &= ~(1<<PIND1); // turn off LED
//		PORTD0 = PINC5;
//        if (PINC & (1<<PINC5))    // (1<<PINC2) is 00000100,PINC & 00000100 looks for button
//        PORTD |= (1<<PIND0);  // turn on LED
//        else
//        PORTD &= ~(1<<PIND0); // turn off LED
//	}
//	return 0;
}



//		if (leftButton())    // (1<<PINC2) is 00000100,PINC & 00000100 looks for button
//		PORTD |= (1<<PIND1);  // turn on LED
//		else
//		PORTD &= ~(1<<PIND1); // turn off LED

//        if (rightButton())    // (1<<PINC2) is 00000100,PINC & 00000100 looks for button
//        PORTD |= (1<<PIND0);  // turn on LED
//        else
//        PORTD &= ~(1<<PIND0); // turn off LED



