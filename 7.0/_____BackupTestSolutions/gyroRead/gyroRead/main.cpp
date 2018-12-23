/*
 * mainTimer.cpp
 *
 * Created: 10/17/2017 8:14:09 PM
 * Author : Lee
 */ 
 
#define F_CPU 16000000UL //this has to be set for the 16Mhz external clock that is installed
#include <avr/io.h>

#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "RXTXLEDOnOff.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item


void timer2_init();
uint16_t startADCConversion();
volatile uint16_t gyroValue;// ADC higher value


int main(void)
{

	// connect led to pin PC0
	RegisterInitialization();
	
	// initialize timer
	timer2_init();
	
	// loop forever
	while(1)
	{
		// check if the timer count reaches 124
		for(long unsigned int oneSecond =0; oneSecond  <= 10;oneSecond++)//(oneSecond  <= 10) and (TCNT2 <= 160) is 0.001 second
		{
			while (TCNT2 <= 160)
			{
			TCNT2++;// reset counter
 			}
			TCNT2 = 0;// reset counter
		};
		gyroValue = startADCConversion();
	}




}

void timer2_init()
{
	/////////////////////////////////USART config
	UBRR0H = (BRC >> 8); //sets the UART BAUD rate shifted over 8 bits , upper 8 bits
	UBRR0L = BRC;// lower 8bits
	UCSR0B = (1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);// sets up 8 bit data frame
	
	///////////////////////////////////ADC configure
	ADCSRA =  (1 << ADEN) | (1 << ADPS2);//(1 << ADPS2) | (1 << ADPS1)  // 16 prescale for 1Mhz
	//aden: adc enable;
	//input clockmux range: 16,000,000/50,000= 320  to   16,000,000/200,000= 80
	// 128 is the closest to what we need, so: ADPS2,ADPS1,ADPS0 all need to be 1
	//adie: adc interupt enable
	DIDR0 = (1 << ADC0D) | (1 << ADC1D) | (1 << ADC2D);//disables digital input from this pin is not needed to reduce power consumption
	ADMUX |= (1 << REFS0);  // AVcc with External Capacitor at Aref pin, leaving MUX0,MUX1,MUX2,and MUX3 zero says we are using ADC0
	//ADMUX |= 1<<ADLAR;//flips the bit needs to use High bit, gives 8bit resolution
	//ADMUX &= ~(1 << ADLAR);   // clear for 10 bit resolution( &= ~ is turn a bit off)
	

	
	// set up timer with prescaler = 1024
	TCCR2B |= (1 << CS20)|(1 << CS21)|(1 << CS22);
	// initialize counter
	TCNT2 = 0;
}


uint16_t startADCConversion()
{
	uint8_t theLow; // ADC lower value
	uint16_t gyroValue;// ADC higher value

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish
	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish

	theLow = ADCL; // ADC lower value
	gyroValue = ADCH <<8 | theLow;// ADC higher value

	return gyroValue;
}

 /*********************** Gyro Stuff **************************/
 //float gyroAngle() {
 //int t = micros();
 //int gyroRead = analogRead(gyroPin) - 302;
 //if(gyroRead > 4 || gyroRead < -4)
 //{
 ////        gyroRead = gyroRead*4.928/1023; //volts
 ////        angle = gyroRead/0.000685;  //
 ////        angle = angle/100.0; //millivolts
 //totalAngle = totalAngle + gyroRead/2;
 //while(micros() - t < 1000) {
 //}
 //}
 //return totalAngle;
 ////        return gyroRead;
 //}