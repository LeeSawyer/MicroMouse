/* IRSensors.cpp
 * functions for using front sensors
 *
 *	diagonalLEDOn();
 *	diagonalLEDOff();
 *	frontLEDOn();
 *	frontLEDOff();
 *	IRSensorFrontLeft(); returns int
 *	IRSensorFrontRight(); returns int
 *	IRSensorAngleLeft(); returns int
 *	IRSensorAngleRight(); returns int
 *  checkWalls();
 */

void diagonalLEDOn()
{
		//also 0x16 = 0b00010000 = (1 << PORTC4) = (1 << 4) = _BV(4) = 16
		PORTC |= (1 << PORTC4); //port C4 diagonal 
}
 
void diagonalLEDOff()
{
		//also 0x16 = 0b00010000 = (1 << PORTC4) = (1 << 4) = _BV(4) = 16
		PORTC &= ~(1 << PORTC4); //port C4 diagonal 
}

void frontLEDOn()
{
 		//also 0x08 = 0b00001000 = (1 << PORTC3) = (1 << 3) = _BV(3) = 08
		PORTC |= (1 << PORTC3); //port C3 front
}
 
void frontLEDOff()
{
 		//also 0x08 = 0b00001000 = (1 << PORTC3) = (1 << 3) = _BV(3) = 08
		PORTC &= ~(1 << PORTC3); //port C3 front
}

uint16_t IRSensorFrontLeft()// 108 walls edge no light , 103 walls edge high light, 942 center cell
 {
  	 timerInMilliseconds(1);
	 uint8_t theLow; // ADC lower value
	 uint16_t IRnoise;// ADC higher value
	 uint16_t IRSensorValue;

	 ADMUX = 0x42;//|= (1 << MUX1);         // use #2 ADC 
	 frontLEDOff();

	 ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	 while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
  	 timerInMilliseconds(1);
	 ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	 while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	 theLow = ADCL; // ADC lower value
	 IRnoise = ADCH <<8 | theLow;// ADC higher value

	 frontLEDOn();
 	 timerInMilliseconds(1);

	 ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	 while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	 frontLEDOff();

	 theLow = ADCL; // ADC lower value
	 IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	 IRSensorValue = IRSensorValue - IRnoise;

	 return IRSensorValue;
 };

uint16_t IRSensorFrontRight()// 117 walls edge no light , 129 walls edge high light, 871 center cell
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRnoise;// ADC higher value
	uint16_t IRSensorValue;

	ADMUX = 0x46;//|= (1 << MUX2) | (1 << MUX1);         // use #6 ADC
	frontLEDOff();

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
    timerInMilliseconds(1);
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	theLow = ADCL; // ADC lower value
	IRnoise = ADCH <<8 | theLow;// ADC higher value

	frontLEDOn();
	//_delay_ms(1);
	timerInMilliseconds(1);

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	frontLEDOff();

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	IRSensorValue = IRSensorValue - IRnoise;

	return IRSensorValue;
};

uint16_t IRSensorAngleLeft()//251 no light, 180 high light
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRnoise;// ADC higher value
	uint16_t IRSensorValue;

	ADMUX = 0x41;//|= (1 << MUX0);         // use #1 ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	timerInMilliseconds(1);
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	theLow = ADCL; // ADC lower value
	IRnoise = ADCH <<8 | theLow;// ADC higher value

	diagonalLEDOn();
	timerInMilliseconds(1);

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	diagonalLEDOff();

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	IRSensorValue = IRSensorValue - IRnoise;

	return IRSensorValue;
};

uint16_t IRSensorAngleRight()//251 no light, 230 high light
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRnoise;// ADC higher value
	uint16_t IRSensorValue;

	ADMUX = 0x47; //|= (1 << MUX2) | (1 << MUX1) |(1 << MUX0);         // use #7 ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	timerInMilliseconds(1);
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	theLow = ADCL; // ADC lower value
	IRnoise = ADCH <<8 | theLow;// ADC higher value

	diagonalLEDOn();
	 timerInMilliseconds(1);

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	diagonalLEDOff();

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	IRSensorValue = IRSensorValue - IRnoise;

	return IRSensorValue;
};

uint16_t IRSensorFrontLeftLED()// 108 walls edge no light , 103 walls edge high light, 942 center cell
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRSensorValue;

	ADMUX = 0x42;//|= (1 << MUX1);         // use #2 ADC
	frontLEDOff();

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	timerInMilliseconds(1);
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	frontLEDOn();
	 timerInMilliseconds(1);

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	frontLEDOff();

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	return IRSensorValue;
};

uint16_t IRSensorFrontRightLED()// 117 walls edge no light , 129 walls edge high light, 871 center cell
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRSensorValue;

	ADMUX = 0x46;//|= (1 << MUX2) | (1 << MUX1);         // use #6 ADC
	frontLEDOff();

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	timerInMilliseconds(1);	
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	frontLEDOn();
	 timerInMilliseconds(1);

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	frontLEDOff();

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	return IRSensorValue;
};

uint16_t IRSensorAngleLeftLED()//251 no light, 180 high light
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRSensorValue;

	ADMUX = 0x41;//|= (1 << MUX0);         // use #1 ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	timerInMilliseconds(1);	
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	diagonalLEDOn();
	 timerInMilliseconds(1);
	
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	
	diagonalLEDOff();

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	return IRSensorValue;
};

uint16_t IRSensorAngleRightLED()//251 no light, 230 high light
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRSensorValue;

	ADMUX = 0x47; //|= (1 << MUX2) | (1 << MUX1) |(1 << MUX0);         // use #7 ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	timerInMilliseconds(1);	
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	diagonalLEDOn();
	 timerInMilliseconds(1);
	
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	
	diagonalLEDOff();

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	return IRSensorValue;
};

uint16_t IRSensorFrontLeftNoLED()// 108 walls edge no light , 103 walls edge high light, 942 center cell
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRSensorValue;

	ADMUX = 0x42;//|= (1 << MUX1);         // use #2 ADC
	frontLEDOff();

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	timerInMilliseconds(1);	
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	return IRSensorValue;
};

uint16_t IRSensorFrontRightNoLED()// 117 walls edge no light , 129 walls edge high light, 871 center cell
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRSensorValue;

	ADMUX = 0x46;//|= (1 << MUX2) | (1 << MUX1);         // use #6 ADC
	frontLEDOff();

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	timerInMilliseconds(1);	
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	//	IRSensorValue = IRSensorValue - IRnoise;

	return IRSensorValue;
};

uint16_t IRSensorAngleLeftNoLED()//251 no light, 180 high light
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRSensorValue;

	ADMUX = 0x41;//|= (1 << MUX0);         // use #1 ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	timerInMilliseconds(1);	
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	return IRSensorValue;
};

uint16_t IRSensorAngleRightNoLED()//251 no light, 230 high light
{
	timerInMilliseconds(1);
	uint8_t theLow; // ADC lower value
	uint16_t IRSensorValue;

	ADMUX = 0x47; //|= (1 << MUX2) | (1 << MUX1) |(1 << MUX0);         // use #7 ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	timerInMilliseconds(1);	
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	theLow = ADCL; // ADC lower value
	IRSensorValue = ADCH <<8 | theLow;// ADC higher value

	return IRSensorValue;
};

uint8_t checkWalls()
{		
	cellWalls = 0x00;
	if(IRSensorAngleLeft() > 175)
	{
		cellWalls |= 0x01;

		}
		//else
		//blueTXLEDOff();
	if(IRSensorFrontRight() > 30)
	{
		cellWalls |= 0x02;
		//blueTXLEDOn();


		}
	if(IRSensorAngleRight() > 175)
	{
		cellWalls |= 0x04;
		 //greenRXLEDOn();
		}
		//else
		//greenRXLEDOff();
	return cellWalls;
};