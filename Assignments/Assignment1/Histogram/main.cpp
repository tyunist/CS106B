//
//  main.cpp
//  Histogram
//
//  Created by Rafael Veronezi on 10/04/13.
//
//

#include <iostream>
#include <fstream>
#include "simpio.h"
#include "strlib.h"

using namespace std;

const int MAX_VALUES = 1000;
const int BUCKETS = 10;

int values[MAX_VALUES];
int valuesSize = 0;
int buckets[BUCKETS];


/*
 * Function Prototypes
 */
void loadDataFromStream(ifstream &infile);
void openFile(ifstream &infile);
void loadBuckets();
void printHistogram();

/*
 * Program entry-point
 */
int main()
{
    // Creates the input stream, open and loads it's data
    ifstream infile;
    openFile(infile);
    loadDataFromStream(infile);
    infile.close();
    
    // Calculates and prints the histogram
    loadBuckets();
    printHistogram();
    
    return 0;
}

/*
 * Function: openFile
 * Usage: openFile(infile)
 * -----------------------
 * Asks the user for the file with data for the histogram
 */
void openFile(ifstream &infile)
{
    while (true) {
        cout << "Enter file name: ";
        string filename = getLine();
        infile.open(filename.c_str());
        if (!infile.fail()) break;
        
        cout << "Invalid filename!" << endl;
        infile.clear();
    }
}

/*
 * Function: loadDataFromStream
 * Usage: loadDataFromStream(infile)
 * ---------------------------------
 * Loads the data from the specified stream into the array of values
 */
void loadDataFromStream(ifstream &infile)
{
    // Read each line of the file, loading into the array of values
    while (true) {
        string line;
        getline(infile, line);
        if (infile.fail()) break;
        values[valuesSize++] = stringToInteger(line);
    }
    
    // Clears the error state
    infile.clear();
}

/*
 * Function: loadBuckets
 * Usage: loadBuckets
 * ---------------------
 * Loads the buckets of the histogram, based on the loaded values
 */
void loadBuckets()
{
    // resets the buckets values
    for (int i = 0; i < BUCKETS; i++)
        buckets[i] = 0;
    
    for (int i = 0; i < valuesSize; i++) {
        int bucketN = values[i] / 10;
        buckets[bucketN]++;
    }
}

void printHistogram()
{
    for (int i = 0; i < BUCKETS; i++) {
        cout << i * 10 << "-" << ((i+1) * 10) - 1 << ": ";
        for (int j = 0; j < buckets[i]; j++) {
            cout << "X";
        }
        cout << endl;
    }
}