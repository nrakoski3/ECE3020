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
    char  name;             // Name the user defined
    char  *inputs[];        // Array of pointers to arrays that list all possible inputs( 2^5 > 25 states, 5 inputs at most)
    NODE  *nextState[];     // Array of NODE pointers, every input (in boolean order: 00,01,10,11), has a pointer to the next state.
                            // Initializes as an array of NULL pointers the size of the total inputs possible, after the user specifies input #
    
    int   defInputs[];      // Array of the inputs the user has defined, the index corresponds to the index in boolean order.
                            // Total length is length of all possible inputs. 0 = false, 1 = true, initiallizes as all 0's
    
    int   defOutputs[];     // Array of the inputs the user has defined, the index corresponds to the index in boolean order.
                            // Total length is length of all possible inputs. 0 = false, 1 = true, initiallizes as all 0's
    
    char  *mealyOutputs[];  // For Mealy: Array of output pointers the size of the number of possible inputs, each ptr corresponding to a
                            // possible output the user defined the index corresponds to the corresponding input in boolean order.
    
    char*  mooreOutput;     // If Moore, each state(node) has 1 corresponding output. This is the pointer to that output, which lies
                            // is a list of outputs that the user has defined so far.
    
} state_t;


void buildNodes(nodeArr, stateNum, inputNum, type){
    // take user definitions of state machine and build the array of pointers to Nodes
    
    int numPossibleInputs = pow(2, intputNum);
    int inputArr[numPossibleInputs];    //Array of 0's and 1's that marks what has been defined by the user
    int outputArr[numPossibleInputs];   //Array of 0's and 1's that marks what has been defined by the user
    
    
    
    // build array of inputs and outputs yet to be defined, 0 = false, 1 = true
    for(int i; i < inputNum; i++){
        inputArr[i] = 0;
        outputArr[i] = 0;
    }
    
    for(int i; i < stateNum; i++){
        nodes[i] = new NODE;            //Initializes state[i]
    
        // Inputs that the user has defined Outputs for, initiallizes as an array of 'x' the size of # possible outputs
        // like: ['x','x','x','x'] for eventually ['00','01','10','11']
        
    }
    
}

void addStateInfo(fromState, input, twoState, output){

    
}

void AddAtTail(state_t* s)
{
    if (tail == NULL)
    { // First entry in list
        head = s;
    }
    else
    { // link new element from previous tail
        tail->next = s;
    }
    s->prior = tail; // New element is new tail and prior is old tail
    s->next = NULL;  // New element has no next
    tail = s;
}

void PrintNameList()
{
    state_t* h = head;
    while(h != NULL)
    {
        printf("fn %s mn %s ln %s average %f grade %c\n",
               h->fname, h->mname, h->lname, h->average, h->letterGrade);
        h = h->next;
    }
}



void main(){
    
    // initial setup
    NODE **nodes;       //Pointer to pointer or type NODE
    int statenum;
    int inputnum;       //Example: 2 -> X1X2 = ['00','01','10','11']
    int numPossibleInputs = pow(2, intputNum);
    int temp;
    bool type;
    
    // store user entered data
    char *outputs[];                // array of pointers to stings that user entered as outputs;
    
    // Ask user for state machine specifications
    cout<<"Enter Number of States Desired:"<<endl;
    cin  >> statenum;
    cout<<"Enter Number of Inputs Desired:"<<endl;
    cin  >> inputnum;
    cout<<"Enter 0 for Moore FST, 1 for Mealy FST:"<<endl;
    cin  >> temp;
    // add if statment to go from temp to type
    
    
    nodes = new NODE *[statenum];                     // Declares array of pointers to NODEs
    buildNodes(nodes, stateNum, inputNum, type);      // Builds list of node pointers
    

    
    
    
    
    
    /* Example of how to work with COUT
     cout<<"enter1:"<<endl;
     cin  >> Car[0]->RegCode;
     cout<<"you entered"<<endl;
     cout<<Car[0]->RegCode<<endl;
     system("pause");
     */

}

/*
 Trash Code
 
 char* str;                                                       //char* strarray[] = {"hey", "sup", "dogg"};
 vector<string> strvector;
 char* strarray[];
 //std::vector<std::string> strInputs[];                          // syntax std::vector<std::string> v = {"Hello", "World"};
 */






