/*
 * RXDemo.c
 *
 *  Author: L Sawyer
 */
 

#include <avr/io.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "RXTXLEDOnOff.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "mainTimer.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "communications.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "IRSensors.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "movement.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item

  
int main(void)
{
	RegisterInitialization();
    //UCSR0B |= (1 << RXEN0);						//Control and Status Register 0 B, enable Receiver/RX is 5v low, always 5v
     
    while(1)									//the infinite loop
    {
					//greenRXLEDOn();
					//timerInMilliseconds(200);
					//greenRXLEDOff();
					//timerInMilliseconds(200);

		switch (recievedChar)
		{
		case 102:								//102 is ASCII 'f', for "forward"
			forwardTimed();
			recievedChar = 0;
			break;
		case 98:								//98 is ASCII 'b', for "backward"
			rearwardTimed();
			recievedChar = 0;
			break;
		case 117:								//117 is ASCII 'u', for "u-turn"
			faceRearTimed();
			recievedChar = 0;
			break;		
		case 108:								//108 is ASCII 'l', for "left face"
			faceLeftTimed();
			recievedChar = 0;
			break;		
		case 114:								//114 is ASCII 'r', for "right face"
			faceRightTimed();
			recievedChar = 0;
			break;		
		default:
			break;
		}
    }
}
 
ISR(USART_RX_vect)								//Interrupt Service Routine, if data comes in on RX pin, this triggers
{
    recievedChar  = 114;//UDR0;
				greenRXLEDOn();
 				timerInMilliseconds(200);
 				greenRXLEDOff();
}