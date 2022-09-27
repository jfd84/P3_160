//
// Created by Joe D'Agostino on 9/23/22.
//

#ifndef P2_160_QUADRATICTABLE_H
#define P2_160_QUADRATICTABLE_H

#include <cstdio>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cctype>
#include <cmath>
using namespace std;

class QuadraticTable {
public:
    //Creates an array with the size specified in the first line of the file
    QuadraticTable(unsigned int dSize, unsigned int iSize);

    unsigned int getKey(const string &word) const;

    //Creates an instance of fstream to read file data and fill the table
    long loadTable(string fileName);

    //Iterates through array, prints the number of empty buckets (for analysis of hash function)
    unsigned int readInput(string fileName);

    void numEmpty();

    //Iterates through array, prints each element
    void print();

    unsigned int dictSize;
    unsigned int inputSize;
    string *arr;
    long inputDuration;


}; //END QuadraticTable Declaration


#endif //P2_160_QUADRATICTABLE_H
