//
// Created by Joe D'Agostino on 9/23/22.
//

#include "QuadraticTable.h"

QuadraticTable::QuadraticTable(unsigned int dSize, unsigned int iSize)
{
    dictSize = dSize;
    inputSize = iSize;
    arr = new string[dSize];
    inputDuration = 0;
}

unsigned int QuadraticTable::getKey(const string &word) const
{
    unsigned int key = 0;
    for (char i:word) { key = 37 * (key + short(i)); }
    return key % dictSize;
}

long QuadraticTable::loadTable(string fileName) {
    ifstream inFile;
    inFile.open(fileName.c_str());
    string tempWord;
    unsigned int key;
    unsigned int thisProbe;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now(); //START
    while (inFile >> tempWord)
    {
        key = getKey(tempWord);
        thisProbe = 1;
        while (arr[key].size() != 0) {
            key = int(key + pow(thisProbe, 2)) % dictSize;
            ++thisProbe;
        }
        arr[key] = tempWord;
    }
    chrono::high_resolution_clock::time_point stop = chrono::high_resolution_clock::now(); //STOP
    long time = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    //Closes stream
    inFile.close();
    return time;
}
unsigned int QuadraticTable::readInput(string fileName)
{
    ifstream inFile;
    inFile.open(fileName.c_str());
    string tempWord;
    string tempArray[inputSize];
    int splitIndex;
    int doubleIndex;
    string splitWord1;
    string splitWord2;
    int i = 0;

    //Parses through the input file, cleans up issues with strings, and stores each string to a temporary array.
    while (inFile >> tempWord)
    {
        splitIndex = 0;
        doubleIndex = 0;

        if (tempWord.empty()) { continue; }
        while (ispunct(tempWord.back())) { tempWord.pop_back(); if (tempWord.empty()) { break; } }
        if (tempWord.empty()) { continue; }
        while (ispunct(tempWord.front())) {tempWord.erase(0, 1); if (tempWord.empty()) { break; } }
        if (tempWord.empty()) { continue; }
        if (tempWord.back() == 's')
        {
            if (ispunct(tempWord[tempWord.length()-2])) { tempWord.erase(tempWord.length()-2,2); }
        }
        if (tempWord.empty()) { continue; }
        if (tempWord.front() >='A' && tempWord.front() <= 'Z')
        {
            tempWord[0] = char(tempWord[0] + 32);
            if (tempWord[1] >='A' && tempWord[1] <= 'Z')
            {
                for(unsigned int j = 1; j < tempWord.length(); ++j) { tempWord[j] = char(tempWord[j] + 32); }
            }
        }
        splitIndex = int(tempWord.find('-'));
        if (splitIndex != -1)
        {
            doubleIndex = int(tempWord.find("--"));
            splitWord1 = tempWord.substr(0, splitIndex);
            if (doubleIndex != -1) { splitWord2 = tempWord.substr(splitIndex+2, tempWord.length() - splitIndex-1); }
            else { splitWord2 = tempWord.substr(splitIndex+1, tempWord.length() - splitIndex-2); }
            if (splitWord1.empty()) { continue; }
            while (ispunct(splitWord1.back())) { splitWord1.pop_back();  if (splitWord1.empty()) { break; } }
            if (splitWord2.empty()) { continue; }
            while (ispunct(splitWord2.back())) { splitWord2.pop_back();  if (splitWord2.empty()) { break; } }
            if (splitWord1.empty()) { continue; }
            while (ispunct(splitWord1.front())) { splitWord1.erase(0, 1); if(splitWord1.empty()) { break; } }
            if (splitWord2.empty()) { continue; }
            while (ispunct(splitWord2.front())) { splitWord2.erase(0, 1); if(splitWord2.empty()) { break; } }

            if (isdigit(splitWord1.front())) { continue; }
            if (isdigit(splitWord2.front())) { continue; }

            tempArray[i] = splitWord1;
            tempArray[i+1] = splitWord2;
            i += 2;
        }
        else {
            if (isdigit(tempWord.front())) { continue; }
            tempArray[i] = tempWord;
            ++i;
        }
    }
    inFile.close();

    //Creates variables necessary for operations in the proceeding while loop
    string thisWord;
    unsigned int testKey;
    unsigned int numIncorrect = 0;
    bool found;
    //Parses through each word in the file, and check if it exists in the hash table
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();  //START
    for (unsigned int i = 0; i < inputSize; ++i)
    {
        if (tempArray[i].empty()) { continue; }
        thisWord = tempArray[i];
        //If the word is spelled correctly, the key should reveal the index of the hashTable
        testKey = getKey(thisWord);
        found = false;
        unsigned int thisProbe = 0;

        while(!arr[testKey].empty())
        {
            if (thisWord == arr[testKey])
            {
                found = true;
                break;
            }
            testKey = int(testKey + pow(thisProbe, 2)) % dictSize;
            ++thisProbe;
        }
        if (!found) { ++numIncorrect; }
    }
    chrono::high_resolution_clock::time_point stop = chrono::high_resolution_clock::now();  //STOP
    long time = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    inputDuration = time;

    return numIncorrect;
}

//Iterates through array, prints each element
void QuadraticTable::print()
{
    for (unsigned int i = 0; i < dictSize; ++i)
    {
        cout << "#" << i << ": " << arr[i] << endl;
    }
    cout << endl << endl;
}

//Iterates through array, prints the number of empty buckets (for analysis of hash function)
void QuadraticTable::numEmpty()
{
    unsigned int numEmpty = 0;
    for (unsigned int i = 0; i < dictSize; ++i)
    {
        if (arr[i].size() == 0)
        {
            ++numEmpty;
        }
    }
    cout << "Number of Empty Strings: " << numEmpty << " out of " << dictSize << endl << endl;
}