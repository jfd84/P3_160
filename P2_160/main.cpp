//
//  main.cpp
//  P2_160
//
//  Created by Joe D'Agostino on 9/19/22.
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include "ChainTable.h"
#include "QuadraticTable.h"

using namespace std;

int main(int argc, const char * argv[]) {
    //Ensures that an argument (path for dictionary) was passed. If not, requests run time input
    string dictName = argv[1];
    
    //Opens stream of file
    ifstream inFile;
    unsigned int dictSize = 0;
    inFile.open(dictName.c_str());
    //Quickly loops through file to determine total size
    string tempWord;

    while(inFile >> tempWord) { ++dictSize; }

    //Closes stream
    inFile.close();

    string inputName = argv[2];
    unsigned int inputSize = 0;
    string thisWord;
    inFile.open(inputName.c_str());

    int splitIndex;
    int numHyphen = 0;
    while(inFile >> thisWord)
    {
        splitIndex = 0;
        ++inputSize;
        splitIndex = thisWord.find("-");
        if (splitIndex != -1) { ++numHyphen; }
    }
    inFile.close();
    inputSize = inputSize + (numHyphen);
    
    
    //Multiplies dictSize by 1.33 and rounds up, to ensure that the load is not < 0.75
    dictSize = ceil(dictSize * 1.33);
    //Makes sure that dictSize is not an even number
    if (dictSize % 2 != 0) { ++dictSize; }

    //*********************************************************************************************************
    //Creates "chain" an instance of the ChainTable class
    ChainTable chain(dictSize, inputSize);
    //Calls the loadTable() function of the ChainTable class, which returns time taken to construct
    long time = chain.loadTable(dictName);
    cout << "Time taken to construct hashTable1 (chaining): " << time << " nanoseconds" << endl;

    unsigned int numIncorrect = chain.readInput(inputName);
    cout << "Duration of input check (chaining): " << chain.inputDuration << " nanoseconds" << endl;
    cout << "Total number of words that hashtable1 (chaining) considers misspelled: " << numIncorrect << endl;
    //*********************************************************************************************************
    cout << endl;
    //Creates QuadraticTable object. increases dictSize to give the hash table a 0.5 load, common for quadratic probing
    QuadraticTable quad(int((dictSize/1.33)*2), inputSize);
    time = quad.loadTable(dictName);
    cout << "Time taken to construct hashTable2 (quadratic): " << time << " nanoseconds" << endl;

    numIncorrect = quad.readInput(inputName);
    cout << "Duration of input check (quadratic): " << quad.inputDuration << " nanoseconds" << endl;
    cout << "Total number of words that hashtable2 (quadratic) considers misspelled: " << numIncorrect << endl;
    cout << endl;

    if (quad.inputDuration < chain.inputDuration) {
        cout << "Quadratic Probing is MORE efficient in this instance." << endl;
    }
    else { cout << "Chaining is MORE efficient in this instance." << endl; }

    return 0;
}
