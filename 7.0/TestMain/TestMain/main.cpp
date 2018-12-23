 /*
 * TestMain.cpp
 *
 * Created: 9/25/2017 6:33:59 AM
 * Author : Lee
 */ 
#include <avr/io.h> //standard include for ATMega16
#include <avr/interrupt.h>
#include <stdlib.h>

#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "RXTXLEDOnOff.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "mainTimer.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "communications.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
//#include <util/delay.h> // this changes you main clock speed, use "mainTimer.cpp", has to go after RegisterInitialization.cpp

int main(void)
{

	
	/* Replace with your application code */
	RegisterInitialization();
	while(1)
	{
	timerInMilliseconds(5000);
	greenRXLEDOff();
	uint8_tToBluetooth(9);
	timerInMilliseconds(1000);
	greenRXLEDOn();
	uint8_tToBluetooth(9);
	timerInMilliseconds(1000);	}
}

