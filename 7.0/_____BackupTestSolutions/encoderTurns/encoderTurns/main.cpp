/*
 * encoderTurns.cpp
 *
 * Created: 2/15/2018 3:53:35 PM
 * Author : Lee
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "mainTimer.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "IRSensors.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "movement.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item

//void leftEncoderTurn(void)
//{
	//for (int8_t x = 10; x < 50; x += 10)//accelerate
	//{
	//leftMotorRearward(x);
	//rightMotorForward(x);
	//timerInMilliseconds(20);
	//}
	//rightEncoderAPos = 0;
    //while (rightEncoderAPos < 105)
    //{
	////timerInMilliseconds(50); // this is the delay between sensor readings
	//leftMotorRearward(50);
	//rightMotorForward(50);
		////timerInMilliseconds(5000);		
		////PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	//}
	//for (int8_t x = 50; x > 0; x -= 10)//accelerate
	//{
		//leftMotorRearward(x);
		//rightMotorForward(x);
		//timerInMilliseconds(20);
	//}
	//leftMotorRearward(0);
	//rightMotorForward(0);
	////break stop
	////rightMotoRearward(50);
	////leftMotorForward(50);
	////timerInMilliseconds(20);
	////rightMotorRearward(0);
	////leftMotorForward(0);
//}
//
//void rightEncoderTurn(void)
//{
	//for (int8_t x = 10; x < 50; x += 10)//accelerate
	//{
		//leftMotorForward(x);
		//rightMotorRearward(x);
		//timerInMilliseconds(20);
	//}
	//rightEncoderAPos = 0;
	//while (rightEncoderAPos < 105)
	//{
		////timerInMilliseconds(50); // this is the delay between sensor readings
		//leftMotorForward(50);
		//rightMotorRearward(50);
		////timerInMilliseconds(5000);
		////PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	//}
	//for (int8_t x = 50; x > 0; x -= 10)//accelerate
	//{
		//leftMotorForward(x);
		//rightMotorRearward(x);
		//timerInMilliseconds(20);
	//}
	//leftMotorForward(0);
	//rightMotorRearward(0);
	////break stop
	////rightMotorForward(50);
	////leftMotorRearward(50);
	////timerInMilliseconds(20);
	////rightMotorForward(0);
	////leftMotorRearward(0);
//}


//void rightEncoder180(void)
//{
//for (int8_t x = 10; x < 50; x += 10)//accelerate
//{
//leftMotorForward(x);
//rightMotorRearward(x);
//timerInMilliseconds(20);
//}
//rightEncoderAPos = 0;
//while (rightEncoderAPos < 530)
//{
////timerInMilliseconds(50); // this is the delay between sensor readings
//leftMotorForward(50);
//rightMotorRearward(50);
////timerInMilliseconds(5000);
////PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
//}
//for (int8_t x = 50; x > 0; x -= 10)//accelerate
//{
//leftMotorForward(x);
//rightMotorRearward(x);
//timerInMilliseconds(20);
//}
//leftMotorForward(0);
//rightMotorRearward(0);
////break stop
////rightMotorForward(50);
////leftMotorRearward(50);
////timerInMilliseconds(20);
////rightMotorForward(0);
////leftMotorRearward(0);
//}

int main(void)
{
	// Output for an LED
	//DDRD = (1<<PORTD0);
	RegisterInitialization();
    /* Replace with your application code */
    while (1) 
    { 
	timerInMilliseconds(2000);
	rightEncoderTurn();
	}
}
