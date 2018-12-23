/*
 * alignToFrontWall.cpp
 *
 * Created: 1/26/2018 12:05:45 AM
 * Author : Lee
 */ 

#include <avr/io.h> //standard include for ATMega16
#include <avr/interrupt.h>
#include <stdlib.h>

#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "mainTimer.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "IRSensors.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "movement.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "communications.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item

void alignToFrontWallDEMO(void);


int main(void)
{ 
	RegisterInitialization();

	//uint16_t leftIRDiff = 0;
 	//uint16_t rightIRDiff = 0;
	//uint8_t leftMotorSpeed = 0;
	//uint8_t rightMotorSpeed = 0;
	//uint16_t oldLeftIRDiff = 0;
	//uint16_t oldRightIRDiff = 0;
	//uint16_t errorLeftIRDiff = 0;
	//uint16_t errorRightIRDiff = 0;
	//uint16_t PFrontwallAlign = 4;
	//uint16_t DFrontwallAlign = 4;
	alignToFrontWallDEMO();

    /* Replace with your application code */
	}
//
void alignToFrontWallDEMO(void)
{
    while (1)
    {
	timerInMilliseconds(1);

	leftIRDiff = IRSensorFrontLeft();
	//intToCharUart(leftIRDiff);

	if(	 leftIRDiff >= 942) //closer than
		{leftIRDiff = (leftIRDiff - 942);

			if(leftIRDiff < 20) // we are close enough... just stop
				{leftIRDiff = 0;
				oldLeftIRDiff = 0;
				};//breakWhileLoopCounter++;};//if oldLeftIRDiff is bigger than leftIRDiff, it puts a negative number into errorLeftIRDiff below

			if(leftIRDiff  > 50)// to fast... slow down
				leftIRDiff = 50;	

		errorLeftIRDiff = leftIRDiff - oldLeftIRDiff; //our differential, (Change of error distance )/(time between measurements)
		leftIRDiff =  (leftIRDiff/PFrontwallAlign) + (errorLeftIRDiff/DFrontwallAlign);
		oldLeftIRDiff = leftIRDiff;// for the next dx/dt
		leftMotorSpeed = 0xFF &  leftIRDiff; // make this an 8-bit for our PWM register 	
		//int8_tToCharUart(leftMotorSpeed);

		leftMotorRearward(leftMotorSpeed);
		//PIND = (1<<PORTD1);  // Pin changed - toggle an LED on PD0 ===green
		}
	else//(	 leftIRDiff < 942) //farther than
		{leftIRDiff = (942 - leftIRDiff);
			if (leftIRDiff < 20) // we are close enough... just stop
					{leftIRDiff = 0;
					 oldLeftIRDiff = 0;
					 };//breakWhileLoopCounter++;};//if oldLeftIRDiff is bigger than leftIRDiff, it puts a negative number into errorLeftIRDiff below
			if(leftIRDiff  > 50)
					leftIRDiff = 50;
			errorLeftIRDiff = leftIRDiff - oldLeftIRDiff; //our differential, (Change of error distance )/(time between measurements)
			leftIRDiff =  (leftIRDiff/PFrontwallAlign) + (errorLeftIRDiff/DFrontwallAlign);
			oldLeftIRDiff = leftIRDiff;// for the next dx/dt
			leftMotorSpeed = 0xFF &  leftIRDiff;// this is supposed to move the lower 8 bits into this uint_8
			leftMotorForward(leftMotorSpeed);
			//PIND = (1<<PORTD0);  // Pin changed - toggle an LED on PD0 ===blue
		};

		timerInMilliseconds(1);

		rightIRDiff = IRSensorFrontRight();
		//intToCharUart(rightIRDiff);

	if(	 rightIRDiff >= 942) //closer than
		{rightIRDiff = (rightIRDiff - 942);

			if(rightIRDiff < 20) // we are close enough... just stop
				{rightIRDiff = 0;
				 oldRightIRDiff = 0;
				 };//breakWhileLoopCounter++;};//if oldRightIRDiff is bigger than RightIRDiff, it puts a negative number into errorRightIRDiff below
			if(rightIRDiff  > 50)// to fast... slow down
			rightIRDiff = 50;

			errorRightIRDiff = rightIRDiff - oldRightIRDiff; //our differential, (Change of error distance )/(time between measurements)
			rightIRDiff =  (rightIRDiff/PFrontwallAlign) + (errorRightIRDiff/DFrontwallAlign);
			oldRightIRDiff = rightIRDiff;// for the next dx/dt
			rightMotorSpeed = 0xFF &  rightIRDiff;// this is supposed to move the lower 8 bits into this uint_8
			//int8_tToCharUart(rightMotorSpeed);

			rightMotorRearward(rightMotorSpeed);
			//PIND = (1<<PORTD1);  // Pin changed - toggle an LED on PD0 ===green
		}
		else//(	 rightIRDiff < 942) //farther than
		{rightIRDiff = (942 - rightIRDiff);
			if (rightIRDiff < 20) // we are close enough... just stop
				{rightIRDiff = 0;
				 oldRightIRDiff = 0;
				 };//breakWhileLoopCounter++;};
			if(rightIRDiff  > 50)
				rightIRDiff = 50;
			errorRightIRDiff = rightIRDiff - oldRightIRDiff;
			rightIRDiff =  (rightIRDiff/PFrontwallAlign) + (errorRightIRDiff/DFrontwallAlign);
			oldRightIRDiff = rightIRDiff;
			rightMotorSpeed = 0xFF &  rightIRDiff;// this is supposed to move the lower 8 bits into this uint_8
			rightMotorForward(rightMotorSpeed);//rightMotorSpeed);
			//PIND = (1<<PORTD0);  // Pin changed - toggle an LED on PD0 ===blue
		};
		//if (breakWhileLoopCounter > 50)
			//break;
	}
		//breakWhileLoopCounter = 0;
				leftMotorForward(0);
				rightMotorForward(0);//kill the motors
				//PIND = (1<<PORTD0);  // Pin changed - toggle an LED on PD0 ===blue
}

