/*
 * chooseDirection.cpp
 *
 * Created: 2/9/2018 3:34:46 AM
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


/* /const uint8_t widthLengthSize = 6;
//struct mazeCell//all data in a cell:the walls, step count , cell weight for priority
//{
	//uint8_t cellParameters;  //first four bits are: north(0x80),south(0x40),east(0x20),west(0x10);
	////last four bits are: visited(0x08), Dead end(0x04), unexplored path(0x02), not used.
	//uint8_t cellStepCount;   //when doing breadth first search
	//uint8_t weightToCenter; //used to draw mouse to the center
//};
//mazeCell mazeArray[widthLengthSize][ widthLengthSize];//this array is for tracking what is in each cell.
//uint8_t turnDirection;//the direction the mouse wants to face and move can be north, south, east, west.
//#define north 0x80
//#define south 0x40
//#define east 0x20
//#define west 0x10
//uint8_t current_i_xEastWestLeftRight = 0;//current X, i, cell
//uint8_t current_j_yNorthSouthUpDown = widthLengthSize - 1;//current Y, j, cell
//const int8_t north = 0x80;
//const int8_t south = 0x40;
//const int8_t east = 0x20;
//const int8_t west = 0x10;
//int8_t currentDirection = north;//the direction the mouse icon is facing,can be north, south, east, west */

void mazeCellInitialize()
{
	///////////initializes maze,
	///////////initializes the weight to the center,//used to draw mouse to the center
	for (uint8_t i = 0; i < 6; i++)//columns 6x6, weighted to corner
	{
		for (uint8_t j = 0; j < 6; j++)//rows
		{
			mazeArray[i][j].weightToCenter = (10 - (i + j));
		}
	}

		//for (uint8_t i = 0; i < 16; i++)//columns 16x16 map wieght
		//{
			//for (uint8_t j = 0; j < 16; j++)//rows
			//{
				//if ((i <= 7) && (j <= 7))
				//mazeArray[i, j].weightToCenter = (14 - (i + j));
				//else if ((i <= 7) && (j >= 8))
				//mazeArray[i, j].weightToCenter =  ((j - i )- 1);
				//else if ((i >= 8) && (j <= 7))
				//mazeArray[i, j].weightToCenter = ((i - j) - 1);
				//else if ((i >= 8) && (j >= 8))
				//mazeArray[i, j].weightToCenter = ((i + j) - 16);
			//}
		//}
	
	///////////////////////initializes cell parameters for boarder wall
	for (uint8_t i = 0; i < (widthLengthSize ); i++)
	{
		mazeArray[i][ 0].cellParameters |= 0x40;//south
		mazeArray[i][ (widthLengthSize - 1)].cellParameters |= 0x80;//north
		mazeArray[(widthLengthSize - 1)][ i].cellParameters |= 0x20;//east
		mazeArray[0][i].cellParameters |= 0x10;//west
	}

	/////////////////initialize first cell
	mazeArray[0][0].cellParameters |= 0x2C;//east wall, visited, and dead-end


}

void markWalls()// usually done by IR sensor dropping to lower resistance
{

	switch (currentDirection)
	{


		case north:
			if (cellWalls & 0x04){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1)+1, ((current_j_yNorthSouthUpDown * 2)+1)].BackColor == Color.Red)//right/East wall
			mazeArray[current_i_xEastWestLeftRight][ current_j_yNorthSouthUpDown].cellParameters |= 0x20;}
			if (cellWalls & 0x02){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1), ((current_j_yNorthSouthUpDown * 2)+1)-1].BackColor == Color.Red)//front/North wall
			mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters |= 0x80;}
			if (cellWalls & 0x01){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1)-1, ((current_j_yNorthSouthUpDown * 2)+1)].BackColor == Color.Red)//left/West wall
			mazeArray[current_i_xEastWestLeftRight][ current_j_yNorthSouthUpDown].cellParameters |= 0x10;}
		break;
		case south:
			if (cellWalls & 0x01){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1)+1, ((current_j_yNorthSouthUpDown * 2)+1)].BackColor == Color.Red)//left/East wall
			mazeArray[current_i_xEastWestLeftRight][ current_j_yNorthSouthUpDown].cellParameters |= 0x20;}
			if (cellWalls & 0x02){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1), ((current_j_yNorthSouthUpDown * 2)+1)+1].BackColor == Color.Red)//front/South wall
			mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters |= 0x40;}
			if (cellWalls & 0x04){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1)-1, ((current_j_yNorthSouthUpDown * 2)+1)].BackColor == Color.Red)//right/West wall
			mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters |= 0x10;}
		break;
		case east:
			if (cellWalls & 0x01){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1), ((current_j_yNorthSouthUpDown * 2)+1)-1].BackColor == Color.Red)//left/North wall
			mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters |= 0x80;}
			if (cellWalls & 0x02){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1)+1, ((current_j_yNorthSouthUpDown * 2)+1)].BackColor == Color.Red)//front/East wall
			mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters |= 0x20;}
			if (cellWalls & 0x04){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1), ((current_j_yNorthSouthUpDown * 2)+1)+1].BackColor == Color.Red)//right/South wall
			mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters |= 0x40;}
		break;
		case west:
			if (cellWalls & 0x04){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1), ((current_j_yNorthSouthUpDown * 2)+1)-1].BackColor == Color.Red)//right/North wall
			mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters |= 0x80;}
			if (cellWalls & 0x02){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1)-1] [((current_j_yNorthSouthUpDown * 2)+1)].BackColor == Color.Red)//front/West wall
			mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters |= 0x10;}
			if (cellWalls & 0x01){
			//buttonArray[((current_i_xEastWestLeftRight * 2)+1)] [((current_j_yNorthSouthUpDown * 2)+1)+1].BackColor == Color.Red)//left/South wall
			mazeArray[current_i_xEastWestLeftRight][current_j_yNorthSouthUpDown].cellParameters |= 0x40;}
		break;
		default:
		 break;
	}

		//uint8_tToBluetooth(mazeArray[current_i_xEastWestLeftRight][ current_j_yNorthSouthUpDown+1].cellParameters);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//uint8_tToBluetooth(mazeArray[current_i_xEastWestLeftRight][ current_j_yNorthSouthUpDown - 1].cellParameters);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//uint8_tToBluetooth(mazeArray[current_i_xEastWestLeftRight+1][ current_j_yNorthSouthUpDown].cellParameters);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//uint8_tToBluetooth(mazeArray[current_i_xEastWestLeftRight-1][ current_j_yNorthSouthUpDown].cellParameters);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//uint8_tToBluetooth(mazeArray[current_i_xEastWestLeftRight][ current_j_yNorthSouthUpDown].cellParameters);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//uint8_tToBluetooth(current_i_xEastWestLeftRight);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//uint8_tToBluetooth(current_j_yNorthSouthUpDown);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//uint8_tToBluetooth(currentDirection);
		//timerInMilliseconds(5);// can't do more than 5 seconds
		//uint8_tToBluetooth(turnDirection);
		//timerInMilliseconds(5);// can't do more than 5 seconds
}


void chooseDirection()
{

	switch (currentDirection)
	{

        case north:
            /*  has 8 possible scenarios for when we reach 
			*  the center of each square.
			*  If it has more than one option then
			*  it chooses randomly
			*
            * because we are ANDing the cellParameters uint8_t
            * first we check for if we are in a dead-end, 3 walls in front of us
            * , then for 2 walls
            * , then for 1 wall
            * , then no walls
            */

            if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0xb0) == 0xb0))//North(top) ,east(right), and west(left) walls detected
            {
                turnDirection = south; //North(top) ,east(right), and west(left) walls detected... dead-end, turn around (possibility #1)   
                mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters |= 0x04;
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x90) == 0x90) //there are North(top) and west(left) walls 
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = east; //North(top) and west(left) walls detected... go right turn (possibility #2)   
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0xa0) == 0xa0) //there are North(top) and East(right) walls 
                && ((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = west; //North(top) and East(right) walls detected... go left turn (possibility #3)  
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x30) == 0x30) //there are East(right) and west(left) walls 
                && ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = north; //East(right) and west(left) walls detected... go straight (possibility #4)  
                break;
            }
            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x80) == 0x80) //there is a North(top) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//east(right) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //North(top) walls detected... go right(east)(possibility #5)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = west; //North(top) walls detected... go left(west)(possibility #5)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x20) == 0x20) //there is a East(right) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].weightToCenter)//west(left) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
								//uint8_tToBluetooth(mazeArray[current_i_xEastWestLeftRight][ current_j_yNorthSouthUpDown].cellParameters);
								//timerInMilliseconds(5);// can't do more than 5 seconds
//
								//greenRXLEDOn();
                    turnDirection = east; //East(right) walls detected... go left(west)(possibility #6)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = north; //East(right) walls detected... go up(north)(possibility #6)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x10) == 0x10) //there is a West(left) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//East(right) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = west; //West(left) walls detected... go right(east)(possibility #7)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = north; //West(left) walls detected... go up(north)(possibility #7)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x30) == 0x30) //are no walls 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].weightToCenter)//west(left) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //East(right) walls detected... go left(west)(possibility #8)  
                    break;
                }
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].weightToCenter
                    > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//East(right) is closer to the center
                    && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = west; //West(left) walls detected... go right(east)(possibility #8)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = north; //West(left) walls detected... go up(north)(possibility #8)  
                    break;
                }
                else   break;//this would be where the search for next closest unexplored path would be
            }  
            break;
        case south:
            /*  has 8 possible scenarios for when we reach 
    *  the center of each square.
    *  If it has more than one option then
    *  it chooses randomly
    */
            /* because we are ANDing the cellParameters uint8_t
                * first we check for if we are in a dead-end, 3 walls in front of us
                * , then for 2 walls
                * , then for 1 wall
                * , then no walls
                */
            if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x70) == 0x70))//North(top) ,east(right), and west(left) walls detected
            {
                turnDirection = north; //North(top) ,east(right), and west(left) walls detected... dead-end, turn around (possibility #1)   
                mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters |= 0x04;
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x50) == 0x50) //there are South(bottom) and west(left) walls 
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = east; //South(bottom) and west(left) walls detected... go right turn (possibility #2)   
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x60) == 0x60) //there are South(bottom) and East(right) walls 
                && ((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = west; //South(bottom) and East(right) walls detected... go left turn (possibility #3)  
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x30) == 0x30) //there are East(right) and west(left) walls 
                && ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = south; //East(right) and west(left) walls detected... go straight (possibility #4)  
                break;
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x40) == 0x40) //there is a South(bottom) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//east(right) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //South(bottom) walls detected... go right(east)(possibility #5)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = west; //South(bottom) walls detected... go left(west)(possibility #5)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x20) == 0x20) //there is a East(right) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].weightToCenter)//west(left) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //East(right) walls detected... go left(west)(possibility #6)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = south; //East(right) walls detected... go down(south)(possibility #6)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x10) == 0x10) //there is a West(left) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//East(right) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = west; //West(left) walls detected... go right(east)(possibility #7)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = south; //West(left) walls detected... go down(south)(possibility #7)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x00) == 0x00) //are no walls(never happen)
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].weightToCenter)//west(left) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //East(right) walls detected... go left(west)(possibility #8)  
                    break;
                }
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter
                    > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//East(right) is closer to the center
                    && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = west; //West(left) walls detected... go right(east)(possibility #8)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = south; //West(left) walls detected... go down(south)(possibility #8)  
                    break;
                }
                else break;//this would be where the search for next closest unexplored path would be
            }  

            break;
        case east:

            /*  has 8 possible scenarios for when we reach 
    *  the center of each square.
    *  If it has more than one option then
    *  it chooses randomly
    */
            /* because we are ANDing the cellParameters uint8_t
                * first we check for if we are in a dead-end, 3 walls in front of us
                * , then for 2 walls
                * , then for 1 wall
                * , then no walls
                */
            if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0xe0) == 0xe0))//North(top) ,south(bottom), and east(right) walls detected
            {
                turnDirection = west; //North(top) ,south(bottom), and east(right) walls detected... dead-end, turn around (possibility #1)   
                mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters |= 0x04;
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0xa0) == 0xa0) //there are North(top) and East(right) walls 
                && ((mazeArray[current_i_xEastWestLeftRight ] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = south; //North(top) and East(right) walls detected... go right turn (possibility #2)   
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0xc0) == 0xc0) //there are North(top) and South(bottom) walls 
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = east; //North(top) and South(bottom) walls detected... go straight (possibility #3)  
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x60) == 0x60) //there are South(bottom) and East(right) walls 
                && ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = north; //South(Bottom) and East(right) walls detected... go left turn (possibility #4)  
                break;
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x80) == 0x80) //there is a North(top) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//east(right) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //North(top) walls detected... go right(east)(possibility #5)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = south; //North(top) walls detected... go left(west)(possibility #5)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x20) == 0x20) //there is a East(right) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight ] [current_j_yNorthSouthUpDown - 1].weightToCenter)//South(bottom) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = south; //East(right) walls detected... go down(south)(possibility #6)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = north; //East(right) walls detected... go up(north)(possibility #6)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x40) == 0x40) //there is a South(bottom) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//East(right) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //south(bottom) walls detected... go right(east)(possibility #7)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = north; //south(bottom) walls detected... go up(north)(possibility #7)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x00) == 0x00) //are no walls // not happening
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//east(right) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //East(right) walls detected... go straight(east)(possibility #8)  
                    break;
                }
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].weightToCenter
                    > mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter)//south(bottom) is closer to the center
                    && ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = south; //East(right) walls detected... go right(south)(possibility #8)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08))//north(up) is closer to the center and next cell "not visited"
                {
                    turnDirection = north; //East(right) walls detected... go up(north)(possibility #8)  
                    break;
                }
                else break;//this would be where the search for next closest unexplored path would be
            }   

            break;
        case west:
            /*  has 8 possible scenarios for when we reach 
    *  the center of each square.
    *  If it has more than one option then
    *  it chooses randomly
    */
            /* because we are ANDing the cellParameters uint8_t
                * first we check for if we are in a dead-end, 3 walls in front of us
                * , then for 2 walls
                * , then for 1 wall
                * , then no walls
                */
            if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0xd0) == 0xd0))//North(top), south(bottom), and west(left) walls detected
            {
                turnDirection = east; //North(top), south(bottom), and west(left) walls detected... dead-end, turn around (possibility #1)   
                mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters |= 0x04;
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x90) == 0x90) //there are North(top) and West(left) walls 
                && ((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = south; //North(top) and West(left) walls detected... go left turn (possibility #2)   
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0xc0) == 0xc0) //there are North(top) and South(bottom) walls 
                && ((mazeArray[current_i_xEastWestLeftRight - 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = east; //North(top) and South(bottom) walls detected... go straight (possibility #3)  
                break;
            }
            else if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x60) == 0x60) //there are South(bottom) and West(left) walls 
                && ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08)) //and next cell "not visited"
            {
                turnDirection = north; //South(Bottom) and East(right) walls detected... go left turn (possibility #4)  
                break;
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x80) == 0x80) //there is a North(top) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//east(right) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //North(top) walls detected... go right(east)(possibility #5)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = south; //North(top) walls detected... go left(west)(possibility #5)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x20) == 0x20) //there is a East(right) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter)//South(bottom) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = south; //East(right) walls detected... go down(south)(possibility #6)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = north; //East(right) walls detected... go up(north)(possibility #6)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x40) == 0x40) //there is a South(bottom) wall 
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//East(right) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //south(bottom) walls detected... go right(east)(possibility #7)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08))//west(right) is closer to the center and next cell "not visited"
                {
                    turnDirection = north; //south(bottom) walls detected... go up(north)(possibility #7)  
                    break;
                }
            }

            else if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters & 0x00) == 0x00) //are no walls // not happening
            {
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter
                > mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].weightToCenter)//east(right) is closer to the center
                && ((mazeArray[current_i_xEastWestLeftRight + 1] [current_j_yNorthSouthUpDown].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = east; //East(right) walls detected... go straight(east)(possibility #8)  
                    break;
                }
                if ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].weightToCenter
                    > mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].weightToCenter)//south(bottom) is closer to the center
                    && ((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown - 1].cellParameters & 0x08) != 0x08))//and next cell "not visited"
                {
                    turnDirection = south; //East(right) walls detected... go right(south)(possibility #8)  
                    break;
                }
                if (((mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown + 1].cellParameters & 0x08) != 0x08))//north(up) is closer to the center and next cell "not visited"
                {
                    turnDirection = north; //East(right) walls detected... go up(north)(possibility #8)  
                    break;
                }
                else break;//this would be where the search for next closest unexplored path would be
            }  
        break;
			default:
			/* Your code here */
			break;
    } 


}

void faceNextDirection()
{// makes turn and marks cell as "visited"
    switch (turnDirection)
    {
        case north:
			switch (currentDirection)
			{
				case north:
					//already there
				break;
				case south:
					rightEncoder180();
				break;
				case east:

					rightEncoderTurn();
					break;
				case west:
					leftEncoderTurn();
				break;
				//default:
				///* Your code here */
				//break;
			}
            currentDirection = north;
            mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters |= 0x08; // visited
			current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown + 1; // this changes
            break;
        case south:
			switch (currentDirection)
			{
				case north:
					rightEncoder180();				
				break;
				case south:
					//already there
				break;
				case east:
					leftEncoderTurn();
				break;
				case west:
					rightEncoderTurn();
				break;
				//default:
				///* Your code here */
				//break;
			}
			currentDirection = south;
			mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters |= 0x08; // visited
			current_j_yNorthSouthUpDown = current_j_yNorthSouthUpDown - 1; // this changes
            break;
        case east:
			switch (currentDirection)
			{
				case north:
					rightEncoderTurn();
				break;
				case south:
					leftEncoderTurn();
				break;
				case east:
				//already there
				break;
				case west:
					rightEncoder180();
				break;
				//default:
				///* Your code here */
				//break;
			}
			currentDirection = east;
			mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters |= 0x08; // visited
			current_i_xEastWestLeftRight = current_i_xEastWestLeftRight + 1; // this changes
            break;
        case west:
			switch (currentDirection)
			{
				case north:
					leftEncoderTurn();
				break;
				case south:
					rightEncoderTurn();
				break;
				case east:

					rightEncoder180();
				break;
				case west:
				//already there
				break;
				//default:
				///* Your code here */
				//break;
			}
			currentDirection = west;
			mazeArray[current_i_xEastWestLeftRight] [current_j_yNorthSouthUpDown].cellParameters |= 0x08; // visited
			current_i_xEastWestLeftRight = current_i_xEastWestLeftRight - 1; // this changes
            break;
    }
}

/* void createDebugMaze()
{
	//creator debug maze array
	for (uint8_t i = 0; i < ((widthLengthSize * 2) + 1); i++)
	{
		for (uint8_t j = 0; j < ((widthLengthSize * 2) + 1); j++)
		{
			if ((i + 1) % 2 == 0)//odd row
			{
				if ((j + 1) % 2 == 0)//odd column, cell
				{
					"*";
				}
				else //odd row, horizontal wall
				{
					"_";
				}
			}

			else // even row
			{

				if ((j + 1) % 2 == 0)//even column, vertical wall
				{
					"|";
				}
				else
				{//even row, wall pegs
					"*";
				}
			}
		}
	}
}
*/

/******		DELETE WHEN REAL MOVEONEBLOCK IS COMPLETED     *********** 
//void moveOneBlock(void)
//{ 
	////////////////////////////// moveWithPB
	//uint16_t leftWallSensorValue = 0;
	//uint16_t rightWallSensorValue = 0;
	//uint16_t hasLeftWall = 150;
	//uint16_t hasRightWall = 150;
	//uint16_t errorP = 0;
	//uint16_t errorD = 0;
	//uint16_t oldErrorP = 0;
	//uint16_t leftMiddleValue = 182;
	//uint16_t rightMiddleValue = 211;
	//uint16_t totalError16 = 0;
	//uint8_t totalError8 = 0;
	//uint8_t leftBaseSpeed = 50;
	//uint8_t rightBaseSpeed = 50;
	//uint16_t P = 4;
	//uint16_t D = 1;
	//uint16_t testVariable = 0;// test variable
	//for (int8_t x = 10; x < 50; x += 10)//accelerate
	//{
		//leftMotorForward(x);
		//rightMotorForward(x);
		//timerInMilliseconds(20);
	//}
	//rightEncoderAPos = 0;
	//while (rightEncoderAPos < 1200)
	//{
		//leftWallSensorValue = IRSensorAngleLeft();
		//rightWallSensorValue = IRSensorAngleRight();
			//if((leftWallSensorValue > hasLeftWall && rightWallSensorValue > hasRightWall))//has both walls
			//{
				//errorP = rightWallSensorValue - leftWallSensorValue - 29;//29 is the offset between left and right sensor when mouse in the middle of cell
				////errorD = errorP - oldErrorP;
			//}
			//else if((leftWallSensorValue > hasLeftWall))//only has left wall
			//{
				//errorP = 2 * (leftMiddleValue - leftWallSensorValue);
				////errorD = errorP - oldErrorP;
			//}
			//else if((rightWallSensorValue > hasRightWall))//only has right wall
			//{
				//errorP = 2 * (rightWallSensorValue - rightMiddleValue);
				////errorD = errorP - oldErrorP;
			//}
			//else if((leftWallSensorValue < hasLeftWall && rightWallSensorValue < hasRightWall))//no wall, use encoder or gyro
			//{
				//errorP = 0;//(leftEncoder – rightEncoder*1005/1000)*3;
				//errorD = 0;
			//};
			//totalError16 = P * errorP;// + D * errorD;
			//oldErrorP = errorP;
			//totalError8 = (1 << 8) & totalError16;// this is supposed to move the lower 8 bits into this uint_8
			//leftMotorForward(leftBaseSpeed - totalError8);
			//rightMotorForward(rightBaseSpeed + totalError8);
			/////////////////////////test data
			//testVariable++;
			//if (testVariable > 40)
			//{
				//testVariable = 0;
				//intToCharUart(leftWallSensorValue);
			//}
		////PIND |= (1<<PORTD0);  // Pin changed - toggle an LED on PD0
	//}
	//for (int8_t x = 50; x > 0; x -= 10)//accelerate
	//{
		//leftMotorForward(x);
		//rightMotorForward(x);
		//timerInMilliseconds(20);
	//}
	//leftMotorForward(0);
	//rightMotorForward(0);
//}
///	DELETE WHEN REAL MOVEONEBLOCK IS COMPLETED     ********/

int main(void)
{
	RegisterInitialization();
	//greenRXLEDOn();

	while (800 > IRSensorFrontLeft()) //waits for left front sensor to be tripped by user to continue
	{
		timerInMilliseconds(10);
	}

	mazeCellInitialize();
	//createDebugMaze();
    /* Replace with your application code */


    while (1) 
    { 


		timerInMilliseconds(1000);// can't do more than 5 seconds

	    moveOneBlock();
		markWalls();
	    chooseDirection();
		faceNextDirection();
	}	
}


