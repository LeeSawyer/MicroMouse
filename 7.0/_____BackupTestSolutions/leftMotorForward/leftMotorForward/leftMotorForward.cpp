/*
 * PWM practice 2.c
 *
 * Created: 8/31/2014 6:01:08 AM
 *  Author: cafehill
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	///////////////////////////////////////////__This is for the timer/counter 0
	DDRD = 0x40;//Data Direction, sets bit 0 of portB to output , I don't think this is needed.
	//also 0x40 = 0b01000000 = (1 << DDRD6) = (1 << 7) = _BV(7) = 64
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);// TTTTimer/CCCCounter CCCControl RRRRegister AAAA:
	// CCCCompare OOOOutput MMMMode for Channel B1: COM0B1=1, COM0B0=0, Clear OC0B on Compare Match.
	// WWWWaveform GGGGeneration MMMMode: WGM02=0, WGM01=1, WGM00=1,
	//Timer/Counter Mode of Operation: Fast PWM
	//TOP: 0xFF
	//Update of OCR0x at: BOTTOM
	//TOV Flag Set on: MAX,0xFF
	int leftMotorForwardSpeed = 0;
	OCR0A = leftMotorForwardSpeed; // the number we compare to the counter
	TCCR0B = (1 << CS02) | (1 << CS00); // TTTTimer/CCCCounter CCCControl RRRRegister BBBB
	//Clock Select 0
	//CA02+1, CS01=0, CS00=1: clkI/O/1024 (From prescaler)... /1024 is the fastest timer trigger setting
	
	
	while(1)
	{
		for(int leftMotorForwardSpeed=0;leftMotorForwardSpeed<255;leftMotorForwardSpeed = leftMotorForwardSpeed + 5)
		{
			OCR0A = leftMotorForwardSpeed;
			_delay_ms(500);
			
		}
		
		for(int leftMotorForwardSpeed=255;leftMotorForwardSpeed>0;leftMotorForwardSpeed = leftMotorForwardSpeed - 5)
		{
			OCR0A = leftMotorForwardSpeed;
			_delay_ms(500);
		}
		
	}
}


