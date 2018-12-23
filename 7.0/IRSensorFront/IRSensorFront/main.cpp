/*
 * IRSensorFront.c
 *
 * Created: 3/12/2015 10:12:51 PM
 *  Author: Lee Sawyer
 *
 *  This is for use on an 8-bit AVR Atmel micro controller. 
 *  It demonstrates use of an Analog-to-Digital Converter and outputs the value out the USART serial port
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>



#include "RegisterInitialization.cpp"// contains F-CPU definition
#include "mainTimer.cpp"// contains F-CPU definition
//#include <util/delay.h>// delay.h has to be after F-CPU... for some reason
#include "IRSensors.cpp"
#include "communications.cpp"



//void intToCharUart(uint16_t ADCValue);


int main(void)
{
	RegisterInitialization();
	uint16_t IRSensorValue;// ADC higher value
	
     while (1)
     {	

		//IRSensorValue = IRSensorFrontLeftNoLED();
		//intToCharUart(IRSensorValue);
		//IRSensorValue = IRSensorFrontRightNoLED();
		//intToCharUart(IRSensorValue);
		//IRSensorValue = IRSensorFrontLeftLED();
		//intToCharUart(IRSensorValue);
		//IRSensorValue = IRSensorFrontRightLED();
		//intToCharUart(IRSensorValue);
		//IRSensorValue = IRSensorAngleLeftNoLED();
		//intToCharUart(IRSensorValue);
		//IRSensorValue = IRSensorAngleRightNoLED();
		//intToCharUart(IRSensorValue);
		//IRSensorValue = IRSensorAngleLeftLED();
		//intToCharUart(IRSensorValue);
		//IRSensorValue = IRSensorAngleRightLED();
		IRSensorValue = IRSensorAngleLeftLED();
		intToCharUart(IRSensorValue);

		timerInMilliseconds(1);
		IRSensorValue = IRSensorAngleRightLED();
		intToCharUart(IRSensorValue);
		//UDR0 = 0x0A;

		timerInMilliseconds(1000);
     }
}



