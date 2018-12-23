/*
 * EEPROM.cpp
 *
 * Created: 2/10/2018 9:16:43 PM
 * Author : Lee
 */ 

#include <avr/io.h>

#include <avr/eeprom.h>

int main()
{
	uint16_t WordOfData ;
	WordOfData = 0x1111 ;
	eeprom_update_word((uint16_t*)0, WordOfData );
	WordOfData = 0x2222 ;
	eeprom_update_word((uint16_t*)2, WordOfData );
	WordOfData = 0x3333 ;
	eeprom_update_word((uint16_t*)4, WordOfData );
	WordOfData = 0x4444 ;
	eeprom_update_word((uint16_t*)6, WordOfData );
	WordOfData = 0x5555 ;
	eeprom_update_word((uint16_t*)8, WordOfData );
}

