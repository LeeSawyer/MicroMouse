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
	DDRB = 0x04;//Data Direction, sets bit 0 of portB to output , I don't think this is needed.
				//also 0x20 = 0b00100000 = (1 << DDRD5) = (1 << 5) = _BV(5) = 32
    TCCR1A = (1 << COM1B1) | (1 << WGM10);// TTTTimer/CCCCounter CCCControl RRRRegister AAAA: 
						// CCCCompare OOOOutput MMMMode for Channel B1: COM0B1=1, COM0B0=0, Clear OC0B on Compare Match.
						// WWWWaveform GGGGeneration MMMMode: WGM02=0, WGM01=1, WGM00=1,
								//Timer/Counter Mode of Operation: Fast PWM
								//TOP: 0xFF
								//Update of OCR0x at: BOTTOM
								//TOV Flag Set on: MAX
	TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12); // TTTTimer/CCCCounter CCCControl RRRRegister BBBB 
						//Clock Select 0
						//CA02+1, CS01=0, CS00=1: clkI/O/1024 (From prescaler)... /1024 is the fastest timer trigger setting

	int rightMotorRearwardSpeed = 0;
	OCR1B = rightMotorRearwardSpeed; // the number we compare to the counter	
	
	while(1)
    {				
		for(rightMotorRearwardSpeed=0;rightMotorRearwardSpeed<255;rightMotorRearwardSpeed = rightMotorRearwardSpeed + 5)
		{
				OCR1B = rightMotorRearwardSpeed;
				_delay_ms(500);
	
		}
		
		for(rightMotorRearwardSpeed=255;rightMotorRearwardSpeed>0;rightMotorRearwardSpeed = rightMotorRearwardSpeed - 5)
		{
			OCR1B = rightMotorRearwardSpeed;
			_delay_ms(500);
		}
	
    }
}


