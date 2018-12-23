/*
 * moveOneBlock.cpp
 *
 * Created: 2/1/2018 10:31:44 PM
 * Author : Lee
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

/* ///////////////////////////// moveWithPB 
//uint16_t leftWallSensorValue = 0;
//uint16_t rightWallSensorValue = 0;
//uint16_t hasLeftWall = 110;
//uint16_t hasRightWall = 110;
//uint16_t errorP = 0;
//uint16_t errorD = 0;
//uint16_t oldErrorP = 0;
//uint16_t leftMiddleValue = 182;
//uint16_t rightMiddleValue = 211;
//uint16_t totalError16 = 0;
//uint8_t totalError8 = 0;
//uint8_t leftBaseSpeed = 50;
//uint8_t rightBaseSpeed = 50;
//uint16_t Paway = 10;
//uint16_t Ptoward = 5;
//uint16_t D = 1;
//uint16_t errorMax = ((rightBaseSpeed - 5) * Paway);//this is the max difference between 255 or 0 and Base speed, * the Propotional divider 
//uint16_t testVariable = 0;// test variable
//uint16_t WordsOfData = 0;//used in EEPROM data
//
//void moveWithPD(void)
//{
	//if((leftWallSensorValue > hasLeftWall && rightWallSensorValue > hasRightWall))//has both walls
		//{  // **************** can not turn from unsigned int to int: 1) can't debug with excel, 2)
			//if(rightWallSensorValue > (leftWallSensorValue + 29))
				//{	errorP = rightWallSensorValue - leftWallSensorValue - 29;//29 is the offset between left and right sensor when mouse in the middle of cell
					//errorD = errorP - oldErrorP;
					//totalError16 =  errorP/Paway;// + D * errorD;
					//oldErrorP = errorP;
					//totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					//leftMotorForward(leftBaseSpeed + totalError8);
					//rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
			//}
			//else
				//{	errorP = (leftWallSensorValue + 29) - rightWallSensorValue;//29 is the offset between left and right sensor when mouse in the middle of cell
					//errorD = errorP - oldErrorP;
					//totalError16 =  errorP/Paway;// + D * errorD;
					//oldErrorP = errorP;
					//totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					//leftMotorForward(leftBaseSpeed + totalError8);
					//rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
			//}
		//}
	//else if((leftWallSensorValue > hasLeftWall))//only has left wall = 150
		//{
			//if (leftWallSensorValue > leftMiddleValue )// ************   has wall & > leftMiddleValue = 182, close, go right
				//{	errorP =  2 * (leftWallSensorValue - leftMiddleValue );//leftMiddleValue = 182
					//if (errorP > errorMax)// *  above this and the number gets to big
						//errorP = errorMax;
					//errorD = errorP - oldErrorP;
					//totalError16 =  errorP/Paway;// + D * errorD;
					//oldErrorP = errorP;
					//totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					//leftMotorForward(leftBaseSpeed + totalError8);
					//rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
					//PIND = (1<<PORTD1);  // Pin changed - toggle an LED on PD0 ===green
						////eeprom_update_word((uint16_t*)WordsOfData, (rightBaseSpeed - totalError8 +4));
						////WordsOfData++;
						////WordsOfData++;
			//} 
			//else// needs to go left, back towards the wall
				//{	errorP =  2 * (leftMiddleValue - leftWallSensorValue );//2 *
					//errorD = errorP - oldErrorP;
					//totalError16 =  errorP/Ptoward;// + D * errorD;
					//oldErrorP = errorP;
					//totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					//leftMotorForward(leftBaseSpeed - totalError8);
					//rightMotorForward(rightBaseSpeed + totalError8 +4);//+4 is to get rid of the slight right curve
					//PIND = (1<<PORTD0);  // Pin changed - toggle an LED on PD0 ===blue
			//}
		//}
	//else if((rightWallSensorValue > hasRightWall))//only has right wall
		//{
			//if (rightWallSensorValue > rightMiddleValue)
				//{	errorP = 2 * (rightWallSensorValue - rightMiddleValue);
					//if (errorP > errorMax)//  above this and the number gets to big
						//errorP = errorMax;
					//errorD = errorP - oldErrorP;
					//totalError16 =  errorP/Paway;// + D * errorD;
					//oldErrorP = errorP;
					//totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					//leftMotorForward(leftBaseSpeed - totalError8);
					//rightMotorForward(rightBaseSpeed + totalError8 +4);//+4 is to get rid of the slight right curve
			//} 
			//else// turn back right, toward the wall
				//{	errorP = 2 * (rightMiddleValue - rightWallSensorValue);
					//errorD = errorP - oldErrorP;
					//totalError16 =  errorP/Ptoward;// + D * errorD;
					//oldErrorP = errorP;
					//totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					//leftMotorForward(leftBaseSpeed + totalError8);
					//rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
//
			//}
		//}
	//else if((leftWallSensorValue < hasLeftWall && rightWallSensorValue < hasRightWall))//no wall, use encoder or gyro
		//{
					//errorP = 0;//(leftEncoder – rightEncoder*1005/1000)*3;
					//errorD = 0;
					//totalError16 =  errorP/Ptoward;// + D * errorD;
					//oldErrorP = errorP;
					//totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					//leftMotorForward(leftBaseSpeed + totalError8);
					//rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
		//};
//
//
//
	////timerInMilliseconds(1);
	////eeprom_update_word((uint16_t*)WordsOfData, 0x00000000);
	////WordsOfData++;
	////WordsOfData++;	
//
	////eeprom_update_word((uint16_t*)WordsOfData, totalError16);
	////WordsOfData++;
	////WordsOfData++;
	////eeprom_update_word((uint16_t*)WordsOfData, totalError8);
	////WordsOfData++; 
	////WordsOfData++;
//
	////eeprom_update_word((uint16_t*)WordsOfData, 0x0000 );
	////WordsOfData++;
	////WordsOfData++;
	/////////////////////////test data
	////testVariable++;
	////if (testVariable > 40)
	////{
	////testVariable = 0;
	////intToCharUart(leftWallSensorValue);
	////}
//}
//
//void moveOneBlock(void)
//{
	//for (int8_t x = 10; x < 50; x += 10)//accelerate
	//{
		//leftMotorForward(x);
		//rightMotorForward(x);
		//timerInMilliseconds(20);
	//}
	//rightEncoderAPos = 0;
	//while (rightEncoderAPos < 1200)
	//{
		//leftWallSensorValue = IRSensorAngleLeftLED();
		//rightWallSensorValue = IRSensorAngleRightLED();
		//moveWithPD();
		////leftMotorForward(leftBaseSpeed);//straight line test
		////rightMotorForward(rightBaseSpeed +4);//straight line test, +4 is to get rid of the slight right curve
//
		////timerInMilliseconds(20);
		////PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	//}
	//for (int8_t x = 40; x > 0; x -= 10)//decelerate
	//{
		//leftMotorForward(x + 19);// there is a drag to the left that the +19 is making up for, does a little zig-zag at the end
		//rightMotorForward(x);
		//timerInMilliseconds(20);
	//}
	//leftMotorForward(0);
	//rightMotorForward(0);
//}   */

int main(void)
{

	RegisterInitialization();

	while (800 > IRSensorFrontLeft()) //waits for left front sensor to be tripped by user to continue
	{
	timerInMilliseconds(1); 	
	}

	for (uint16_t i=0;i<1023;i++)// clear the data
	{
		eeprom_update_word((uint16_t*)i, 0x0000 );// has 1000 8-bit bytes, or 50
		i++;
	}

    //while (1) 
    //{ 

		timerInMilliseconds(1000); // this is the delay between sensor readings
		moveOneBlock();
		timerInMilliseconds(1000); // this is the delay between sensor readings
		moveOneBlock();
		timerInMilliseconds(1000); // this is the delay between sensor readings
		moveOneBlock();
		timerInMilliseconds(1000); // this is the delay between sensor readings
		moveOneBlock();
		timerInMilliseconds(1000); // this is the delay between sensor readings
		moveOneBlock();




		////eeprom_update_word((uint16_t*)WordsOfData, 0xFFFF);// data collector
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//moveOneBlock();
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//moveOneBlock();
//
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//leftEncoderTurn();
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//moveOneBlock();
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//leftEncoderTurn();
//
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//moveOneBlock();
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//moveOneBlock();
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//moveOneBlock();
//
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//leftEncoderTurn();
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//moveOneBlock();
		//timerInMilliseconds(1000); // this is the delay between sensor readings
		//leftEncoderTurn();

	
}

