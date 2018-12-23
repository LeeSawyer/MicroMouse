/*
 * mainTimer.cpp
 *
 * Created: 10/17/2017 8:14:09 PM
 * Author : Lee
 *
 * timerInMilliseconds(number in millisecond);// can't do more than 5 seconds
 */ 
 
//#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
//#include "RXTXLEDOnOff.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item


int timerInMilliseconds(unsigned int num) // can't do more than 5 seconds
{
		for(long unsigned int oneSecond = 0; oneSecond  <= (num * 10); oneSecond++)//(oneSecond  <= 10) and (TCNT2 <= 160) is 0.001 second
		{
			while (TCNT2 <= 160)
			{
				TCNT2++;// reset counter
			}
			TCNT2 = 0;// reset counter
		}
		return(0);
}


//int main(void)
//{
	// connect led to pin PC0
//	RegisterInitialization();
	////////////////////////////////// timer/counter 2 setup
	//TCCR2B |= (1 << CS20)|(1 << CS21)|(1 << CS22);		// set up timer with prescaler = 1024
	//TCNT2 = 0;
		//DDRD = 0b01100011; //port D6 and D7 is for motor control, port D0 RX LED and D1 TX LED
//
		//RXLEDOff();

	// loop forever
//	while(1)
//	{
		// check if the timer count reaches 124
//		timerInMilliseconds(1000);

//			if (PORTD & 1<<PORTD1)
//				{RXLEDOff();}
//			else
//				{RXLEDOn();}				
	//}
//}