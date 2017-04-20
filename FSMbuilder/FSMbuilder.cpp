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
using namespace std;

/* Rules for Finite State Machine Generator (FSM)
 1. At most 4 inputs per state (Node)
 2. At most 25 states
 3. User Inputs
    * Mealy State Machine
    - NODE "name"
    - Arc  "fromNode toNode inputs/ output"
 
    * Moore State Machine
    - NODE "name"
    - Arc  "fromNode toNode input"
 4. inputs = 0,1, x(don't care)
 5. NODE must be defined by user before it can be used in an ARC statement
 6. Program Outputs
    - Graph:
        - List all Nodes in alphebetical order by state name (if Moore: followed by state output (Z))
        - Transition arcs listed (no order) on following lines with:
            - destination state name
            - input values that cause transition
            - (If Mealy: associatd output value)
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








