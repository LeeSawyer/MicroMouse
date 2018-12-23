/*
 * GyroBluetoothOutput.c
 *
 * Created: 3/12/2015 10:12:51 PM
 *  Author: Lee Sawyer
 *
 *  This is for use on an 8-bit AVR Atmel microcontroller. 
 *  It demonstrates use of an Analog-to-Digital Converter and outputs the value out the USART serial port
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

//#include "Motor.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item

#define F_CPU	16000000UL
#define BUAD	9600
#define BRC		((F_CPU/16/BUAD) - 1) // BUAD Rate Calculator((clockspeed/ 16 / the UART BAUD rate)-1)


#include <util/delay.h>
//#include <string>

// 	uint8_t theLow = 0;
// 	uint16_t theTenBitResult = 0;

//uint8_t destroyer = 97;

int main(void)
{
	/////////////////////////////////USART config
	//UBRR0H = (BRC >> 8); //sets the UART BAUD rate shifted over 8 bits , upper 8 bits
	UBRR0L = BRC;// lower 8bits
	UCSR0B = (1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);// sets up 8 bit data frame
	
	/////////////////////////////////ADC configure
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADIE); //Enable ADC and with prescaler=128; page 256 of datasheet
		//aden: adc enable; 
		//input clockmux range: 16,000,000/50,000= 320  to   16,000,000/200,000= 80
				// 128 is the closest to what we need, so: ADPS2,ADPS1,ADPS0 all need to be 1 
		//adie: adc interupt enable
	DIDR0 = (1 << ADC0D) | (1 << ADC1D) | (1 << ADC2D);//disables digital input from this pin is not needed to reduce power consumption
	ADMUX |= 1<<REFS0;// AVcc with External Capacitor at Aref pin, leaving MUX0,MUX1,MUX2,and MUX3 zero says we are using ADC0
	//ADMUX |= 1<<ADLAR;//flips the bit needs to use High bit, gives 8bit resolution
	
	sei();//Set External Interupt
	
	ADCSRA |= _BV(ADSC);          //adsc: adc start first conversion



    while(1)
    {

    }
}

 /*********************** Gyro Stuff **************************/
 //float gyroAngle() {
 	//int t = micros();
 	//int gyroRead = analogRead(gyroPin) - 302;
 	//if(gyroRead > 4 || gyroRead < -4)
 	//{
 		////        gyroRead = gyroRead*4.928/1023;
 		////        angle = gyroRead/0.000685;
 		////        angle = angle/100.0;
 		//totalAngle = totalAngle + gyroRead/2;
 		//while(micros() - t < 1000) {
 		//}
 	//}
 	//return totalAngle;
 	////        return gyroRead;
 //}

ISR(ADC_vect)
{
	//unsigned int num = 1024;// our input number
	char buf[5];//buffer ?
	
	uint8_t theLow = ADCL; // ADC lower value
	uint16_t theTenBitResult = ADCH <<8 | theLow;// ADC higher value



	itoa(theTenBitResult, buf, 10);//(input number, pointer to buffer array, base), requires <stdlib.h>

		
	_delay_ms(1);
	//sending just one char
	UDR0 = buf[0];//'9';//register that we put the data in that we want transmitted
 	_delay_ms(1);
 	UDR0 = buf[1];
 	_delay_ms(1);
 	UDR0 = buf[2];
 	_delay_ms(1);
 	UDR0 = buf[3];
 	_delay_ms(1);
 	UDR0 = 0x0A;
 	_delay_ms(1);
 	UDR0 = 0x0D;
	_delay_ms(1000);
		
		
	ADCSRA |= 1<<ADSC;
	
}
