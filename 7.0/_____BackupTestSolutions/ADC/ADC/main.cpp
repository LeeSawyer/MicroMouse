/* adc.c
 * This program demonstrates the use of ADMUX for selecting the ADC input pin
 */


#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{
// 	DDRB = 0x60;		// 0x60 = 0110000,   0 is input , 1 is output
//     DDRC = 0x18; // port B output, 0x3f = 0011 1111
//     DDRD = 0xc6; // 0xc6 = 11000110
// 	unsigned char compare_value = 0x7f; // 0x7f = 0111 1111 = 127
//     unsigned char x[4]; //Array
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADIE); //Enable ADC and with prescaler=16; page 256 of datasheet
	DIDR0 = (1 << ADC0D) | (1 << ADC1D) | (1 << ADC2D);//disables digital input from this pin is not needed to reduce power consumption
    ADMUX |= 1<<REFS0;
//	int i=0;
	
	sei();
	
	ADCSRA |= _BV(ADSC);          //ADC control and status Register A 
	
    while (1==1)
    {




            // Select pin ADC0:0b00000000 Gyro, ADC1:0b00000001 LeftAngle, ADC2:0b00000010 leftFront,
			//	ADC6:0b00000110 rightFront, ADC7:0b00000111 rightAngle.  using MUXr
            //ADMUX = _BV(REFS0)  | _BV(ADLAR) ;    //ASC  multiplexer register
				//REFS0: where the voltage reference is coming from
				//ADLAR: Left Adjust Result, fills ADCL and ADCR in reverse order

            //Start Conversion
            //ADCSRA |= _BV(ADSC);          //ADC control and status Register A

//             // wait until converstion completed, don't know it I need this
//             while (ADCSRA & _BV(ADSC) ) {}


    }
}

//void startADCConversion()
//{
	//ADCSRA |=  _BV(ADEN); // after the flag is thrown, this will reset.
//}

ISR(ADC_vect)
{
	//uint8_t theLow = ADCL;
	//uint16_t theTenBitResult = ADCH<<8 | theLow;

// 	switch (ADMUX)
// 	{
// 		case 0xC0:
// 		Send_An_IntegerToMrLCD(4, 1, theTenBitResult, 4);
// 		ADMUX = 0xC1;
// 		break;
// 
// 		case 0xC1:
// 		Send_An_IntegerToMrLCD(4, 2, theTenBitResult, 4);
// 		ADMUX = 0xC0;
// 		break;
// 		default:
// 		//Default code
// 		break;
// 	} 
	
	ADCSRA |= 1<<ADSC; 
	
	}
