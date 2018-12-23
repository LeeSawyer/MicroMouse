/*
 * calculateFastPath.cpp
 *
 * Created: 2/15/2018 11:25:26 PM
 * Author : Lee
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include "RegisterInitialization.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "RXTXLEDOnOff.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "mainTimer.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "communications.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "IRSensors.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item
#include "movement.cpp" //include by adding path by right clicking project main(TestMain)->Properties->Toolchain->AVR/GNU C++ Compiler->Directories->Add Item



//uint8_t mousePath[16][16]; //replaced by mazeArray[][].cellsToTargetCell
//uint8_t mousePriority[16][16];
//uint8_t steps = 1;
//bool reverse = false;
//bool stopReverse = false;
//uint8_t mazeArray[NodeArrayRow][NodeArrayColumn].cellParameters[16][16];
//uint8_t DistanceFromTargetNode[16][16];  replaced by mazeArray[][].cellsToTargetCell

//uint8_t Length;
//uint8_t target_X =5;
//uint8_t target_y =5;

void initializeMazeParameters()
{

/*
   6X6 practice maze

   *--*--*--*--*--*--*
   |              |  |
   *  *--*  *--*  *  *
   |     |     |     |
   *  *  *--*--*  *--*
   |  |     |  |  |  |
   *  *  *--*  *  *  *
   |  |     |  |     |
   *  *  *--*  *--*  *
   |  |     |     |  |
   *  *  *--*  *  *  *
   |  |        |     |
   *--*--*--*--*--*--*
*/

//row y= 0;
mazeArray[0][0].cellParameters = 0x78;
mazeArray[1][0].cellParameters = 0x58;
mazeArray[2][0].cellParameters = 0xC8;
mazeArray[3][0].cellParameters = 0x68;
mazeArray[4][0].cellParameters = 0x58;
mazeArray[5][0].cellParameters = 0x68;

//row y= 1;
mazeArray[0][1].cellParameters = 0x38;
mazeArray[1][1].cellParameters = 0x18;
mazeArray[2][1].cellParameters = 0xE8;
mazeArray[3][1].cellParameters = 0x18;
mazeArray[4][1].cellParameters = 0xA8;
mazeArray[5][1].cellParameters = 0x38;

//row y= 2;
mazeArray[0][2].cellParameters = 0x38;
mazeArray[1][2].cellParameters = 0x18;
mazeArray[2][2].cellParameters = 0xE8;
mazeArray[3][2].cellParameters = 0x38;
mazeArray[4][2].cellParameters = 0x58;
mazeArray[5][2].cellParameters = 0x28;

//row y= 3;
mazeArray[0][3].cellParameters = 0x38;
mazeArray[1][3].cellParameters = 0x18;
mazeArray[2][3].cellParameters = 0xE8;
mazeArray[3][3].cellParameters = 0xB8;
mazeArray[4][3].cellParameters = 0x38;
mazeArray[5][3].cellParameters = 0xB8;

//row y= 4;
mazeArray[0][4].cellParameters = 0x18;
mazeArray[1][4].cellParameters = 0xA8;
mazeArray[2][4].cellParameters = 0x58;
mazeArray[3][4].cellParameters = 0xE8;
mazeArray[4][4].cellParameters = 0x18;
mazeArray[5][4].cellParameters = 0x68;

//row y= 5;
mazeArray[0][5].cellParameters = 0x98;
mazeArray[1][5].cellParameters = 0xC8;
mazeArray[2][5].cellParameters = 0x88;
mazeArray[3][5].cellParameters = 0xC8;
mazeArray[4][5].cellParameters = 0xA8;
mazeArray[5][5].cellParameters = 0xB8;


}

void findClosestUnexploredPath(void)//
{

uint8_t target_X;
uint8_t target_y;
uint8_t lowestWeightToCenter = 50;// 50 is a big number

for (uint8_t x = 0; x < widthLengthSize; x++)
{
	for (uint8_t y = 0; y < widthLengthSize; y++)
	{
		if(mazeArray[x][y].cellsToTargetCell & 0x02)// looks at all cells with unexplored paths
		{
			if (lowestWeightToCenter > mazeArray[x][y].weightToCenter)//sees if the cell is closer to the center than the last one
			{
				lowestWeightToCenter = mazeArray[x][y].weightToCenter;	
				target_X  = x;
				target_y  = y;
			}
		}


	}
}
}

	
void calcFastPathToATargetCell(uint8_t target_X,uint8_t target_y)//	
{

	//uint16_t WordsOfData = 0;
	//for (uint16_t i=0;i<1023;i++)// clear the data
	//{
		//eeprom_update_word((uint16_t*)i, 0x0000 );// has 1000 8-bit bytes, or 50
		//i++;
	//}

	//resets the .cellsToTargetCell attribute in the mazeArray[][] array
	for (int i=0; i<(widthLengthSize); ++i)//i is for row
	{
		for (int k=0; k<(widthLengthSize); ++k)
		{
			mazeArray[i][k].cellsToTargetCell = (widthLengthSize * widthLengthSize);
		}
	}
	//////////////////////////////////////////////
	uint16_t Length = 0;
	//marking target node as 0, are start point of MooresBFS(breadth first search)
	mazeArray[target_X][target_y].cellsToTargetCell = 0;
	//make loop to not stop till Position(current) node is marked
	//	printf("Current direction: ");
	while(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell == (widthLengthSize * widthLengthSize))//current_j_yNorthSouthUpDown][current_j_yNorthSouthUpDown] == (16 * 16))
	{
		//look at each node with .cellsToTargetCell = Length
		for (int x = 0; x < widthLengthSize; x++)
		{
			for (int y = 0; y < widthLengthSize; y++)
			{
				if(mazeArray[x][y].cellsToTargetCell == Length)
				{
					//look for walls around node:Length except in direction of previous path
					//if nodes adjacent to is .cellsToTargetCell = (16 * 16)
					//if yes change .cellsToTargetCell to Length +1
					//these if statements look for a wall and makes sure it's in a direction we have not already been
					if ((!(mazeArray[x][y].cellParameters & north)//looks for no north wall
						&& (mazeArray[x][y+1].cellParameters & 0x08))//and looks for visited
						&& (mazeArray[x][y+1].cellsToTargetCell
						== (widthLengthSize * widthLengthSize)))//and looks to see if the .cellsToTargetCell has not been set already. this might happen in a loop
					{mazeArray[x][y+1].cellsToTargetCell = (Length + 1);}

					if ((!(mazeArray[x][y].cellParameters & south)//looks for no south wall
						&& (mazeArray[x][y-1].cellParameters & 0x08))
						&& (mazeArray[x][y-1].cellsToTargetCell
						== (widthLengthSize * widthLengthSize)))
					{mazeArray[x][y-1].cellsToTargetCell = (Length + 1);}

					if ((!(mazeArray[x][y].cellParameters & east)//looks for no east wall
						&& (mazeArray[x+1][y].cellParameters & 0x08))
						&& (mazeArray[x+1][y].cellsToTargetCell
						== (widthLengthSize * widthLengthSize)))
					{mazeArray[x+1][y].cellsToTargetCell = (Length + 1);}

					if ((!(mazeArray[x][y].cellParameters & west)//looks for no west wall
						&& (mazeArray[x-1][y].cellParameters & 0x08))
						&& (mazeArray[x-1][y].cellsToTargetCell
						== (widthLengthSize * widthLengthSize)))
					{mazeArray[x-1][y].cellsToTargetCell = (Length + 1);}






				}
			}
		}
		


		Length++;
	}
	/*
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[0][5].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[1][5].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[2][5].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[3][5].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[4][5].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[5][5].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;


			//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[0][5].cellParameters);
			//WordsOfData++;
			//WordsOfData++;
			//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[1][5].cellParameters);
			//WordsOfData++;
			//WordsOfData++;
			//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[2][5].cellParameters);
			//WordsOfData++;
			//WordsOfData++;
			//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[3][5].cellParameters);
			//WordsOfData++;
			//WordsOfData++;
			//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[4][5].cellParameters);
			//WordsOfData++;
			//WordsOfData++;
			//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[5][5].cellParameters);
			//WordsOfData++;
			//WordsOfData++;

			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[0][4].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[1][4].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[2][4].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[3][4].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[4][4].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[5][4].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;

			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[0][3].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[1][3].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[2][3].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[3][3].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[4][3].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[5][3].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;

			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[0][2].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[1][2].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[2][2].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[3][2].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[4][2].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[5][2].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;

			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[0][1].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[1][1].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[2][1].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[3][1].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[4][1].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[5][1].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;

			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[0][0].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[1][0].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[2][0].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[3][0].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[4][0].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++;
			eeprom_update_word((uint16_t*)WordsOfData,mazeArray[5][0].cellsToTargetCell);
			WordsOfData++;
			WordsOfData++; 
			*/
}

void travelFastestPath()
{
	while(!(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell == 0))
	{
		switch(currentDirection)
		{
			case north://////////// north
			if(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown+1].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown + 1;
				turnDirection = north;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown-1].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown - 1;
				rightEncoder180();
				turnDirection = south;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight+1][current_j_yNorthSouthUpDown].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_i_xEastWestLeftRight = current_i_xEastWestLeftRight + 1;
				rightGyroTurn();
				turnDirection = east;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight-1][current_j_yNorthSouthUpDown].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_i_xEastWestLeftRight = current_i_xEastWestLeftRight - 1;
				leftGyroTurn();
				turnDirection = west;
				break;
			}

			case south:////////////// south
			if(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown+1].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown + 1;
				rightEncoder180();
				turnDirection = north;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown-1].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown - 1;
				turnDirection = south;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight+1][current_j_yNorthSouthUpDown].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_i_xEastWestLeftRight = current_i_xEastWestLeftRight + 1;
				leftGyroTurn();
				turnDirection = east;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight-1][current_j_yNorthSouthUpDown].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_i_xEastWestLeftRight = current_i_xEastWestLeftRight - 1;
				rightGyroTurn();
				turnDirection = west;
				break;
			}

			case east:///////////////// east
			if(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown+1].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown + 1;
				leftGyroTurn();
				turnDirection = north;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown-1].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown - 1;
				rightGyroTurn();
				turnDirection = south;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight+1][current_j_yNorthSouthUpDown].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_i_xEastWestLeftRight = current_i_xEastWestLeftRight + 1;
				turnDirection = east;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight-1][current_j_yNorthSouthUpDown].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_i_xEastWestLeftRight = current_i_xEastWestLeftRight - 1;
				rightEncoder180();
				turnDirection = west;
				break;
			}

			case west://////////////// west
			if(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown+1].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown + 1;
				rightGyroTurn();
				turnDirection = north;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown-1].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown - 1;
				leftGyroTurn();
				turnDirection = south;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight+1][current_j_yNorthSouthUpDown].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_i_xEastWestLeftRight = current_i_xEastWestLeftRight + 1;
				rightEncoder180();
				turnDirection = east;
				break;
			}
			if(mazeArray[current_i_xEastWestLeftRight-1][current_j_yNorthSouthUpDown].cellsToTargetCell == (mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell - 1))
			{
				current_i_xEastWestLeftRight = current_i_xEastWestLeftRight - 1;
				turnDirection = west;
				break;
			}



		}

		//uint16_t WordsOfData = 0;
		//for (uint16_t i=0;i<1023;i++)// clear the data
		//{
			//eeprom_update_word((uint16_t*)i, 0x0000 );// has 1000 8-bit bytes, or 50
			//i++;
		//}
//
		//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[0][5].cellsToTargetCell);
		//WordsOfData++;
		//WordsOfData++;
		//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[1][5].cellsToTargetCell);
		//WordsOfData++;
		//WordsOfData++;
		//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[2][5].cellsToTargetCell);
		//WordsOfData++;
		//WordsOfData++;
		//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[3][5].cellsToTargetCell);
		//WordsOfData++;
		//WordsOfData++;
		//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[4][5].cellsToTargetCell);
		//WordsOfData++;
		//WordsOfData++;
		//eeprom_update_word((uint16_t*)WordsOfData,mazeArray[5][5].cellsToTargetCell);
		//WordsOfData++;
		//WordsOfData++;





		/*
		//intToCharUartNoNL(mazeArray[0][5].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[1][5].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[2][5].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[3][5].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[4][5].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUart(mazeArray[5][5].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
//
//
		//intToCharUartNoNL(mazeArray[0][4].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[1][4].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[2][4].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[3][4].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[4][4].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUart(mazeArray[5][4].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
//
		//intToCharUartNoNL(mazeArray[0][3].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[1][3].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[2][3].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[3][3].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[4][3].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUart(mazeArray[5][3].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
//
		//intToCharUartNoNL(mazeArray[0][2].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[1][2].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[2][2].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[3][2].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[4][2].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUart(mazeArray[5][2].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
//
//
//
		//intToCharUartNoNL(mazeArray[0][1].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[1][1].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[2][1].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[3][1].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[4][1].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUart(mazeArray[5][1].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
//
//
		//intToCharUartNoNL(mazeArray[0][0].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[1][0].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[2][0].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[3][0].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUartNoNL(mazeArray[4][0].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//intToCharUart(mazeArray[5][0].cellsToTargetCell);
		//timerInMilliseconds(5);// can't do more than 5 seconds  */






		//while (950 > IRSensorAngleLeft()) //waits for left front sensor to be tripped by user to continue
		//{
			//timerInMilliseconds(10);
		//}


		timerInMilliseconds(500);
		moveOneBlock();
		currentDirection = turnDirection;
	}
}

int main(void)
{
	RegisterInitialization();
    /* Replace with your application code */
    //while (1) 
	initializeMazeParameters();
	//{


		while (950 > IRSensorAngleLeft()) //waits for left front sensor to be tripped by user to continue
		{
			timerInMilliseconds(10);
		}

			timerInMilliseconds(5000);
			calcFastPathToATargetCell(4,0);
			travelFastestPath();
    //}
}

	/*  /printMaze2();
	/////////////
			//while((current_j_yNorthSouthUpDown != Endrow) || (current_i_xEastWestLeftRight != Endcolumn))
			//{
				////	maze->Generate();
				//// count down nodes... looks in all four directions for a lower ..cellsToTargetCell towards
				//if ((mazeArray[current_i_xEastWestLeftRight - 1][current_j_yNorthSouthUpDown].cellsToTargetCell < mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell)
						//&& !(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters & 1))
				//{
					//currentDirection = north;
				//}
				//else if ((mazeArray[current_i_xEastWestLeftRight + 1][current_j_yNorthSouthUpDown].cellsToTargetCell < mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell)
						//&& !(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters & 2))
				//{
					//currentDirection = south;
				//}
				//else if ((mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown + 1].cellsToTargetCell < mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellsToTargetCell)
						//&& !(mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters & 4))
				//{
					//currentDirection = east;
			//}
				//else
			//{
					//currentDirection  = west;
				//}
				///////////////////////////////
				////						// the first set of	SWITCH CASE statements look for which direction it is going to
				//switch (currentDirection)
				//{
				//case north : //which is actually looking at the previous move
					//current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown - 1;//"current_j_yNorthSouthUpDown" is the 33X33 position
					//break;
	//
				//case south : //which is actually looking at the previous move
					//current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown + 1;
					//break;
	//
				//case east : //which is actually looking at the previous move
					//current_i_xEastWestLeftRight = current_i_xEastWestLeftRight + 1;
					//break;
	//
				//case west : //which is actually looking at the previous move
					//current_i_xEastWestLeftRight = current_i_xEastWestLeftRight- 1;
					//break;
	//
				//default : cout << "Move FAAAAIL?!?!";
				//break;
				//}
	///////////////////
			//maze->Print(); */
