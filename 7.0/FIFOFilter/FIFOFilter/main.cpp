/*
 * FIFOFilter.cpp
 *
 * Created: 3/15/2018 3:48:44 AM
 * Author : Lee
 */ 


    
	/*Implementation of queue with basic operation using arrays */

#include<stdio.h>      //<iostream>     
using namespace std;        
#define MAX 6               //to accomodate a maximum of 05 elements as 1 cell pointed by tail will always be vacant

void ENQUE(int key);        // ~insertion
int  DEQUEUE();             // ~deletion
void TRAVERSE();
bool isEmpty();
bool isFull ();

int Q[MAX], head=0, tail=0; /* Note: head is the side facing cashier and new person joins the queue at tail. So, from cashier point of view tail~rear and head~front.
                               Q -> [h ][][][][][][][][][][t]
                               Q -> [h,t][][][][][][][][][][] : initial configuration*/



int main(){
    int choice,val,i;
    char ch='y';

    do{
        cout<<"1. For Enqueue \n";
        cout<<"2. For Dequeue \n";
        cout<<"3. For Traverse \nYour Option : ";
        cin>>choice;

        switch(choice)
        {
            case 1 :        // insertion
                if( isFull() ){
                    cout<<"\nQueue Full !!!\n";
                    break;
                }
                cin>>val;
                ENQUE(val);
                TRAVERSE();
                break;

            case 2 :        //deletion
                if( isEmpty() ){
                    cout<<"\nQueue Empty !!!\n";
                    break;
                }
                cout<<"\nDeleted element from Queue : "<<DEQUEUE()<<endl;
                TRAVERSE();
                break;

            case 3 :        //traversal
                if( isEmpty() ){
                    cout<<"\nQueue Empty !!!\n";
                    break;
                }
                TRAVERSE();
                break;

            default :
                cout<<"Please choose 1/2/3 !!! \n";
        }
        cout<<"\nDo you want to continue(y/n):";
        cin>>ch;

    }while(ch=='y'||ch=='Y');  //end of do loop

    return 0;
}

void ENQUE(int x){

    Q[tail] = x;
    tail =(tail+1)%MAX ;       //OR tail =  (tail==MAX) ? 0 : tail+1 ; */
}

int  DEQUEUE(){

    int temp =Q[head];
    head =(head+1)%MAX ;       //OR head =  (head==MAX) ? 0 : head+1 ; */
    return temp;
}

void TRAVERSE(){
    int i;                              //simple  case: Q -> [  ][ ][h7][8][9][5t][  ][  ][  ][  ][  ]
    for(i=head; i!=tail; i=(i+1)% MAX)  //complex case: Q -> [16][t][  ][ ][ ][h5][11][12][13][14][15]
        cout<<Q[i]<<" ";
    cout<<endl;
}

bool isEmpty(){
    if(head == tail)
        return true;
    else
        return false;
}

bool isFull(){
    if( (tail == MAX-1 && head == 0) || (head == tail + 1)  )
        return true;
    else
        return false;
}
	
	

