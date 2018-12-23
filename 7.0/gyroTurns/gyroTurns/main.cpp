/*
 * gyroTurns.cpp
 *
 * Created: 2/8/2018 12:44:11 PM
 * Author : Lee
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "mainTimer.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "IRSensors.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "communications.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "movement.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "RXTXLEDOnOff.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item

/* /
//uint16_t startGyroADCConversion()
//{
	//timerInMilliseconds(1);
	//ADMUX = 0x40;//|= 1<<REFS0;// | 0x41;//|= (1 << MUX0);// use #1 ADC, left angle        ;// mux 0 is gyro ,<- moved to where the other admux info is, 0x40 = 0b0100000 gyro ;//| _BV(ADLAR) ;//ASC  multiplexer register: REFS0: where the voltage reference is coming from
//
	//uint8_t theGyroLow; // ADC lower value
	//uint16_t functionGyroValue;// ADC higher value
//
	////ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	////while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
//
	//ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	//while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
//
	//theGyroLow = ADCL; // ADC lower value
	//functionGyroValue = ADCH <<8 | theGyroLow;// ADC higher value
	////if(functionGyroValue > 30) //closer than
	////greenRXLEDOn();
	//return functionGyroValue;
//}
//
///////////////////////align to front wall variables
//uint16_t gyroValue = 1;//1 is to get it into the while loop
//int16_t leftTurnValue = 2100;// 2400 for "x" mouse, 2100 for "o" mouse
//int16_t rightTurnValue = -2600;// 2400 for "x" mouse, -2200 for "o" mouse
//int16_t right180Value = -4500;// 4800 for "x" mouse, -4500 for "o" mouse
//uint8_t motorSpeed8Bit = 0;
//int16_t motorSpeed16Bit = 0;
//int16_t oldmotorSpeed = 0;
//int16_t errormotorSpeedDiff = 0;//6 is to get it into the while loop
//int16_t PGyroTurn = 50;//proportional coefficient
//int16_t DGyroTurn = 100;//derivative coefficient
//uint16_t gyroBreakWhileLoopCounter = 0;//derivative coefficient
//
//void leftGyroTurn()
//{
//
	//gyroBreakWhileLoopCounter = 0;
	//leftTurnValue = 2100;
//
	//rightMotorForward(50);
	//leftMotorRearward(50);
//
	//while (gyroBreakWhileLoopCounter < 100)
	//{
		///////////////////////////test @ 1800 left and  @ 2200 right
//
		//////if(functionGyroValue > 30) //closer than
		//////greenRXLEDOn();
		//gyroValue = startGyroADCConversion();//(301 -
//
		//if(gyroValue > 305) //turning left
		//{
			//leftTurnValue -= (gyroValue - 301);
		//}
//
		//if(gyroValue < 297) //turning right
		//{
			//leftTurnValue += (301 - gyroValue);
		//}
//
		////eeprom_update_word((uint16_t*)WordsOfData, leftTurnValue);
		////WordsOfData++;
		////WordsOfData++;
//
		//motorSpeed16Bit = leftTurnValue;
		//errormotorSpeedDiff = motorSpeed16Bit - oldmotorSpeed; //our differential, dTheda/dTime, (Change of error distance )/(time between measurements)
		//motorSpeed16Bit =  (motorSpeed16Bit/PGyroTurn) + (errormotorSpeedDiff/DGyroTurn);
		//oldmotorSpeed = motorSpeed16Bit;// for the next dTheda/dTime
//
		////intToCharUart(motorSpeed16Bit);
//
		//if(motorSpeed16Bit > 50)//clips the leftTurnValue to a usable PWM value, until close to 0
		//{
			//motorSpeed16Bit = 50;
			//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			//rightMotorForward(motorSpeed8Bit);
			//leftMotorRearward(motorSpeed8Bit);
		//}
//
		//if(motorSpeed16Bit < -50)//clips the leftTurnValu for when leftTurnValue overshoots 0, becomes negative and has to return to 0
		//{
			//motorSpeed16Bit = 50;
			//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			//leftMotorForward(motorSpeed8Bit);
			//rightMotorRearward(motorSpeed8Bit);
		//}
		//
//
		////intToCharUart(totalLeftTurnValue);
		//if((49 > motorSpeed16Bit) && (motorSpeed16Bit>(-49)))// >(-20)
		//{
			//if(motorSpeed8Bit > 0)//clips the leftTurnValue to a usable PWM value, until close to 0
			//{
				//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				//rightMotorForward(motorSpeed8Bit);
				//leftMotorRearward(motorSpeed8Bit);
			//}
//
			//if(motorSpeed8Bit < 0)//for when leftTurnValue overshoots 0, becomes negative and has to return to 0
			//{
				//motorSpeed16Bit = abs(motorSpeed16Bit);
				//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				//leftMotorForward(motorSpeed8Bit);
				//rightMotorRearward(motorSpeed8Bit);
			//}
		//}
//
//
		//if ((15 > motorSpeed16Bit) && (motorSpeed16Bit>(-15)))
		//{
			//gyroBreakWhileLoopCounter++;
		//}
//
		//timerInMilliseconds(7);// the bandwidth of LY3200 Gyro is 140Hz= 7ms
	//}
//
	//rightMotorForward(0);
	//leftMotorRearward(0);
//
//}
//
//void rightGyroTurn()
//{
//
	//gyroBreakWhileLoopCounter = 0;
	//rightTurnValue = -2600;
//
	//leftMotorForward(50);
	//rightMotorRearward(50);
//
	//while (gyroBreakWhileLoopCounter < 100)
	//{
		///////////////////////////test @ 1800 left and  @ 2200 right
//
		//////if(functionGyroValue > 30) //closer than
		//////greenRXLEDOn();
		//gyroValue = startGyroADCConversion();//(301 -
//
		//if(gyroValue > 305) //turning left
		//{
			//rightTurnValue -= (gyroValue - 301);
		//}
//
		//if(gyroValue < 297) //turning right
		//{
			//rightTurnValue += (301 - gyroValue);
		//}
//
		////eeprom_update_word((uint16_t*)WordsOfData, righttTurnValue);
		////WordsOfData++;
		////WordsOfData++;
//
		//motorSpeed16Bit = rightTurnValue;
		//errormotorSpeedDiff = motorSpeed16Bit - oldmotorSpeed; //our differential, dTheda/dTime, (Change of error distance )/(time between measurements)
		//motorSpeed16Bit =  (motorSpeed16Bit/PGyroTurn) + (errormotorSpeedDiff/DGyroTurn);
		//oldmotorSpeed = motorSpeed16Bit;// for the next dTheda/dTime
//
		////intToCharUart(totalLeftTurnValue);
//
		//if(motorSpeed16Bit > 50)//clips the leftTurnValue to a usable PWM value, until close to 0
		//{
			//motorSpeed16Bit = 50;
			//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			//rightMotorForward(motorSpeed8Bit);
			//leftMotorRearward(motorSpeed8Bit);
		//}
		//if(motorSpeed16Bit < -50)//clips the leftTurnValu for when leftTurnValue overshoots 0, becomes negative and has to return to 0
		//{
			//motorSpeed16Bit = 50;
			//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			//leftMotorForward(motorSpeed8Bit);
			//rightMotorRearward(motorSpeed8Bit);
		//}
		//
//
//
		//if((49 > motorSpeed16Bit) && (motorSpeed16Bit > -49))// >(-20)
		//{
			////greenRXLEDOn();
			//if(motorSpeed16Bit > 0)//clips the leftTurnValue to a usable PWM value, until close to 0
			//{
				//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				//rightMotorForward(motorSpeed8Bit);
				//leftMotorRearward(motorSpeed8Bit);
				////intToCharUart(motorSpeed16Bit);
			//}
			//if(motorSpeed16Bit < 0)//for when leftTurnValue overshoots 0, becomes negative and has to return to 0
			//{
				//motorSpeed16Bit = abs(motorSpeed16Bit);
				//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				//leftMotorForward(motorSpeed8Bit);
				//rightMotorRearward(motorSpeed8Bit);
			//}
		//}
//
//
		//if ((15 > motorSpeed16Bit) && (motorSpeed16Bit>(-15)))
		//{
			//gyroBreakWhileLoopCounter++;
		//}
//
		//timerInMilliseconds(7);// the bandwidth of LY3200 Gyro is 140Hz= 7ms
	//}
//
	//rightMotorForward(0);
	//leftMotorRearward(0);
//
//}
//
//
//void rightGyro180()
//{
//
	//gyroBreakWhileLoopCounter = 0;
	//right180Value = -4500;
//
	//leftMotorForward(50);
	//rightMotorRearward(50);
//
	//while (gyroBreakWhileLoopCounter < 100)
	//{
		///////////////////////////test @ 1800 left and  @ 2200 right
//
		//////if(functionGyroValue > 30) //closer than
		//////greenRXLEDOn();
		//gyroValue = startGyroADCConversion();//(301 -
//
		//if(gyroValue > 305) //turning left
		//{
			//right180Value -= (gyroValue - 301);
		//}
//
		//if(gyroValue < 297) //turning right
		//{
			//right180Value += (301 - gyroValue);
		//}
//
		////eeprom_update_word((uint16_t*)WordsOfData, righttTurnValue);
		////WordsOfData++;
		////WordsOfData++;
//
		//motorSpeed16Bit = right180Value;
		//errormotorSpeedDiff = motorSpeed16Bit - oldmotorSpeed; //our differential, dTheda/dTime, (Change of error distance )/(time between measurements)
		//motorSpeed16Bit =  (motorSpeed16Bit/PGyroTurn) + (errormotorSpeedDiff/DGyroTurn);
		//oldmotorSpeed = motorSpeed16Bit;// for the next dTheda/dTime
//
		////intToCharUart(totalLeftTurnValue);
//
		//if(motorSpeed16Bit > 50)//clips the leftTurnValue to a usable PWM value, until close to 0
		//{
			//motorSpeed16Bit = 50;
			//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			//rightMotorForward(motorSpeed8Bit);
			//leftMotorRearward(motorSpeed8Bit);
		//}
		//if(motorSpeed16Bit < -50)//clips the leftTurnValu for when leftTurnValue overshoots 0, becomes negative and has to return to 0
		//{
			//motorSpeed16Bit = 50;
			//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			//leftMotorForward(motorSpeed8Bit);
			//rightMotorRearward(motorSpeed8Bit);
		//}
		//
//
//
		//if((49 > motorSpeed16Bit) && (motorSpeed16Bit > -49))// >(-20)
		//{
			////greenRXLEDOn();
			//if(motorSpeed16Bit > 0)//clips the leftTurnValue to a usable PWM value, until close to 0
			//{
				//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				//rightMotorForward(motorSpeed8Bit);
				//leftMotorRearward(motorSpeed8Bit);
				////intToCharUart(motorSpeed16Bit);
			//}
			//if(motorSpeed16Bit < 0)//for when leftTurnValue overshoots 0, becomes negative and has to return to 0
			//{
				//motorSpeed16Bit = abs(motorSpeed16Bit);
				//motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				//leftMotorForward(motorSpeed8Bit);
				//rightMotorRearward(motorSpeed8Bit);
			//}
		//}
//
//
		//if ((15 > motorSpeed16Bit) && (motorSpeed16Bit>(-15)))
		//{
			//gyroBreakWhileLoopCounter++;
		//}
//
		//timerInMilliseconds(7);// the bandwidth of LY3200 Gyro is 140Hz= 7ms
	//}
//
	//rightMotorForward(0);
	//leftMotorRearward(0);
//
//}
//
/  */


int main(void)
{

	RegisterInitialization();

	while (800 > IRSensorFrontLeft()) //waits for left front sensor to be tripped by user to continue
	{
		timerInMilliseconds(10);
	}

	//uint16_t WordsOfData = 0;
	//for (uint16_t i=0;i<1023;i++)// clear the EEPROM data
	//{
		//eeprom_update_word((uint16_t*)i, 0x0000 );// has 1000 8-bit bytes, or 50
		//i++;
	//}

	while (1)
	{
	//moveOneBlock();
	//rightEncoderTurn();
	rightGyroTurn();
	timerInMilliseconds(5000);// the bandwidth of LY3200 Gyro is 140Hz= 7ms
	}

}

