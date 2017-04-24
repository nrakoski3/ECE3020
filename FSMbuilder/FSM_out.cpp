//
//  FSM_out.cpp
//  FSMbuilder
//
//  Created by Natalie Rakoski on 4/23/17.
//
//

#include "FSM_out.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <bitset>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

typedef struct NODE
{
    NODE* nextAlph;         // Next pointer to a NODE of linked list in Alphebetical Order
    string*  name;            // Pointer to name the user defined
    int   defInputs[32];   // Arry of 0's or 1's corrrespinding to what inputs the user has defined.
    NODE  *nextState[32];   // Moore, only. Array of NODE pointers, every input (in boolean order: 00,01,10,11), has a pointer to the next state.
                            // Initializes as an array of NULL pointers the size of the total inputs possible, after the user specifies input #
    string  *mealyOutputs[32];//For Mealy: Array of pointers to the names of outputs that the user has defined
                            //Ever input combination has its own output.
    string*  mooreOutput;     // If Moore, each state(node) has 1 corresponding output. This is the pointer to that output, which lies
                            // in a list of outputs that the user has defined so far.

} state_t;

int main(){

    //char *statenames[statenum];           // array of pointers to stings that user entered as statenames;
    //char *statenamesAlph[statenum];       // array of pointers to stings that user entered as statenames in alphebetical order;

    //Generated using FST specifications
    int statenum = 2;
    int inputnum = 2;       //Example: 2 -> X1X2 = ['00','01','10','11']
    int numPossInputs = pow(2, inputnum); // = 4
    bool type = 0;      //Moore = 0
    cout<<"Begin"<< endl;
    //int definedInputs[] = {0,0,0,0}; // 0 or 1 if user has defined input
    const string possinputs[] = {"00", "01", "10", "11"};



    //Generated by user putting in data
    string outputs[32];
    outputs[0] = "hot";
    outputs[1] = "cold";
    outputs[2] = "off";

    string states[25];
    states[0] = "Red";
    states[1] = "Blue";
    int userInput = 3;
    int numPossible = pow(2,userInput);
    string StrArray[numPossible];
    //int numPossible = pow(2,UserInput)
    string nums1[] = {"0", "1"};
    string nums2[] = {"00", "01", "10", "11"};
    string nums3[] = {"000", "001", "010", "011", "100", "101","110", "111"};
    string nums4[] = {"0000", "0001", "0010", "0011", "0100", "0101","0110", "0111", "1000", "1001", "1010","1011", "1100","1101", "1110", "1111"};
    string nums5[] = {"00000", "00001", "00010", "00011", "00100", "00101","00110", "00111", "01000", "01001", "01010","01011", "01100","01101", "01110", "01111","10000","10001", "10010", "10011", "10100","10101","10111","11000", "11001" , "11010","11011","11100","11101","11110", "11111"};
    switch(userInput){
      case 1:
        for(int i=0; i < numPossible; i++)
          StrArray[i] = nums1[i];
        break;
      case 2:
        for(int i=0; i < numPossible; i++)
          StrArray[i] = nums2[i];
        break;
      case 3:
        for(int i=0; i < numPossible; i++)
          StrArray[i] = nums3[i];
        break;
      case 4:
        for(int i=0; i < numPossible; i++)
          StrArray[i] = nums4[i];
        break;
      case 5:
        for(int i=0; i < numPossible; i++)
          StrArray[i] = nums5[i];
        break;
      };

    // Build
    cout<< "Begin Build:"<< endl;

    NODE **nodes;       //Pointer to pointer or type NODE
    nodes = new NODE *[statenum];
    nodes[0] = new NODE;
    nodes[1] = new NODE;

    //test name
    nodes[0]->name = &states[0];
    nodes[1]->name = &states[1];
    cout<< *(nodes[0]->name) << endl;  // output node name
    cout<< *(nodes[1]->name) << endl;

    //test defInputs
    cout<< nodes[0]->defInputs[0] << endl;

    //test nextState
    //nodes[1] = new NODE;
    nodes[1]->name = &states[1];
    cout << nodes[1] << endl; //prints address to nodes[1]

    nodes[0]->nextState[0] = nodes[1];              //sets node[0].nextState[0](next state of input'00') = nodes[1] (state Blue)
    cout<< *(nodes[0]->nextState[0])->name << endl; //gives the name of the next state

    //test mealyOutputs
    nodes[1]->mealyOutputs[0] = &outputs[0];// set to
    cout<< *(nodes[1]->mealyOutputs[0]) << endl; //gives the name of the output

    //test mooreOutput
    nodes[0]->mooreOutput = &outputs[1];
    cout<< *(nodes[0]->mooreOutput) << endl;

    //test NodeAlph
    NODE **nodesAlph;
    nodesAlph = new NODE *[statenum];
    nodesAlph[0] = nodes[1];
    nodesAlph[1] = nodes[0];

    cout<< *(nodesAlph[0]->name) << endl;
    cout<< *(nodesAlph[1]->name) << endl;
    //Create Moore Table/Graph
    if(type == 0){
      cout<<"Output Graph" << endl<<endl;
      for(int i = 0; i < statenum; i++){
          cout<< *(nodes[0]->name) << endl;  // output node name
          for(int j= 0; j < numPossible; j++){
            cout<< setw(10)<< *(nodes[0]->nextState[0])->name << setw(10)<< StrArray[0]<< "/"<<  *(nodes[0]->mooreOutput)  ; //output next state
        }
        cout<<endl;
      }
      cout<< "Output Table" << endl<<endl;
      cout<< "Current" <<  setw(8)<< "|"<< setw(10)<< "Next State/Output"<<endl;
      cout<< "State" << setw(10)<<"|" << setw(10);
      for(int i = 0; i < numPossible; i++){
        cout<<"X = "<< StrArray[0]<<setw(10);
      }
      cout<<endl;
      for(int i =0; i <statenum; i++ )
        cout<< *(nodes[0]->name) << setw(10)<< "|"<<setw(10);
        for(int j = 0; j< numPossible; j++){
          cout<< *(nodes[0]->nextState[0])->name<< "/"<< *(nodes[0]->mooreOutput) << setw(10);
        }
        cout<< endl;
    }
    else{         // Mealy Graph
      cout<<"Output Graph" << endl<<endl;
      for(int i = 0; i < statenum; i++){
          cout<< *(nodes[0]->name) << endl;  // output node name
          for(int j= 0; j < numPossible; j++){
            cout<< setw(10)<< *(nodes[0]->nextState[0])->name << setw(10)<< StrArray[0]<< "/"<<  *(nodes[0]->mooreOutput)  ; //output next state
        }
        cout<<endl;
      }
      cout<< "Output Table" << endl<<endl;
      cout<< "Current" <<  setw(10)<< "|"<< setw(10)<< "Next State/Output"<<endl;
      cout<< "State" << setw(10)<<"|";
      for(int i = 0; i < numPossible; i++){
        cout<<"X = "<< StrArray[i]<<setw(10);
      }
      cout<<endl;
      cout<< "_____________________________________________________" <<endl;
      for(int i =0; i <statenum; i++ )
        cout<< *(nodes[0]->name) << setw(10)<< "|"<<setw(10);
        for(int j = 0; j< numPossible; j++){
          cout<< *(nodes[0]->nextState[0])->name<< "/"<<  *(nodes[1]->mealyOutputs[0])  << setw(10);
        }
        cout<< endl;
    }

}


/*
void  BinaryNums(string* StrArray, int userInput){
  //int numPossible = pow(2,UserInput)
  string nums1[] = {"0", "1"};
  string nums2[] = {"00", "01", "10", "11"};
  string nums3[] = {"000", "001", "010", "011", "100", "101","110", "111"};
  string nums4[] = {"0000", "0001", "0010", "0011", "0100", "0101","0110", "0111", "1000", "1001", "1010","1011", "1100","1101", "1110", "1111"};
  string nums5[] = {"00000", "00001", "00010", "00011", "00100", "00101","00110", "00111", "01000", "01001", "01010","01011", "01100","01101", "01110", "01111","10000","10001", "10010", "10011", "10100","10101","10111","11000", "11001" , "11010","11011","11100","11101","11110", "11111"};
  switch(userInput){
    case 1:
        StrArray = nums1;

      break;
    case 2:
        StrArray = nums2;
      break;
    case 3:
      StrArray = nums3;
      break;
    case 4:
      StrArray = nums4;
      break;
    case 5:
      StrArray = nums5;
      break;
  }


}
*/
