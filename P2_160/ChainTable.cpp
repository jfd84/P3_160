//
//  ChainTable.cpp
//  P2_160
//
//  Created by Joe D'Agostino on 9/20/22.
//

#include <stdio.h>
#include "ChainTable.h"


ChainTable::ChainTable(unsigned int dictSize)
{
    //time = 0;
    //totalTrans = 0;
    size = dictSize;
}

unsigned int ChainTable::getKey(string word)
{
    unsigned int key = 0;
    
    for(unsigned int i = 0; i < word.length(); ++i)
    {
        key = 37 * key + int(word.at(i));
    }
    key = key % size;
    return key;
}



//Uses an instance of fstream to read file data and fill the array
long ChainTable::loadTable(string fileName)
{
    ifstream inFile;
    inFile.open(fileName.c_str());
    string tempWord;
    unsigned int testKey = 0;
    
    auto start = chrono::steady_clock::now();  //START
    
    arr = new Bucket[size];
    while (inFile >> tempWord)
    {
        testKey = getKey(tempWord);
        arr[testKey].add(tempWord);
    }
    
    auto end = chrono::steady_clock::now();  //END
    
    long time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //Closes stream
    inFile.close();
    return time;
}

//Iterates through array, prints each element
void ChainTable::print()
{
    for (unsigned int i = 0; i < size; ++i)
    {
        cout << "#" << i << ": " << arr[i].size << "  ****  ";
        arr[i].print();
        cout << endl;
    }
    cout << endl << endl;
}

//Iterates through array, prints the number of empty buckets (for analysis of hash function)
void ChainTable::numEmpty()
{
    unsigned int numEmpty = 0;
    for (unsigned int i = 0; i < size; ++i)
    {
        if (arr[i].size == 0)
        {
            ++numEmpty;
        }
    }
    cout << "Number of Empty Buckets: " << numEmpty << " out of " << size << endl << endl;
}


unsigned int ChainTable::readInput(string fileName)
{
    unsigned int numIncorrect = 0;
    bool found;
    fstream inFile;
    inFile.open(fileName.c_str());
    
    string thisWord;
    unsigned int thisKey;
    Node *thisNode = new Node();
    //Parses through each word in the file
    auto start = chrono::steady_clock::now();
    while (inFile >> thisWord)
    {
        //If the word is spelled correctly, the key should reveal the index of the hashTable
        thisKey = getKey(thisWord);
        thisNode = arr[thisKey].header;
        found = false;
        for(unsigned int i = 0; i < arr[thisKey].size; ++i)
        {
            if (thisWord == thisNode->word)
            {
                found = true;
                break;
            }
            thisNode = thisNode->next;
        }
        if (found == false) { numIncorrect+=1; }
    }
    auto end = chrono::steady_clock::now();
    long time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "TIME TO CHECK INPUT: " << time << " nanoseconds" << endl; //REMOVE
    return numIncorrect;
}
