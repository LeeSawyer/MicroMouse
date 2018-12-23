/*
 * externalInterupt.cpp
 *
 * Created: 3/7/2016 11:19:12 PM
 * Author : Lee
 */ 

/*
 *  Written in AVR Studio 5 / AVR Studio 6
 *  Compiler: AVR GNU C Compiler (GCC)
 *
 *  Author: AVR Tutorials
 *  Website: www.AVR-Tutorials.com
*/
 
#include <avr/io.h>
#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include <util/delay.h>
 
int main(void)
{ 
    // Output for an LED
    DDRD = (1<<PORTD0);
	RegisterInitialization();
    while(1)
    {
		if (rightEncoderAPos > 2900) //2900 one block
			{ 
				PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
				rightEncoderAPos = 0;
			}
    }
}


////Interrupt Service Routine for PCINT0/B0
//ISR(PCINT0_vect)
//{    
	//rightEncoderAPos++;
//}
//
//ISR(PCINT2_vect)
//{
	//rightEncoderAPos++;
//}