/*
 * checkWalls.cpp
 *
 * Created: 1/25/2018 5:31:33 PM
 * Author : Lee
 */ 
#include <avr/io.h> //standard include for ATMega16
#include <avr/interrupt.h>
#include <stdlib.h>

#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "movement.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "IRSensors.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "RXTXLEDOnOff.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item

#include <util/delay.h>

int main(void)
{
	RegisterInitialization();
	    while (1) 
    {
      currentCellWalls = checkWalls();
		if (currentCellWalls == 0x07) //all walls
			{
			 RXLEDOn();
			 _delay_ms(500);
			 RXLEDOff();
 			 _delay_ms(100);
			RXLEDOn();
			_delay_ms(500);
			RXLEDOff();
			_delay_ms(100);
			RXLEDOn();
			_delay_ms(500);
			RXLEDOff();
			_delay_ms(1000);
			}
		else if (currentCellWalls == 0x06) //front and right walls
			{
			 RXLEDOn();
			 _delay_ms(100);
			 RXLEDOff();
			 _delay_ms(100);
			 RXLEDOn();
			 _delay_ms(500);
			 RXLEDOff();
			 _delay_ms(100);
			 RXLEDOn();
			 _delay_ms(500);
			 RXLEDOff();
			 _delay_ms(1000);			
			}
		else if (currentCellWalls == 0x05) //left and right walls
			{
			RXLEDOn();
			_delay_ms(500);
			RXLEDOff();
			_delay_ms(100);
			RXLEDOn();
			_delay_ms(100);
			RXLEDOff();
			_delay_ms(100);
			RXLEDOn();
			_delay_ms(500);
			RXLEDOff();
			_delay_ms(1000);		
			}
		else if (currentCellWalls == 0x06) //front and left walls
			{
			 RXLEDOn();
			 _delay_ms(500);
			 RXLEDOff();
			 _delay_ms(100);
			 RXLEDOn();
			 _delay_ms(500);
			 RXLEDOff();
			 _delay_ms(100);
			 RXLEDOn();
			 _delay_ms(100);
			 RXLEDOff();
			 _delay_ms(1000);			
			}
		else if (currentCellWalls == 0x04) //right wall
			{
			 RXLEDOn();
			 _delay_ms(100);
			 RXLEDOff();
			 _delay_ms(100);
			 RXLEDOn();
			 _delay_ms(100);
			 RXLEDOff();
			 _delay_ms(100);
			 RXLEDOn();
			 _delay_ms(500);
			 RXLEDOff();
			 _delay_ms(1000);			
			}
		else if (currentCellWalls == 0x01) //left walls
			{
			 RXLEDOn();
			 _delay_ms(500);
			 RXLEDOff();
			 _delay_ms(100);
			 RXLEDOn();
			 _delay_ms(100);
			 RXLEDOff();
			 _delay_ms(100);
			 RXLEDOn();
			 _delay_ms(100);
			 RXLEDOff();
			 _delay_ms(1000);			
			}
		else if (currentCellWalls == 0x02) //front walls
		{
			RXLEDOn();
			_delay_ms(100);
			RXLEDOff();
			_delay_ms(100);
			RXLEDOn();
			_delay_ms(500);
			RXLEDOff();
			_delay_ms(100);
			RXLEDOn();
			_delay_ms(100);
			RXLEDOff();
			_delay_ms(1000);
		}
		else if (currentCellWalls == 0x00) //no walls
		{
			RXLEDOn();
			_delay_ms(100);
			RXLEDOff();
			_delay_ms(100);
			RXLEDOn();
			_delay_ms(100);
			RXLEDOff();
			_delay_ms(100);
			RXLEDOn();
			_delay_ms(100);
			RXLEDOff();
			_delay_ms(1000);
		}
		else 
		{
			RXLEDOn();
			_delay_ms(100);
			RXLEDOff();
			_delay_ms(100);
			RXLEDOn();
			_delay_ms(100);
			RXLEDOff();
			_delay_ms(100);
			RXLEDOn();
			_delay_ms(100);
			RXLEDOff();
			_delay_ms(100);		
		};



	}
}

