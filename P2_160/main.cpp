//
//  main.cpp
//  P2_160
//
//  Created by Joe D'Agostino on 9/19/22.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include "ChainTable.h"

using namespace std;

int main(int argc, const char * argv[]) {

    //Ensures that an argument (path for dictionary) was passed. If not, requests run time input
    string dictName;
    if (argv[1] == NULL) {
        cout << "NO FILE PATH PASSED WHEN CALLING EXECUTABLE" << endl;
        cout << "Please enter file path: ";
        //cin >> dictName;
        dictName = "/Users/jfd/Desktop/COSC_160/P2_160/P2_160/dictionaryFile1.txt";
        cout << endl;
    }
    else {
        dictName = argv[1];
    }
    
    //Opens stream of file
    ifstream inFile;
    inFile.open(dictName.c_str());
    //Quickly loops through file to determine total size
    unsigned int dictSize = 0;
    string tempWord;
    while(inFile)
    {
        getline(inFile, tempWord);
        ++dictSize;
    }
    //Closes stream
    inFile.close();
    
    
    //Multiplies dictSize by 1.33 and rounds up, to ensure that the load is not < 0.75
    dictSize = ceil(dictSize * 1.33);
    //Makes sure that dictSize is not an even number
    if (dictSize % 2 != 0) { ++dictSize; }
    
    //Creates "chain" an instance of the ChainTable class
    ChainTable chain(dictSize);
    //Calls the loadTable() function of the ChainTable class, which returns time taken to construct
    
    long time = chain.loadTable(dictName);
    
    //chain.print(); //REMOVE
    cout << "TIME TO LOAD: " << time << " nanoseconds" << endl; //REMOVE
    chain.numEmpty(); //REMOVE
    
    
    //Ensures that a 2nd argument (path for input) was passed. If not, requests run time input
    string inputName;
    if (argv[1] == NULL) {
        cout << endl << "NO FILE PATH PASSED WHEN CALLING EXECUTABLE" << endl;
        cout << "Please enter file path: ";
        cin >> inputName;
        cout << endl;
    }
    else {
        dictName = argv[2];
    }
    unsigned int numIncorrect = chain.readInput(inputName);
    cout << "# Misspelled: " << numIncorrect << endl;
    
    
    
    
    return 0;
}
