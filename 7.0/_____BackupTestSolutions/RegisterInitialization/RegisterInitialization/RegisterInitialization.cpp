/*
 * RegisterInitialization.cpp
 *
 * Created: 9/29/2017 3:51:39 AM
 * Author : Lee
 */ 

#define F_CPU 16000000UL //this has to be set for the 16Mhz external clock that is installed

#include <avr/io.h> //standard include for ATMega16
#include <util/delay.h>

int main(void)
{
	DDRC = 0b00011000; //port C3 front and port C4 diagonal
	//also 0x10 = 0b00010000 = (1 << DDB4) = (1 << 4) = _BV(4) = 16
	DDRD = 0b00000011; //port D 0 and 1, RX and TX LED


}

