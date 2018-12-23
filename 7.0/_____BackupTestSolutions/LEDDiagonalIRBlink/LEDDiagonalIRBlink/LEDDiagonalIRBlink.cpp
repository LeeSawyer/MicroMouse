/* port_test.c
 * The following program just  keeps toggling pin 0 of port B
 */

#define F_CPU 16000000UL //this has to be set for the 16Mhz external clock that is installed

#include <avr/io.h> //standard include for ATMega16
#include <util/delay.h>


int main(void)
{
    DDRC = 0b00010000; //port C4 diagonal 
    //DDRC = 0b00011000; //port C3 front and port C4 diagonal
				//also 0x10 = 0b00010000 = (1 << DDB4) = (1 << 4) = _BV(4) = 16
    //DDRD = 0b00000011; //port D 0 and 1, RX and TX LED

	while (1)
	{
		PORTC ^= 0b00010000; //port C4 diagonal 
		//PORTD ^= 0b00000011;// port D 0 and 1, RX and TX LED
		//_delay_ms(1000);
		//PORTC ^= 0b00011000;//port C3 front and port C4 diagonal
		//PORTD ^= 0b00000011;// port D 0 and 1, RX and TX LED
		//_delay_ms(1000);

	}
}