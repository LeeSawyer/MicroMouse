 /*
 * Communications.cpp
 *	
 *	tranmitUSB();
 *	uint8_tToUart(uint8_t int8ToTrans);
 *	int8_tToCharUart(uint8_t int8ToTrans);
 *	intToCharUart(uint16_t intToTrans);
 *
 * Created: 10/29/2017 10:51:39 AM
 * Author : Lee
 */ 

//#include "mainTimer.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item

void tranmitUSB(void)
{
	// 	//unsigned int num = 1024;// our input number
	// 	char buf[5];//buffer ?
	// 	// 	
	// 	uint8_t theLow = ADCL;
	// 	uint16_t theTenBitResult =  ADCH << 8 | theLow;
	// 
	// 	itoa(theTenBitResult, buf, 10);//(input number, pointer to buffer array, base), requires <stdlib.h>
	unsigned char theLowest= 77;

		/* Wait for empty transmit buffer */
		while ( !( UCSR0A & (1<<UDRE0)) );
		/* Put data into buffer, sends the data */
		UDR0 = theLowest;
	
}

void uint8_tToUart(uint8_t int8ToTrans)
{
	UCSR0B = (1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
	timerInMilliseconds(1);
	UDR0 = int8ToTrans;
	timerInMilliseconds(1);
	
	UCSR0B = 0x0D ;//(1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties	
}

void uint8_tToBluetooth(uint8_t int8ToTrans)
{
	UCSR0B = (1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
	char buf[5];//buffer ?

	itoa(int8ToTrans, buf, 10);//(input number, pointer to buffer array, base), requires <stdlib.h>

	timerInMilliseconds(1);		//sending just one char
	UDR0 = buf[0];//'9';//register that we put the data in that we want transmitted
	timerInMilliseconds(1);
	UDR0 = buf[1];
	timerInMilliseconds(1);
	UDR0 = buf[2];
	timerInMilliseconds(1);
	UDR0 = buf[3];
	timerInMilliseconds(1);
	UDR0 = 0x0A;
	timerInMilliseconds(1);
	UDR0 = 0x0D;
	timerInMilliseconds(1);
		
	UCSR0B = 0x0D ;//(1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
}

void uint8_tToBluetoothNoNL(uint8_t int8ToTrans)
{
	UCSR0B = (1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
	char buf[5];//buffer ?

	itoa(int8ToTrans, buf, 10);//(input number, pointer to buffer array, base), requires <stdlib.h>

	timerInMilliseconds(1);		//sending just one char
	UDR0 = buf[0];//'9';//register that we put the data in that we want transmitted
	timerInMilliseconds(1);
	UDR0 = buf[1];
	timerInMilliseconds(1);
	UDR0 = buf[2];
	timerInMilliseconds(1);
	UDR0 = buf[3];
	timerInMilliseconds(1);
	UDR0 = 0x17;
	timerInMilliseconds(1);
	//UDR0 = 0x0D;
	//timerInMilliseconds(1);
	
	UCSR0B = 0x0D ;//(1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
}

/* /void int8_tToCharUart(uint8_t int8ToTrans)
//{
	//uint16_t intToTrans =  int8ToTrans <<8 ;
	//
	//UCSR0B = (1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
	//char buf[5];//buffer ?
//
	//itoa(intToTrans, buf, 10);//(input number, pointer to buffer array, base), requires <stdlib.h>
//
	//_delay_ms(1);
	////sending just one char
	//UDR0 = buf[0];//'9';//register that we put the data in that we want transmitted
	//_delay_ms(1);
	//UDR0 = buf[1];
	//_delay_ms(1);
	//UDR0 = buf[2];
	//_delay_ms(1);
	//UDR0 = buf[3];
	//_delay_ms(1);
	//UDR0 = 0x0A;
	//_delay_ms(1);
	//UDR0 = 0x0D;
	//_delay_ms(1000);
	//
	//UCSR0B = 0x0D;//(1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
	//
//}  */

void intToCharUart(uint16_t intToTrans)
{
		UCSR0B = (1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
		char buf[6];//buffer ?

		itoa(intToTrans, buf, 10);//(input number, pointer to buffer array, base), requires <stdlib.h>

		timerInMilliseconds(1);		//sending just one char
		UDR0 = buf[0];//'9';//register that we put the data in that we want transmitted
		timerInMilliseconds(1);
		UDR0 = buf[1];
		timerInMilliseconds(1);
		UDR0 = buf[2];
		timerInMilliseconds(1);
		UDR0 = buf[3];
		timerInMilliseconds(1);
		UDR0 = buf[4];
		timerInMilliseconds(1);
		UDR0 = 0x0A;
		timerInMilliseconds(1);
		UDR0 = 0x0D;
 		timerInMilliseconds(1);
		
		UCSR0B = 0x0D;//(1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties	
		
}

void intToCharUartNoNL(uint16_t intToTrans)
{
	UCSR0B = (1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
	char buf[5];//buffer ?

	itoa(intToTrans, buf, 10);//(input number, pointer to buffer array, base), requires <stdlib.h>

	timerInMilliseconds(1);		//sending just one char
	UDR0 = buf[0];//'9';//register that we put the data in that we want transmitted
	timerInMilliseconds(1);
	UDR0 = buf[1];
	timerInMilliseconds(1);
	UDR0 = buf[2];
	timerInMilliseconds(1);
	UDR0 = buf[3];
	timerInMilliseconds(1);
	//UDR0 = 0x0A;
	//timerInMilliseconds(1);
	//UDR0 = 0x0D;
	//timerInMilliseconds(1000);
	
	UCSR0B = 0x0D;//(1 << TXEN0);//  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
	
}
