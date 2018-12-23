/* adc.c
 * This program demonstrates the use of ADMUX for selecting the ADC input pin
 * gyro conversion: 
 */


//#define F_CPU 16000000UL

//#include <avr/io.h>
//#include <avr/interrupt.h>

//int ADCSetup()
//{
// 	DDRB = 0x60;		// 0x60 = 0110000,   0 is input , 1 is output
//     DDRC = 0x18; // port B output, 0x3f = 0011 1111
//     DDRD = 0xc6; // 0xc6 = 11000110
// 	unsigned char compare_value = 0x7f; // 0x7f = 0111 1111 = 127
//     unsigned char x[4]; //Array
//    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADIE); //Enable ADC and with prescaler=16; page 256 of datasheet
//	DIDR0 = (1 << ADC0D) | (1 << ADC1D) | (1 << ADC2D);//disables digital input from this pin is not needed to reduce power consumption
//    ADMUX |= 1<<REFS0;//ASC  multiplexer register: REFS0: where the voltage reference is coming from

//	uint16_t theTenBitResult = 0;
	
//	sei(); //set Global Interrupt Enable
	
//	ADCSRA |= _BV(ADSC);          //ADC control and status Register A 
	
//    while (1==1)
    //{
            // Select pin ADC0:0b00000000 Gyro, ADC1:0b00000001 LeftAngle, ADC2:0b00000010 leftFront,
			//	ADC6:0b00000110 rightFront, ADC7:0b00000111 rightAngle.  using MUXr
            //ADMUX = _BV(REFS0)  | _BV(ADLAR) ;    //ASC  multiplexer register
				//REFS0: where the voltage reference is coming from
				//ADLAR: Left Adjust Result, fills ADCL and ADCR in reverse order
            //Start Conversion
            //ADCSRA |= _BV(ADSC);          //ADC control and status Register A

//             // wait until converstion completed, don't know it I need this
//             while (ADCSRA & _BV(ADSC) ) {}
  //  }
//}

void startADCConversion()
{
ADCSRA |=  _BV(ADEN); // after the flag is thrown, this will reset.
}

ISR(ADC_vect)
{
theLow = ADCL;
theTenBitResult = ADCH<<8 | theLow;

//theTenBitResult = theTenBitResult/500;
 


}
