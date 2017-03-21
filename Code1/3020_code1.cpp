//
//  3020_code1.cpp
//  
//
//  Created by Natalie Rakoski on 3/13/17.
//
//

#include "3020_code1.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <bitset>
using namespace std;


double RAN_LCG(unsigned int& in)
{
    int a = 0x43FD43FD;
    int c = 0xC39EC3;
    int m = 1 << 24;
    
    //get output in (0,1) form
    in = ((a * in) + c) % m;
    
    return ((double)in)/(m);
}

double RAN_LFSR(unsigned int& in )
{
    int num = 0;
    
    //x^24 + x^23 + x^22 + x^17 + 1
    
    // "Taps"
    if(in & 0x800000){
        num++;
    }
    if(in & 0x400000){
        num++;
    }
    if(in & 0x20000){
        num++;
    }
    if(in & 0x100000){
        num++;
    }
    
    if(num%2 == 0){         //XOR is 0, shift in a 0
        in = in << 1;
    }
    else {
        in = (in << 1) | 1; //else, shift in a 1
    }
    
    // return result from (0,1)
    in = in & 0xFFFFFF;
    return ((double)in)/(1 << 24); //divide by 2^24
}

void getStats(int nvalues, int count, double arr[][10000], double meanStats[][3], double stdStats[][3])
{
    double stdBI = 0.0;
    double stdLF = 0.0;
    double stdLC = 0.0;
    
    double meanBI = 0.0;
    double meanLF = 0.0;
    double meanLC = 0.0;
    
    //calc mean = [sum of arr] / nvalues
    for(int i = 0; i < nvalues; i++){
        
        meanBI = meanBI + arr[0][i];
        meanLF = meanLF + arr[1][i];
        meanLC = meanLC + arr[2][i];
        
        //store sum of arr data on last loop
        if(i == (nvalues - 1)){
            meanStats[count][0] = meanBI / nvalues;
            meanStats[count][1] = meanLF / nvalues;
            meanStats[count][2] = meanLC / nvalues;
        }
    }
    
    //calc STD = sqrt[ sum[ (arr - mean)^2 ] / nvalues ]
    for(int i = 0; i < nvalues; i++){
    
        stdBI = stdBI + pow((arr[0][i] - meanStats[count][0]),2);
        stdLF = stdLF + pow((arr[1][i] - meanStats[count][1]),2);
        stdLC = stdLC + pow((arr[2][i] - meanStats[count][2]),2);
        
        
        //store std data on last loop
        if(i == (nvalues - 1)){
            stdStats[count][0] = sqrt(stdBI / nvalues);
            stdStats[count][1] = sqrt(stdLF / nvalues);
            stdStats[count][2] = sqrt(stdLC / nvalues);
        }
        
    }
}

int main(){
    unsigned int LFSR = 0xFFFFFF;
    unsigned int LCG = 0xFFFFFF;
    
    double arr[3][10000];
    double meanStats[7][3];
    double stdStats[7][3];
    
    //output using standard output stream cout
    cout << setprecision(8) << left;
    cout << setw(20) << "Built-In Function" << setw(20) << "LFSR" << setw(20) << "LCG" << endl;
    
    //generate random values
    for(int i = 0; i < 10000; i++){
        arr[0][i] = ((double)rand() / (double)RAND_MAX);
        arr[1][i] = RAN_LFSR(LFSR);
        arr[2][i] = RAN_LCG(LCG);
        
        //store 1st 25
        if(i < 25){
            cout << setw(20) << arr[0][i];
            cout << setw(20) << arr[1][i];
            cout << setw(20) << arr[2][i] << endl;
        }
    }
    
    //get stats
    getStats(25,0,arr,meanStats,stdStats);
    getStats(50,1,arr,meanStats,stdStats);
    getStats(100,2,arr,meanStats,stdStats);
    getStats(500,3,arr,meanStats,stdStats);
    getStats(1000,4,arr,meanStats,stdStats);
    getStats(5000,5,arr,meanStats,stdStats);
    getStats(10000,6,arr,meanStats,stdStats);
    
    //output using cout
    cout << right << endl;
    cout << setw(10) << "# of values" << setw(20) << "Built-In Function" << setw(20) << "LFSR        " << setw(20) << "LCG        " << endl;
    cout << setw(10) << "generated" << setw(10) << "mean" << setw(10) << "std dev" << setw(10) << "mean" << setw(10) << "std dev" << setw(10) << "mean" << setw(10) << "std dev" << endl;
    cout << endl;
    cout << setw(10) << "  25"    << setw(10) << meanStats[0][0] << setw(10) << stdStats[0][0] << setw(10) << meanStats[0][1] << setw(10) << stdStats[0][1] << setw(10) << meanStats[0][2] << setw(10) << stdStats[0][2] << endl;
    cout << setw(10) << "  50"    << setw(10) << meanStats[1][0] << setw(10) << stdStats[1][0] << setw(10) << meanStats[1][1] << setw(10) << stdStats[1][1] << setw(10) << meanStats[1][2] << setw(10) << stdStats[1][2] << endl;
    cout << setw(10) << "  100"   << setw(10) << meanStats[2][0] << setw(10) << stdStats[2][0] << setw(10) << meanStats[2][1] << setw(10) << stdStats[2][1] << setw(10) << meanStats[2][2] << setw(10) << stdStats[2][2] << endl;
    cout << setw(10) << "  500"   << setw(10) << meanStats[3][0] << setw(10) << stdStats[3][0] << setw(10) << meanStats[3][1] << setw(10) << stdStats[3][1] << setw(10) << meanStats[3][2] << setw(10) << stdStats[3][2] << endl;
    cout << setw(10) << "  1000"  << setw(10) << meanStats[4][0] << setw(10) << stdStats[4][0] << setw(10) << meanStats[4][1] << setw(10) << stdStats[4][1] << setw(10) << meanStats[4][2] << setw(10) << stdStats[4][2] << endl;
    cout << setw(10) << "  5000"  << setw(10) << meanStats[5][0] << setw(10) << stdStats[5][0] << setw(10) << meanStats[5][1] << setw(10) << stdStats[5][1] << setw(10) << meanStats[5][2] << setw(10) << stdStats[5][2] << endl;
    cout << setw(10) << "  10000" << setw(10) << meanStats[6][0] << setw(10) << stdStats[6][0] << setw(10) << meanStats[6][1] << setw(10) << stdStats[6][1] << setw(10) << meanStats[6][2] << setw(10) << stdStats[6][2] << endl;
    
    
}









