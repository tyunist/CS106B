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
const int MAX_BUCKETS = 10;

/*
 * Function Prototypes
 */
void openFile(ifstream &infile);
void loadDataFromStream(ifstream &infile, int *vals, int &valsSize);
void calculateHistogram(int *vals, int valsSize, int *ranges, int rangesSize);
void printHistogram(int *ranges, int rangesSize);

/*
 * Program entry-point
 */
int main()
{
    // Variables to hold the data
    int values[MAX_VALUES];
    int valuesSize = 0;
    int buckets[MAX_BUCKETS];
    
    // Creates the input stream, open and loads it's data
    ifstream infile;
    openFile(infile);
    loadDataFromStream(infile, values, valuesSize);
    infile.close();
    
    // Calculates and prints the histogram
    calculateHistogram(values, valuesSize, buckets, MAX_BUCKETS);
    printHistogram(buckets, MAX_BUCKETS);
    
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
 * Usage: loadDataFromStream(infile, vals, valsSize)
 * ---------------------------------
 * Loads the data from the specified stream into the array of values passed as the pointer
 * in the vals parameters. The valsSize keeps track of the effective size
 */
void loadDataFromStream(ifstream &infile, int *vals, int &valsSize)
{
    // Read each line of the file, loading into the array of values
    while (true) {
        string line;
        getline(infile, line);
        if (infile.fail()) break;
        vals[valsSize++] = stringToInteger(line);
    }
    
    // Clears the error state
    infile.clear();
}

/*
 * Function: loadBuckets
 * Usage: loadBuckets(vals, valsSize, ranges, rangesSize)
 * ---------------------
 * Loads the buckets of the histogram, based on the vals array into the ranges bucket array
 */
void calculateHistogram(int *vals, int valsSize, int *ranges, int rangesSize)
{
    // resets the buckets values
    for (int i = 0; i < rangesSize; i++)
        ranges[i] = 0;
    
    for (int i = 0; i < valsSize; i++) {
        int bucketN = vals[i] / 10;
        ranges[bucketN]++;
    }
}

/*
 * Function: printHistogram
 * Usage: printHistogram(ranges, rangesSize)
 * -----------------------------------------
 * Prints the histogram based on the received array of bucket values (ranges) and the size of them
 */
void printHistogram(int *ranges, int rangesSize)
{
    for (int i = 0; i < rangesSize; i++) {
        cout << i * 10 << "-" << ((i+1) * 10) - 1 << ": ";
        for (int j = 0; j < ranges[i]; j++) {
            cout << "X";
        }
        cout << endl;
    }
}