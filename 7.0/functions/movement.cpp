/*
 * movement.cpp
 *
 * Created: 9/25/2017 6:33:59 AM
 * Author : Lee
 *
 * leftMotorForward(uint8_t leftMotorForwardSpeed);
 * leftMotorRearward(uint8_t leftMotorRearwardSpeed);
 * rightMotorForward(uint8_t rightMotorForwardSpeed);
 * rightMotorRearward(uint8_t rightMotorRearwardSpeed);
 *
 * faceRight(uint8_t motorSpeed);
 * faceLeft(uint8_t motorSpeed);
 * forward(uint8_t motorSpeed)
 * turnRight(uint8_t motorSpeed)
 * turnLeft(uint8_t motorSpeed)

 * faceRightTimed();
 * faceLeftTimed();
 * forwardTimed();
 * rearwardTimed();	
 * faceRearTimed();
 *
 * leftEncoderTurn();
 * rightEncoderTurn();
 * rightEncoder180();
 *
 * startGyroADCConversion()
 * leftGyroTurn()
 * rightGyroTurn()
 * rightGyro180()
 *
 * alignToFrontWall();
 *
 * moveWithPD();
 * moveOneBlock();
 * moveOneBlockContinuous();
 * startMoveOneBlock();
 * endMoveOneBlock();
 *
 */ 

//#define F_CPU 16000000UL //this has to be set for the 16Mhz external clock that is installed
//#include <avr/io.h> //standard include for ATMega16

//#include "Motor.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item




void leftMotorForward(uint8_t leftMotorForwardSpeed)//void)
{	OCR1A = 0;
	OCR0A = leftMotorForwardSpeed; 
}// the number we compare to the counter}

void leftMotorRearward(uint8_t leftMotorRearwardSpeed)//void)
{	OCR1A = leftMotorRearwardSpeed;
	OCR0A = 0;
 }// the number we compare to the counter}

void rightMotorForward(uint8_t rightMotorForwardSpeed)//void)
{	OCR1B = 0;
	OCR0B = rightMotorForwardSpeed; 
}// the number we compare to the counter}

void rightMotorRearward(uint8_t rightMotorRearwardSpeed)//void)
{	OCR1B = rightMotorRearwardSpeed; // the number we compare to the counter
	OCR0B = 0;
}	

void faceRight(uint8_t motorSpeed)
{
	leftMotorForward(motorSpeed);
	rightMotorRearward(motorSpeed);
}

void faceLeft(uint8_t motorSpeed)
{
	rightMotorForward(motorSpeed);
	leftMotorRearward(motorSpeed);
}

void forward(uint8_t motorSpeed)
{
	rightMotorForward(motorSpeed);
	leftMotorForward(motorSpeed);
}

void turnRight(uint8_t motorSpeed)
{
	leftMotorForward(motorSpeed);
	rightMotorForward(motorSpeed);
}

void turnLeft(uint8_t motorSpeed)
{
	leftMotorForward(motorSpeed);
	rightMotorForward(motorSpeed);
}
///////////////////////////////////////////////////////////////   timed movement functions
void faceRightTimed(void)		//this is timed for use without the gyro
{
	uint8_t motorSpeed = 120;
		leftMotorForward(motorSpeed);
		rightMotorRearward(motorSpeed);

		//_delay_ms(85);
		timerInMilliseconds(85);

		motorSpeed = 0;
		leftMotorForward(motorSpeed);
		rightMotorRearward(motorSpeed);
}

void faceLeftTimed(void)		//this is timed for use without the gyro
{
	uint8_t motorSpeed = 120;
	leftMotorRearward(motorSpeed);
	rightMotorForward(motorSpeed);

	//_delay_ms(85);
	timerInMilliseconds(85);

	motorSpeed = 0;
	leftMotorRearward(motorSpeed);
	rightMotorForward(motorSpeed);
}

void forwardTimed(void)		//this is timed for use without the encoder
{
	uint8_t motorSpeed = 120;
	leftMotorForward(motorSpeed);
	rightMotorForward(motorSpeed);

	//_delay_ms(170);
	timerInMilliseconds(170);

	motorSpeed = 0;
	leftMotorForward(motorSpeed);
	rightMotorForward(motorSpeed);
}

void rearwardTimed(void)		//this is timed for use without the encoder
{
	uint8_t motorSpeed = 120;
	leftMotorRearward(motorSpeed);
	rightMotorRearward(motorSpeed);

	//_delay_ms(170);
	timerInMilliseconds(170);

	motorSpeed = 0;
	leftMotorRearward(motorSpeed);
	rightMotorRearward(motorSpeed);
}

void faceRearTimed(void)		//this is timed for use without the gyro
{
	uint8_t motorSpeed = 120;
	leftMotorRearward(motorSpeed);
	rightMotorForward(motorSpeed);

	//_delay_ms(230);
	timerInMilliseconds(230);

	motorSpeed = 0;
	leftMotorRearward(motorSpeed);
	rightMotorForward(motorSpeed);
}


////////////////////////////////////////////////////////////////////// encoder functions
void leftEncoderTurn(void)
{
	for (int8_t x = 10; x < 50; x += 10)//accelerate
	{
		leftMotorRearward(x);
		rightMotorForward(x);
		timerInMilliseconds(20);
	}
	rightEncoderAPos = 0;
	while (rightEncoderAPos < 105)
	{
		//timerInMilliseconds(50); // this is the delay between sensor readings
		leftMotorRearward(50);
		rightMotorForward(50);
		//timerInMilliseconds(5000);
		//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	}
	for (int8_t x = 50; x > 0; x -= 10)//accelerate
	{
		leftMotorRearward(x);
		rightMotorForward(x);
		timerInMilliseconds(20);
	}
	leftMotorRearward(0);
	rightMotorForward(0);
	//break stop
	//rightMotoRearward(50);
	//leftMotorForward(50);
	//timerInMilliseconds(20);
	//rightMotorRearward(0);
	//leftMotorForward(0);
}

void rightEncoderTurn(void)
{
	for (int8_t x = 10; x < 50; x += 10)//accelerate
	{
		leftMotorForward(x);
		rightMotorRearward(x);
		timerInMilliseconds(20);
	}
	rightEncoderAPos = 0;
	while (rightEncoderAPos < 30)
	{
		//timerInMilliseconds(50); // this is the delay between sensor readings
		leftMotorForward(50);
		rightMotorRearward(50);
		//timerInMilliseconds(5000);
		//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	}
	for (int8_t x = 50; x > 0; x -= 10)//accelerate
	{
		leftMotorForward(x);
		rightMotorRearward(x);
		timerInMilliseconds(20);
	}
	leftMotorForward(0);
	rightMotorRearward(0);
	//break stop
	//rightMotorForward(50);
	//leftMotorRearward(50);
	//timerInMilliseconds(20);
	//rightMotorForward(0);
	//leftMotorRearward(0);
}

void rightEncoder180(void)
{
	for (int8_t x = 10; x < 50; x += 10)//accelerate
	{
		leftMotorForward(x);
		rightMotorRearward(x);
		timerInMilliseconds(20);
	}
	rightEncoderAPos = 0;
	while (rightEncoderAPos < 530)
	{
		//timerInMilliseconds(50); // this is the delay between sensor readings
		leftMotorForward(50);
		rightMotorRearward(50);
		//timerInMilliseconds(5000);
		//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	}
	for (int8_t x = 50; x > 0; x -= 10)//accelerate
	{
		leftMotorForward(x);
		rightMotorRearward(x);
		timerInMilliseconds(20);
	}
	leftMotorForward(0);
	rightMotorRearward(0);
	//break stop
	//rightMotorForward(50);
	//leftMotorRearward(50);
	//timerInMilliseconds(20);
	//rightMotorForward(0);
	//leftMotorRearward(0);
}

///////////////////////////////////////////////////////////////////////////// gyro movement functions


uint16_t startGyroADCConversion()
{
	timerInMilliseconds(1);
	ADMUX = 0x40;//|= 1<<REFS0;// | 0x41;//|= (1 << MUX0);// use #1 ADC, left angle        ;// mux 0 is gyro ,<- moved to where the other admux info is, 0x40 = 0b0100000 gyro ;//| _BV(ADLAR) ;//ASC  multiplexer register: REFS0: where the voltage reference is coming from

	uint8_t theGyroLow; // ADC lower value
	uint16_t functionGyroValue;// ADC higher value

	//ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	//while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	theGyroLow = ADCL; // ADC lower value
	functionGyroValue = ADCH <<8 | theGyroLow;// ADC higher value
	//if(functionGyroValue > 30) //closer than
	//greenRXLEDOn();
	return functionGyroValue;
}

/////////////////////align to front wall variables
uint16_t gyroValue = 1;//1 is to get it into the while loop
int16_t leftTurnValue = 2100;// 2400 for "x" mouse, 2100 for "o" mouse
int16_t rightTurnValue = -2200;// -2400 for "x" mouse, -2200 for "o" mouse
int16_t right180Value = -4500;// -4800 for "x" mouse, -4500 for "o" mouse
uint8_t motorSpeed8Bit = 0;
int16_t motorSpeed16Bit = 0;
int16_t oldmotorSpeed = 0;
int16_t errormotorSpeedDiff = 0;//6 is to get it into the while loop
int16_t PGyroTurn = 50;//proportional coefficient
int16_t DGyroTurn = 100;//derivative coefficient
uint16_t gyroBreakWhileLoopCounter = 0;//derivative coefficient

void leftGyroTurn()
{

	gyroBreakWhileLoopCounter = 0;
	leftTurnValue = 2100;

	rightMotorForward(50);
	leftMotorRearward(50);

	while (gyroBreakWhileLoopCounter < 100)
	{
		/////////////////////////test @ 1800 left and  @ 2200 right

		////if(functionGyroValue > 30) //closer than
		////greenRXLEDOn();
		gyroValue = startGyroADCConversion();//(301 -

		if(gyroValue > 305) //turning left
		{
			leftTurnValue -= (gyroValue - 301);
		}

		if(gyroValue < 297) //turning right
		{
			leftTurnValue += (301 - gyroValue);
		}

		//eeprom_update_word((uint16_t*)WordsOfData, leftTurnValue);
		//WordsOfData++;
		//WordsOfData++;

		motorSpeed16Bit = leftTurnValue;
		errormotorSpeedDiff = motorSpeed16Bit - oldmotorSpeed; //our differential, dTheda/dTime, (Change of error distance )/(time between measurements)
		motorSpeed16Bit =  (motorSpeed16Bit/PGyroTurn) + (errormotorSpeedDiff/DGyroTurn);
		oldmotorSpeed = motorSpeed16Bit;// for the next dTheda/dTime

		//intToCharUart(motorSpeed16Bit);

		if(motorSpeed16Bit > 50)//clips the leftTurnValue to a usable PWM value, until close to 0
		{
			motorSpeed16Bit = 50;
			motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			rightMotorForward(motorSpeed8Bit);
			leftMotorRearward(motorSpeed8Bit);
		}

		if(motorSpeed16Bit < -50)//clips the leftTurnValu for when leftTurnValue overshoots 0, becomes negative and has to return to 0
		{
			motorSpeed16Bit = 50;
			motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			leftMotorForward(motorSpeed8Bit);
			rightMotorRearward(motorSpeed8Bit);
		}
		

		//intToCharUart(totalLeftTurnValue);
		if((49 > motorSpeed16Bit) && (motorSpeed16Bit>(-49)))// >(-20)
		{
			if(motorSpeed8Bit > 0)//clips the leftTurnValue to a usable PWM value, until close to 0
			{
				motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				rightMotorForward(motorSpeed8Bit);
				leftMotorRearward(motorSpeed8Bit);
			}

			if(motorSpeed8Bit < 0)//for when leftTurnValue overshoots 0, becomes negative and has to return to 0
			{
				motorSpeed16Bit = abs(motorSpeed16Bit);
				motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				leftMotorForward(motorSpeed8Bit);
				rightMotorRearward(motorSpeed8Bit);
			}
		}


		if ((15 > motorSpeed16Bit) && (motorSpeed16Bit>(-15)))
		{
			gyroBreakWhileLoopCounter++;
		}

		timerInMilliseconds(7);// the bandwidth of LY3200 Gyro is 140Hz= 7ms
	}

	rightMotorForward(0);
	leftMotorRearward(0);

}

void rightGyroTurn()
{

	gyroBreakWhileLoopCounter = 0;
	rightTurnValue = -2600;

	leftMotorForward(50);
	rightMotorRearward(50);

	while (gyroBreakWhileLoopCounter < 100)
	{
		/////////////////////////test @ 1800 left and  @ 2200 right

		////if(functionGyroValue > 30) //closer than
		////greenRXLEDOn();
		gyroValue = startGyroADCConversion();//(301 -

		if(gyroValue > 305) //turning left
		{
			rightTurnValue -= (gyroValue - 301);
		}

		if(gyroValue < 297) //turning right
		{
			rightTurnValue += (301 - gyroValue);
		}

		//eeprom_update_word((uint16_t*)WordsOfData, righttTurnValue);
		//WordsOfData++;
		//WordsOfData++;

		motorSpeed16Bit = rightTurnValue;
		errormotorSpeedDiff = motorSpeed16Bit - oldmotorSpeed; //our differential, dTheda/dTime, (Change of error distance )/(time between measurements)
		motorSpeed16Bit =  (motorSpeed16Bit/PGyroTurn) + (errormotorSpeedDiff/DGyroTurn);
		oldmotorSpeed = motorSpeed16Bit;// for the next dTheda/dTime

		//intToCharUart(totalLeftTurnValue);

		if(motorSpeed16Bit > 50)//clips the leftTurnValue to a usable PWM value, until close to 0
		{
			motorSpeed16Bit = 50;
			motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			rightMotorForward(motorSpeed8Bit);
			leftMotorRearward(motorSpeed8Bit);
		}
		if(motorSpeed16Bit < -50)//clips the leftTurnValu for when leftTurnValue overshoots 0, becomes negative and has to return to 0
		{
			motorSpeed16Bit = 50;
			motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			leftMotorForward(motorSpeed8Bit);
			rightMotorRearward(motorSpeed8Bit);
		}
		


		if((49 > motorSpeed16Bit) && (motorSpeed16Bit > -49))// >(-20)
		{
			//greenRXLEDOn();
			if(motorSpeed16Bit > 0)//clips the leftTurnValue to a usable PWM value, until close to 0
			{
				motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				rightMotorForward(motorSpeed8Bit);
				leftMotorRearward(motorSpeed8Bit);
				//intToCharUart(motorSpeed16Bit);
			}
			if(motorSpeed16Bit < 0)//for when leftTurnValue overshoots 0, becomes negative and has to return to 0
			{
				motorSpeed16Bit = abs(motorSpeed16Bit);
				motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				leftMotorForward(motorSpeed8Bit);
				rightMotorRearward(motorSpeed8Bit);
			}
		}


		if ((15 > motorSpeed16Bit) && (motorSpeed16Bit>(-15)))
		{
			gyroBreakWhileLoopCounter++;
		}

		timerInMilliseconds(7);// the bandwidth of LY3200 Gyro is 140Hz= 7ms
	}

	rightMotorForward(0);
	leftMotorRearward(0);

}

void rightGyro180()
{

	gyroBreakWhileLoopCounter = 0;
	right180Value = -4500;

	leftMotorForward(50);
	rightMotorRearward(50);

	while (gyroBreakWhileLoopCounter < 100)
	{
		/////////////////////////test @ 1800 left and  @ 2200 right

		////if(functionGyroValue > 30) //closer than
		////greenRXLEDOn();
		gyroValue = startGyroADCConversion();//(301 -

		if(gyroValue > 305) //turning left
		{
			right180Value -= (gyroValue - 301);
		}

		if(gyroValue < 297) //turning right
		{
			right180Value += (301 - gyroValue);
		}

		//eeprom_update_word((uint16_t*)WordsOfData, righttTurnValue);
		//WordsOfData++;
		//WordsOfData++;

		motorSpeed16Bit = right180Value;
		errormotorSpeedDiff = motorSpeed16Bit - oldmotorSpeed; //our differential, dTheda/dTime, (Change of error distance )/(time between measurements)
		motorSpeed16Bit =  (motorSpeed16Bit/PGyroTurn) + (errormotorSpeedDiff/DGyroTurn);
		oldmotorSpeed = motorSpeed16Bit;// for the next dTheda/dTime

		//intToCharUart(totalLeftTurnValue);

		if(motorSpeed16Bit > 50)//clips the leftTurnValue to a usable PWM value, until close to 0
		{
			motorSpeed16Bit = 50;
			motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			rightMotorForward(motorSpeed8Bit);
			leftMotorRearward(motorSpeed8Bit);
		}
		if(motorSpeed16Bit < -50)//clips the leftTurnValu for when leftTurnValue overshoots 0, becomes negative and has to return to 0
		{
			motorSpeed16Bit = 50;
			motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
			leftMotorForward(motorSpeed8Bit);
			rightMotorRearward(motorSpeed8Bit);
		}
		


		if((49 > motorSpeed16Bit) && (motorSpeed16Bit > -49))// >(-20)
		{
			//greenRXLEDOn();
			if(motorSpeed16Bit > 0)//clips the leftTurnValue to a usable PWM value, until close to 0
			{
				motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				rightMotorForward(motorSpeed8Bit);
				leftMotorRearward(motorSpeed8Bit);
				//intToCharUart(motorSpeed16Bit);
			}
			if(motorSpeed16Bit < 0)//for when leftTurnValue overshoots 0, becomes negative and has to return to 0
			{
				motorSpeed16Bit = abs(motorSpeed16Bit);
				motorSpeed8Bit = 0xFF &  motorSpeed16Bit;// this is supposed to move the lower 8 bits into this uint_8
				leftMotorForward(motorSpeed8Bit);
				rightMotorRearward(motorSpeed8Bit);
			}
		}


		if ((15 > motorSpeed16Bit) && (motorSpeed16Bit>(-15)))
		{
			gyroBreakWhileLoopCounter++;
		}

		timerInMilliseconds(7);// the bandwidth of LY3200 Gyro is 140Hz= 7ms
	}

	rightMotorForward(0);
	leftMotorRearward(0);

}

///////////////////////////////////////////////////////////////////////////// align to front wall variables
uint16_t leftIRDiff = 1;//1 is to get it into the while loop
uint16_t rightIRDiff = 1;
uint8_t leftMotorSpeed = 0;
uint8_t rightMotorSpeed = 0;
uint16_t oldLeftIRDiff = 0;
uint16_t oldRightIRDiff = 0;
uint16_t errorLeftIRDiff = 0;//6 is to get it into the while loop
uint16_t errorRightIRDiff = 0;
uint16_t PFrontwallAlign = 2;//proportional coefficient
uint16_t DFrontwallAlign = 2;//derivative coefficient
uint16_t breakWhileLoopCounter = 0;//derivative coefficient


void alignToFrontWall(void)
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
			breakWhileLoopCounter++;};//if oldLeftIRDiff is bigger than leftIRDiff, it puts a negative number into errorLeftIRDiff below

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
			breakWhileLoopCounter++;};//if oldLeftIRDiff is bigger than leftIRDiff, it puts a negative number into errorLeftIRDiff below
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
			breakWhileLoopCounter++;};//if oldRightIRDiff is bigger than RightIRDiff, it puts a negative number into errorRightIRDiff below
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
			breakWhileLoopCounter++;};
			if(rightIRDiff  > 50)
			rightIRDiff = 50;
			errorRightIRDiff = rightIRDiff - oldRightIRDiff;
			rightIRDiff =  (rightIRDiff/PFrontwallAlign) + (errorRightIRDiff/DFrontwallAlign);
			oldRightIRDiff = rightIRDiff;
			rightMotorSpeed = 0xFF &  rightIRDiff;// this is supposed to move the lower 8 bits into this uint_8
			rightMotorForward(rightMotorSpeed);//rightMotorSpeed);
			//PIND = (1<<PORTD0);  // Pin changed - toggle an LED on PD0 ===blue
		};
		if (breakWhileLoopCounter > 50)
		break;
	}

	leftMotorForward(0);
	rightMotorForward(0);//kill the motors
	breakWhileLoopCounter = 0;

	//PIND = (1<<PORTD0);  // Pin changed - toggle an LED on PD0 ===blue
}





////////////////////////////////////////////////////////////////////////// move with PB functions
uint16_t leftWallSensorValue = 0;
uint16_t rightWallSensorValue = 0;
uint16_t hasLeftWall = 110;// change with different light
uint16_t hasRightWall = 110;// change with different light
uint16_t errorP = 0;
uint16_t errorD = 0;
uint16_t oldErrorP = 0;
uint16_t leftMiddleValue = 164;//change with different light
uint16_t rightMiddleValue = 172;// change with different light
uint16_t totalError16 = 0;
uint8_t totalError8 = 0;
uint8_t leftBaseSpeed = 50;
uint8_t rightBaseSpeed = 50;
uint16_t Paway = 2;// P coefficient// change with different light
uint16_t Ptoward = 2;// change with different light
uint16_t Daway = 2;// change with different light
uint16_t Dtoward = 2;// change with different light
uint16_t errorMax = ((rightBaseSpeed - 5) * Paway);//this is the max difference between 255 or 0 and Base speed, * the Propotional divider
uint16_t testVariable = 0;// test variable
uint16_t WordsOfData = 0;//used in EEPROM data


void moveWithPD(void)// when turning, do left wall only, then right wall only, before doing both/two walls
{
	//if ((leftWallSensorValue > hasLeftWall) && (rightWallSensorValue > hasRightWall))//has both walls
		//{  //**************** can not turn from u_int to int: 1) can't debug with excel, 2)
 				////intToCharUart(leftWallSensorValue);
						////timerInMilliseconds(1);
 				////intToCharUart(rightWallSensorValue);
						////timerInMilliseconds(1);
 				////intToCharUart(0xFFF);
						////timerInMilliseconds(1);
//
			////////////////////////////////////////////////////////////////// using right wall
			//if (rightWallSensorValue > rightMiddleValue)
			//{	errorP = 2 * (rightWallSensorValue - rightMiddleValue);
				//if (errorP > errorMax)//  above this and the number gets to big
				//errorP = errorMax;
				//errorD = errorP - oldErrorP;
				//totalError16 = (errorP/Paway) + (errorD/D);
				//oldErrorP = errorP;
				//totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
				//leftMotorForward(leftBaseSpeed - totalError8);
				//rightMotorForward(rightBaseSpeed + totalError8 +4);//+4 is to get rid of the slight right curve
			//}
			//else// turn back right, toward the wall
			//{	errorP = 2 * (rightMiddleValue - rightWallSensorValue);
				//if (errorP > errorMax)//  above this and the number gets to big
				//errorP = errorMax;
				//errorD = errorP - oldErrorP;
				//totalError16 = (errorP/Ptoward) + (errorD/D);
				//oldErrorP = errorP;
				//totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
				//leftMotorForward(leftBaseSpeed + totalError8);
				//rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
			//}
//
			/////////////////////////////////////////////////////////////////////// using left wall
			////if (leftWallSensorValue > leftMiddleValue )//************   has wall & > leftMiddleValue = 182, close, go right
				////{	errorP =  2 * (leftWallSensorValue - leftMiddleValue );//leftMiddleValue = 182
					////if (errorP > errorMax)//  above this and the number gets to big
						////errorP = errorMax;
					////errorD = errorP - oldErrorP;
					////totalError16 = (errorP/Paway) + (errorD/D);
					////oldErrorP = errorP;
					////totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					////leftMotorForward(leftBaseSpeed + totalError8);
					////rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
					//////PIND = (1<<PORTD1);  // Pin changed - toggle an LED on PD0 ===green
						//////eeprom_update_word((uint16_t*)WordsOfData, leftWallSensorValue);// data collector
						//////WordsOfData++;
						//////WordsOfData++;
			////} 
			////else// needs to go left, back towards the wall
				////{	errorP =  2 * (leftMiddleValue - leftWallSensorValue );//2 *
					////if (errorP > errorMax)//  above this and the number gets to big
						////errorP = errorMax;
					////errorD = errorP - oldErrorP;
					////totalError16 = (errorP/Paway) + (errorD/D);
					////oldErrorP = errorP;
					////totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					////leftMotorForward(leftBaseSpeed - totalError8);
					////rightMotorForward(rightBaseSpeed + totalError8 +4);//+4 is to get rid of the slight right curve
					//////PIND = (1<<PORTD0);  // Pin changed - toggle an LED on PD0 ===blue
			////}
//
			///////////////////////////////////////////////////////////////////////////////// using both walls
			////if(rightWallSensorValue > (leftWallSensorValue - 5))
				////{	errorP = rightWallSensorValue - (leftWallSensorValue - 5);//10 is the offset between left and right sensor when mouse in the middle of cell
					////if (errorP > errorMax)//  above this and the number gets to big
						////errorP = errorMax;
					////errorD = errorP - oldErrorP;
					////totalError16 = (errorP/Paway) + (errorD/D);
					////oldErrorP = errorP;
					////totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					////leftMotorForward(leftBaseSpeed + totalError8);
					////rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
			////}
			////else
				////{	errorP = (leftWallSensorValue - 10) - rightWallSensorValue;//10 is the offset between left and right sensor when mouse in the middle of cell
					////if (errorP > errorMax)//  above this and the number gets to big
						////errorP = errorMax;
					////errorD = errorP - oldErrorP;
					////totalError16 = (errorP/Paway) + (errorD/D);
					////oldErrorP = errorP;
					////totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					////leftMotorForward(leftBaseSpeed + totalError8);
					////rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
			////}
		//}
//
		//else 
		if((leftWallSensorValue > hasLeftWall))//only has left wall 
		{
			if (leftWallSensorValue > leftMiddleValue )//////////////////////////// closer than center, turn away, sensor distance increases quickly, but value drops off slower
				{	errorP =  2 * (leftWallSensorValue - leftMiddleValue );//leftMiddleValue = 182
					if (errorP  > oldErrorP)
					{
						errorD = errorP  - oldErrorP;
					}
					else
					{
						errorD = oldErrorP  - errorP;
					}
					errorD = errorP - oldErrorP;
					totalError16 = (errorP/Paway) + (errorD/Daway);
					oldErrorP = errorP;
					if (totalError16 > (leftBaseSpeed/2))//  clipping it
						totalError16 = (leftBaseSpeed/2);
					totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					leftMotorForward(leftBaseSpeed + totalError8);
					rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
					//PIND = (1<<PORTD1);  // Pin changed - toggle an LED on PD0 ===green
						//eeprom_update_word((uint16_t*)WordsOfData, leftWallSensorValue);// data collector
						//WordsOfData++;
						//WordsOfData++;
			} 
			else/////////////////////////////////////////////////////////////////// turn back right, toward the wall, sensor distance decreases slower, but value jumps up quickly
				{	errorP =  2 * (leftMiddleValue - leftWallSensorValue );//2 *
					if (errorP  > oldErrorP)
					{
						errorD = errorP  - oldErrorP;
					}
					else
					{
						errorD = oldErrorP  - errorP;
					}
					totalError16 = (errorP/Ptoward) + (errorD/Dtoward);
					oldErrorP = errorP;
					if (totalError16 > (leftBaseSpeed/2))//  clipping it
						totalError16 = (leftBaseSpeed/2);
					totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					leftMotorForward(leftBaseSpeed - totalError8);
					rightMotorForward(rightBaseSpeed + totalError8 +4);//+4 is to get rid of the slight right curve
					//PIND = (1<<PORTD0);  // Pin changed - toggle an LED on PD0 ===blue
			}
// 				intToCharUart(leftWallSensorValue);

		}

		else 	if((rightWallSensorValue > hasRightWall))//only has right wall
		{
			if (rightWallSensorValue > rightMiddleValue)//////////////////////////// closer than center, turn away, sensor distance increases quickly, but value drops off slower
				{	
					errorP = 2 * (rightWallSensorValue - rightMiddleValue);
					if (errorP  > oldErrorP)
					{
						errorD = errorP  - oldErrorP;
					}
					else
					{
						errorD = oldErrorP  - errorP;						
					}
					totalError16 = (errorP/Paway) + (errorD/Daway);
					oldErrorP = errorP;
					if (totalError16 > (leftBaseSpeed/2))//  clipping it
						totalError16 = (leftBaseSpeed/2);
					totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					leftMotorForward(leftBaseSpeed - totalError8);
					rightMotorForward(rightBaseSpeed + totalError8 +4);//+4 is to get rid of the slight right curve
				} 
			else/////////////////////////////////////////////////////////////////// turn back right, toward the wall, sensor distance decreases slower, but value jumps up quickly
				{
					errorP = 2 * (rightMiddleValue - rightWallSensorValue);
					if (errorP  > oldErrorP)
					{
						errorD = errorP  - oldErrorP;
					}
					else
					{
						errorD = oldErrorP  - errorP;
					}
					totalError16 = (errorP/Ptoward) + (errorD/Dtoward);
					oldErrorP = errorP;
					if (totalError16 > (leftBaseSpeed/2))//  clipping it
						totalError16 = (leftBaseSpeed/2);
					totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					leftMotorForward(leftBaseSpeed + totalError8);
					rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve

				}
		}

	else if((leftWallSensorValue < hasLeftWall && rightWallSensorValue < hasRightWall))//no wall, use encoder or gyro
		{
					errorP = 0;//(leftEncoder – rightEncoder*1005/1000)*3;
					errorD = 0;
					totalError16 = (errorP/Paway) + (errorD/Daway);
					oldErrorP = errorP;
					totalError8 = 0xFF & totalError16;// this is supposed to move the lower 8 bits into this uint_8
					leftMotorForward(leftBaseSpeed + totalError8);
					rightMotorForward(rightBaseSpeed - totalError8 +4);//+4 is to get rid of the slight right curve
		};



	//timerInMilliseconds(1);
	//eeprom_update_word((uint16_t*)WordsOfData, 0x00000000);
	//WordsOfData++;
	//WordsOfData++;	

	//eeprom_update_word((uint16_t*)WordsOfData, totalError16);
	//WordsOfData++;
	//WordsOfData++;
	//eeprom_update_word((uint16_t*)WordsOfData, totalError8);
	//WordsOfData++; 
	//WordsOfData++;

	//eeprom_update_word((uint16_t*)WordsOfData, 0x0000 );
	//WordsOfData++;
	//WordsOfData++;
	///////////////////////test data
	//testVariable++;
	//if (testVariable > 40)
	//{
	//testVariable = 0;
	//intToCharUart(leftWallSensorValue);
	//}
}

void moveOneBlock(void)
{
	rightEncoderAPos = 0;
	while (rightEncoderAPos < 80)//accelerate
	{
		while (rightEncoderAPos < 60)
		{
			while (rightEncoderAPos < 40)
			{
				leftMotorForward(18);
				rightMotorForward(20);
			}
			leftMotorForward(28);
			rightMotorForward(30);
		}
		leftMotorForward(38);
		rightMotorForward(40);
	}


	rightEncoderAPos = 0;
	//while (rightEncoderAPos < 600)
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
	//checkWalls();
	while (rightEncoderAPos < 1400)
	{
		leftWallSensorValue = IRSensorAngleLeftLED();
		rightWallSensorValue = IRSensorAngleRightLED();
		//eeprom_update_word((uint16_t*)WordsOfData, (leftWallSensorValue));
		//WordsOfData++;
		//WordsOfData++;
		moveWithPD();
		//leftMotorForward(leftBaseSpeed);//straight line test
		//rightMotorForward(rightBaseSpeed +4);//straight line test, +4 is to get rid of the slight right curve

		//timerInMilliseconds(20);
		//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	}
	rightEncoderAPos = 0;
	while (rightEncoderAPos < 80)//decelerate
	{
		while (rightEncoderAPos < 60)
		{
			while (rightEncoderAPos < 40)
			{
				leftMotorForward(40);
				rightMotorForward(30);
			}
			leftMotorForward(30);
			rightMotorForward(20);
		}
		leftMotorForward(20);
		rightMotorForward(10);
	}
	if (IRSensorFrontRightLED() > 100)
		alignToFrontWall();
	leftMotorForward(0);
	rightMotorForward(0);
}

void moveOneBlockContinuous(void)
{
	rightEncoderAPos = 0;
	while (rightEncoderAPos < 900)
	{
		leftWallSensorValue = IRSensorAngleLeftLED();
		rightWallSensorValue = IRSensorAngleRightLED();
		moveWithPD();
		//leftMotorForward(leftBaseSpeed);//straight line test
		//rightMotorForward(rightBaseSpeed +4);//straight line test, +4 is to get rid of the slight right curve

		//timerInMilliseconds(20);
		//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	}
	checkWalls();
	while (rightEncoderAPos < 1600)
	{
		leftWallSensorValue = IRSensorAngleLeftLED();
		rightWallSensorValue = IRSensorAngleRightLED();
		moveWithPD();
		//leftMotorForward(leftBaseSpeed);//straight line test
		//rightMotorForward(rightBaseSpeed +4);//straight line test, +4 is to get rid of the slight right curve

		//timerInMilliseconds(20);
		//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	}
}

void startMoveOneBlock(void)
{
	rightEncoderAPos = 0;
	while (rightEncoderAPos < 80)//accelerate
	{
		while (rightEncoderAPos < 60)
		{
			while (rightEncoderAPos < 40)
			{
				leftMotorForward(18);
				rightMotorForward(20);
			}
			leftMotorForward(28);
			rightMotorForward(30);
		}
		leftMotorForward(38);
		rightMotorForward(40);
	}
	rightEncoderAPos = 0;
	while (rightEncoderAPos < 700)
	{
		leftWallSensorValue = IRSensorAngleLeftLED();
		rightWallSensorValue = IRSensorAngleRightLED();
		moveWithPD();
		//leftMotorForward(leftBaseSpeed);//straight line test
		//rightMotorForward(rightBaseSpeed +4);//straight line test, +4 is to get rid of the slight right curve

		//timerInMilliseconds(20);
		//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	}
	checkWalls();
	while (rightEncoderAPos < 1600)
	{
		leftWallSensorValue = IRSensorAngleLeftLED();
		rightWallSensorValue = IRSensorAngleRightLED();
		moveWithPD();
		//leftMotorForward(leftBaseSpeed);//straight line test
		//rightMotorForward(rightBaseSpeed +4);//straight line test, +4 is to get rid of the slight right curve

		//timerInMilliseconds(20);
		//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	}

}

void endMoveOneBlock(void)
{
	rightEncoderAPos = 0;
	while (rightEncoderAPos < 900)
	{
		leftWallSensorValue = IRSensorAngleLeftLED();
		rightWallSensorValue = IRSensorAngleRightLED();
		moveWithPD();
		//leftMotorForward(leftBaseSpeed);//straight line test
		//rightMotorForward(rightBaseSpeed +4);//straight line test, +4 is to get rid of the slight right curve

		//timerInMilliseconds(20);
		//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	}
	checkWalls();
	while (rightEncoderAPos < 1400)
	{
		leftWallSensorValue = IRSensorAngleLeftLED();
		rightWallSensorValue = IRSensorAngleRightLED();
		moveWithPD();
		//leftMotorForward(leftBaseSpeed);//straight line test
		//rightMotorForward(rightBaseSpeed +4);//straight line test, +4 is to get rid of the slight right curve

		//timerInMilliseconds(20);
		//PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	}
	rightEncoderAPos = 0;
	while (rightEncoderAPos < 80)//decelerate
	{
		while (rightEncoderAPos < 60)
		{
			while (rightEncoderAPos < 40)
			{
				leftMotorForward(40);
				rightMotorForward(34);
			}
			leftMotorForward(30);
			rightMotorForward(24);
		}
		leftMotorForward(20);
		rightMotorForward(14);
	}
	if (IRSensorFrontRightLED() > 100)
	alignToFrontWall();
	leftMotorForward(0);
	rightMotorForward(0);
}
