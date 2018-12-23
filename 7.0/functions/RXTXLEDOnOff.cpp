/* RXTXLEDOnOff.cpp
 * 
 * greenRXLEDOn();
 * greenRXLEDOff();
 * blueTXLEDOn();
 * blueTXLEDOff();
 *
 */

void greenRXLEDOn()
{
		//also 0x02 = 0b00000010 = (1 << PORTD1) = (1 << 2) = _BV(2) = 2
		PORTD |= (1 << PORTD1); //port D1,  RX LED green
}
 
void greenRXLEDOff()
{
		//also 0x02 = 0b00000010 = (1 << PORTD1) = (1 << 2) = _BV(2) = 2
		PORTD &= ~(1 << PORTD1); //port D1,  RX LED green
}

void blueTXLEDOn()
{
		//also 0x01 = 0b00000001 = (1 << PORTD0) = (1 << 1) = _BV(1) = 1
		PORTD |= (1 << PORTD0); //port D0,  TX LED , blue
}

void blueTXLEDOff()
{
		//also 0x01 = 0b00000001 = (1 << PORTD0) = (1 << 1) = _BV(1) = 1
		PORTD &= ~(1 << PORTD0); //port D0,  TX LED blue
}