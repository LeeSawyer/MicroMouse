/*
 * turns.cpp
 *
 * Created: 2/2/2018 2:07:28 AM
 * Author : Lee
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include <util/delay.h>
#include "IRSensors.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "movement.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item

volatile uint16_t gyroValue;// ADC higher value

uint16_t startADCConversion(void);

int main(void)
{

	RegisterInitialization();

    /* Replace with your application code */
    while (1) 
    {
		// check if the timer count reaches 124
		for(long unsigned int oneSecond =0; oneSecond  <= 10;oneSecond++)//(oneSecond  <= 10) and (TCNT2 <= 160) is 0.001 second
		{
			while (TCNT2 <= 160)
			{
				TCNT2++;// reset counter
			}
			TCNT2 = 0;// reset counter
		};
		leftMotorForward(50);
		rightMotorForward(100);
		gyroValue += startADCConversion();
		if (gyroValue > 900) //1700 one block
		{
			gyroValue = 0;
			//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
			break;
		}

	}
	leftMotorForward(0);
	rightMotorForward(0);
}

uint16_t startADCConversion()
{
	uint8_t theLow; // ADC lower value
	uint16_t gyroValue;// ADC higher value

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	theLow = ADCL; // ADC lower value
	gyroValue = ADCH <<8 | theLow;// ADC higher value

	return gyroValue;
}