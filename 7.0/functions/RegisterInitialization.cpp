/*
 * RegisterInitialization.cpp
 *
 * RegisterInitialization();
 *
 * Created: 9/29/2017 3:51:39 AM
 * Author : Lee
 */ 

 #include <avr/interrupt.h>


 #define F_CPU   16000000UL						//my external clock speed
 #define BUAD    9600							//my RN42 Bluetooth rate, changed on RN42 from 115200
 #define BRC     ((F_CPU/16/BUAD) - 1)			//Baud Rate Calculator

 /////////////////////////// Communications variables
 volatile uint8_t recievedChar = 0;					//volatile allows for varable to be passed between ISR and INT MAIN
 volatile uint8_t theLow = 0;
 volatile uint8_t theTenBitResult = 0;

////////////////CheckWalls variables
uint8_t cellWalls = 0x00;

////////////////encoder variable
volatile uint16_t rightEncoderAPos  = 0;

///////////////timer 2(main timer) variables
//volatile uint16_t oneSecond = 0; 

/////////////////////chooseDirection() variables
const uint8_t widthLengthSize = 6;
struct mazeCell//all data in a cell:the walls, step count , cell weight for priority
{
	uint8_t cellParameters;  //first four bits are: north(0x80)=0b10000000
							//						south(0x40)=0b01000000
							//						 east(0x20)=0b00100000
							//						 west(0x10)=0b00010000
							//last four bits are: visited(0x08)=0b00001000 
							//					 Dead end(0x04)=0b00000100 
							//			  unexplored path(0x02)=0b00000010 
							//					not used (0x01)=0b00000001
	uint16_t cellsToTargetCell;   //when doing breadth first search
	uint8_t weightToCenter; //used to draw mouse to the center
};
mazeCell mazeArray[widthLengthSize][ widthLengthSize];//this array is for tracking what is in each cell.
//#define north 0x80
//#define south 0x40
//#define east 0x20
//#define west 0x10
uint8_t current_i_xEastWestLeftRight = 0;//current X, i, cell
uint8_t current_j_yNorthSouthUpDown = 0;//widthLengthSize - 1;//current Y, j, cell
const uint8_t north = 0x80;
const uint8_t south = 0x40;
const uint8_t east = 0x20;
const uint8_t west =0x10;
uint8_t currentDirection = north;//the direction the mouse icon is facing,can be north, south, east, west
uint8_t turnDirection = north;//the direction the mouse wants to face and move can be north, south, east, west.




 
void RegisterInitialization(void)
{
		
	////////////////////////////////////////////GPIO setup
	//also 0x10 = 0b00010000 = (1 << DDB4) = (1 << 4) = _BV(4) = 16
	// SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT)), CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
	// FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT)), CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))
	DDRC |= 0b00011000; //port C3 front IRLED and port C4 diagonal IRLED
	DDRD = 0b01100011; //port D6 and D7 is for motor control, port D0 RX LED and D1 TX LED
	DDRC &= ~0b00101000;//clear bit, configure portC as input button setup
	DDRB |= 0b0000110;//Data Direction, timer/counter 1 for PWM, I don't think this is needed.
	PORTB = (1<<PORTB0);	// Set the pull-up on PB0. our PCINT interrupt
	PORTD = 0b10000000;//(1<<PORTD7);	// Set the pull-up on PB0. our PCINT interrupt

	///////////////////////////////////////////__This is for the timer/counter 0, forward motor
	//also 0x60 = 0b01100000 = (1 << DDRD6) |(1 << DDD4) = (1 << 7) | (1 << 6) = _BV(7) | _BV(6) = 96
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);// TTTTimer/CCCCounter CCCControl RRRRegister AAAA:
	// CCCCompare OOOOutput MMMMode for Channel B1: COM0B1=1, COM0B0=0, Clear OC0B on Compare Match.
	// WWWWaveform GGGGeneration MMMMode: WGM02=0, WGM01=1, WGM00=1,
	//Timer/Counter Mode of Operation: Fast PWM
	//TOP: 0xFF
	//Update of OCR0x at: BOTTOM
	//TOV Flag Set on: MAX,0xFF
	TCCR0B = (1 << CS02) | (1 << CS00); // TTTTimer/CCCCounter CCCControl RRRRegister BBBB
	//Clock Select 0
	//CA02+1, CS01=0, CS00=1: clkI/O/1024 (From prescaler)... /1024 is the fastest timer trigger setting
	
    ///////////////////////////////////////////__This is for the timer/counter 1 , motor in rearward direction
	//also 0x04 = 0b0000110 = (1 << DDRB6) = (1 << 7) = _BV(7) = 64
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);// TTTTimer/CCCCounter CCCControl RRRRegister AAAA:
	// CCCCompare OOOOutput MMMMode for Channel B1: COM0B1=1, COM0B0=0, Clear OC0B on Compare Match.
	// WWWWaveform GGGGeneration MMMMode: WGM02=0, WGM01=1, WGM00=1,
	//Timer/Counter Mode of Operation: Fast PWM
	//TOP: 0xFF
	//Update of OCR0x at: BOTTOM
	//TOV Flag Set on: MAX
	TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12); // TTTTimer/CCCCounter CCCControl RRRRegister BBBB
	//Clock Select 0
	//CA02+1, CS01=0, CS00=1: clkI/O/1024 (From prescaler)... /1024 is the fastest timer trigger setting
	
	//////////////////////////////// timer/counter 2 setup
	//OCR2A = 62; // number in TCNT2 is compaired, OCRn =  [ (clock_speed / Prescaler_value) * Desired_time_in_Seconds ] - 1
	//TCCR2A |= (1 << WGM21);	// Set to CTC Mode, "Clear Timer on Compare" 
	//TIMSK2 |= (1 << OCIE2A); //Set interrupt on compare match
	TCCR2B |= (1 << CS20)|(1 << CS21)|(1 << CS22);		// set up timer with prescaler = 1024
	TCNT2 = 0; 					// initialize counter

	/////////////////////////////////USART config
	UBRR0H = (BRC >> 8); //sets the UART BAUD rate shifted over 8 bits , upper 8 bits
	UBRR0L = BRC;// lower 8bits
	// moved UCSR0B to the using function to save power
	//UCSR0B = (1 << RXCIE0) | (1 << RXEN0);//  (1 << TXEN0)  | (1 << TXCIE0);// TXEN0 enables transmit of UART 0; TXCIE0 trips the USART_TX_vect interupt when the UDR0 register empties
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);// sets up 8 bit data frame

	////////////////////////////////////////////////////ADC setup
    ADCSRA = _BV(ADEN) | _BV(ADPS2);// ADIE is for using interrupts| _BV(ADIE); //Enable ADC and with prescaler=16; page 256 of datasheet
	DIDR0 = (1 << ADC0D) | (1 << ADC1D) | (1 << ADC2D);//disables digital input from this pin is not needed to reduce power consumption
    //ADMUX |= 1<<REFS0<- moved to where the other admux info is, 0x40 = 0b0100000 gyro ;//| _BV(ADLAR) ;//ASC  multiplexer register: REFS0: where the voltage reference is coming from

	///////////////////////////////////////////Encoder setup
	PCMSK2 = (1 << PCINT23); // enable interrupt on D7
	PCMSK0 = (1 << PCINT0); // enable interrupt on B0
	PCICR = (1 << PCIE2) | (1 << PCIE0);// mask

	sei(); //set Global Interrupt Enable	
}

//Interrupt Service Routine for PCINT0/B0
ISR(PCINT0_vect)
{
	rightEncoderAPos++;
}
//Interrupt Service Routine for PCINT2/D7
ISR(PCINT2_vect)
{
	rightEncoderAPos++;
}

//ISR (TIMER2_COMPA_vect)// does not execute my functions in the ISR
//{
	 //action to be done every 250 usec
    //if (oneSecond  <= 255)
    //{
		//oneSecond++;
    //}
	//else
	//{
	//oneSecond = 0;
	//if (1 == PORTD1)
	//RXLEDOff();
	//else
	//RXLEDOn();		
	//}
//}
