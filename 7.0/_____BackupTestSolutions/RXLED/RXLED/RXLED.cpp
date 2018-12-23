/* port_test.c
 * The following program just  keeps toggling pin 0 of port B
 */


#define F_CPU 16000000UL //this has to be set for the 16Mhz external clock that is installed
#include <util/delay.h>

#include <avr/io.h> //standard include for ATMega16



int main(void)
{
    //DDRC = 0b00011000; //port C3 front and port C4 diagonal
				//also 0x10 = 0b00010000 = (1 << DDB4) = (1 << 4) = _BV(4) = 16
    DDRD = 0b00000010; //port D1,  RX LED
    //DDRD = 0b00000011; //port D 0 and 1, RX and TX LED

	while (1)
	{
		//PORTC ^= 0b00010000; //port C4 diagonal 

		_delay_us(1000000);
		//PORTC ^= 0b00011000;//port C3 front and port C4 diagonal
		PORTD ^= 0b00000010; //port D1,  RX LED
		//_delay_ms(1000);

	}
}