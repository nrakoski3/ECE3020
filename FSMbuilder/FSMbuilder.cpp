//
//  FSMbuilder.cpp
//  FSMbuilder
//
//  Created by Natalie Rakoski on 4/20/17.
//
//

#include "FSMbuilder.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <bitset>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

/* Rules for Finite State Machine Generator (FSM)
 1. At most 4 inputs per state (Node)
 2. At most 25 states
 3. User Inputs
    * Mealy State Machine
    - NODE "name"
    - Arc  "fromNode toNode inputs/ output"

    * Moore State Machine
    - NODE "name/ Z(output)"
    - Arc  "fromNode toNode input"
 4. inputs = 0,1, x(don't care)
 5. NODE must be defined by user before it can be used in an ARC statement
 6. Program Outputs
    - Graph:
        - List all Nodes in alphebetical order by state name (if Moore: followed by state output (Z))
        - Transition arcs listed (no order) on following lines with:
            - destination state name
            - input values that cause transition
            - (If Mealy: associated output value)
    - Error Correction
        - For each Node determine if are either incompletely specified or conflicting
            -Ex. if 2 input bits then per state:
                - there should be inputs 00,01,10,11 specified
                - there should not be duplicates of inputs that have different destinations
    - Table
        - Each Node specified in alphebetical order by state name
        - For each state list list inputs and (Moore: next state)/ (Mealy: output)
        - If inputs incompletely specified, use "x"(don't care), if inputs conflicting list "error" for:
            -(If Moore: for the next state)
            -(If Mealy: for the output)
*/


typedef struct NODE
{
    NODE* nextAlph;         // Next pointer to a NODE of linked list in Alphebetical Order
    string*  name;            // Pointer to name the user defined
    int   defInputs[32];   // Arry of 0's or 1's corrrespinding to what inputs the user has defined.
    NODE  *nextState[32];   //Array of NODE pointers, every input (in boolean order: 00,01,10,11), has a pointer to the next state.
    // Initializes as an array of NULL pointers the size of the total inputs possible, after the user specifies input #
    string  *mealyOutputs[32];//For Mealy: Array of pointers to the names of outputs that the user has defined
    //Ever input combination has its own output.
    string*  mooreOutput;     // If Moore, each state(node) has 1 corresponding output. This is the pointer to that output, which lies
    // in a list of outputs that the user has defined so far.

} state_t;


void main(){

    // 1. initial setup
    NODE **nodes;       //Pointer to pointer or type NODE
    int statenum;
    int inputnum;       //Example: 2 -> X1X2 = ['00','01','10','11']
    int temp;
    bool type = false;


    // 2. Ask user for state machine specifications
    cout<<"Enter Number of States Desired:"<<endl;
    cin  >> statenum;
    cout<<"Enter Number of Inputs Desired:"<<endl;
    cin  >> inputnum;
    int numPossibleInputs = pow(2, intputnum);
    string possInputs[numPossibleInputs];
    cout<<"Enter 0 for Moore FST, 1 for Mealy FST:"<<endl;
    cin  >> temp;

    // 3. Initiate Build
    if (temp == 0){         //if Moore
        type = true;
        string outputs[statenum];
        string states[statenum];
    } else {                //if Mealy
        type = true;
        string outputs[numPossibleInputs];
        string states[statenum];
    }
    nodes = new NODE *[statenum];                     // Declares array of pointers to NODEs
    //buildNodes(nodes, stateNum, inputNum, type);      // Builds list of node pointers
    for(int i; i < stateNum; i++){
        nodes[i] = new NODE;            //Initializes state[i]
    }
    // 4. create function that will make sting array of all possible inputs
    //const string possinputs[] = {"00", "01", "10", "11"};


    // 5. start parsing user input and assign data to parts of nodes
            // check for user error
    cout<<"Begin entering FSM specifications:"<<endl;

    string cmd, statein, stateout, input, output;
    int statein_ind, stateout_ind, input_ind, output_ind;
    //stingA.compare(stringB)
    int nodenum = 0;
    int outputnum = 0;

    while(true){

        cout<<"Type ""NODE"" or ""ARC"", when finished type ""END"":"<<endl;
        cin >> cmd;

        if (cmd == "NODE"){

            if (type == 0) {    //if Moore
                cout<<"Type ""stateName"" ""stateOutput"" :"<<endl;
                cin >> states[nodenum] >> outputs[outputnum];

                nodes[nodenum]->name = &states[nodenum];
                nodes[nodenum]->mooreOutput = &outputs[outputnum];

                outputnum += 1;

            } else{             //if Mealy
                cout<<"Type ""stateName"" :"<<endl;
                cin >> states[nodenum];
                nodes[nodenum]->name = &states[nodenum];
            }

            nodenum += 1;

        } else if(cmd == "ARC"){

            if (type == 0) {    //if Moore

                cout<<"Type ""stateIn"" ""stateOut"" ""input(Ex: X1X2X3 = 000)"" :"<<endl;
                cin >> statein >> stateout >> input;

                // Find indexes
                statein_ind = -1;
                stateout_ind = -1;
                for(int i; i<nodenum; i++){
                    if(states[i].compare(statein) == 0){
                        statein_ind = i;
                    }
                    if(states[i].compare(stateout) == 0){
                        stateout_ind = i;
                    }
                }
                //check if User has not defined state
                if((statein_ind == -1) or (stateout_ind == -1)){
                    cout<<"Error:User has not created NODE stateIn or NODE stateOut."<<endl;
                } else{

                    for(int i; i<numPossibleInputs; i++){

                        if(possInputs[i].compare(input) == 0){
                            input_ind = i;
                        }
                    }

                    // Check if input has been defined before
                    if(nodes[statein_ind]->defInputs[input_ind] == 1){

                    }

                    // add pointer to stateout into nextState of statein in the correct place
                    nodes[statein_ind]->nextState[input_ind] = nodes[stateout_ind];
                    // mark defInputs
                    nodes[statein_ind]->defInputs[input_ind] = 1;
                }
            }


            } else{             //if Mealy

                cout<<"Type ""stateIn"" ""stateOut"" ""input(Ex: X1X2X3 = 000)"" ""output"":"<<endl;
                cin >> statein >> stateout >> input >> output;

                // Find indexes
                statein_ind = -1;
                stateout_ind = -1;
                output_ind = -1;
                for(int i; i<nodenum; i++){
                    if(states[i].compare(statein) == 0){
                        statein_ind = i;
                    }
                    if(states[i].compare(stateout) == 0){
                        stateout_ind = i;
                    }
                }
                //check if User has not defined state
                if((statein_ind == -1) or (stateout_ind == -1)){
                    cout<<"Error:User has not created NODE stateIn or NODE stateOut."<<endl;
                } else{


                    for(int i; i<numPossibleInputs; i++){

                        if(possInputs[i].compare(input) == 0){
                            input_ind = i;
                        }
                        if(outputs[i].compare(output) == 0){
                            output_ind = i;
                        }
                    }


                    //check if output has not been defined before
                    if(output_ind == -1){
                        outputs[outputnum] = output;
                        output_ind = outputnum;
                        outputnum += 1;
                    }

                    // add pointer to stateout into nextState of statein in the correct place
                    nodes[statein_ind]->nextState[input_ind] = nodes[stateout_ind];
                    // add pointer to output into mealyOutputs of statein in the correct place
                    nodes[statein_ind]->mealyOutputs[input_ind] = &outputs[output_ind];
                    // mark defInputs
                    nodes[statein_ind]->defInputs[input_ind] = 1;
                }
            }



        } else if(cmd == "END"){ // User ends operation
            break;
        } else{
            cout<<"User did not enter ""NODE"", ""ARC"", or ""END""."<<endl;
        }
    }//end while

    // 8. check for user error, such as not defining states or defining the different outputs for the same input

    // 7. alphebetize state(node) names and link the nodes in the appropriate order (nextAlph var of NODE struct)


    // 9. COUT Graph and Table from information in linked list of nodes
    //int userInput = 3;
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

  //  NODE **nodes;           //Pointer to pointer or type NODE
  //  nodes = new NODE *[statenum];
  //  nodes[0] = new NODE;
  //  nodes[1] = new NODE;

    cout<< *(nodesAlph[0]->name) << endl;
    cout<< *(nodesAlph[1]->name) << endl;
    //Create Moore Table/Graph
    if(type == 0){
      cout<<"Output Graph" << endl<<endl;
      for(int i = 0; i < statenum; i++){
          cout<< *(nodes[i]->name) << endl;  // output node name
          for(int j= 0; j < numPossible; j++){
            cout<< setw(10)<< *(nodes[j]->nextState[j])->name << setw(10)<< StrArray[j]<< "/"<<  *(nodes[j]->mooreOutput)  ; //output next state
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
    /* Example of how to work with COUT
     cout<<"enter1:"<<endl;
     cin  >> Car[0]->RegCode;
     cout<<"you entered"<<endl;
     cout<<Car[0]->RegCode<<endl;
     system("pause");
     */


/*
 Trash Code

 char* str;                                                       //char* strarray[] = {"hey", "sup", "dogg"};
 vector<string> strvector;
 char* strarray[];
 //std::vector<std::string> strInputs[];                          // syntax std::vector<std::string> v = {"Hello", "World"};
 */
