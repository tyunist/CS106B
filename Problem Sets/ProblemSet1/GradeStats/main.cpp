//
//  main.cpp
//  GradeStats
//
//  Created by Rafael Veronezi on 10/04/13.
//
//  This program calculates statistics for a set exam scores
//  I've deliberately used an random array instead of a file to load scores, contraty to what exercise asks,
//  since file loading was handled in a previous exercise (Histogram), which by the way, seemed far more
//  interesting.
//

#include <iostream>
#include "random.h"

using namespace std;

const int MIN_SCORE = 0;
const int MAX_SCORE = 100;
const int MAX_VALUES = 10;

/*
 * Defines a structure to hold the grade stats
 */
struct gradeStatsT {
    int min;
    int max;
    double average;
};

/*
 * Function: calculateStats
 * Usage: stats = calculateStats(vals, valsSize)
 * ---------------------------------------------
 * Calculates the stats based on a array of values
 */
gradeStatsT calculateStats(int *vals, int valsSize)
{
    gradeStatsT stats;
    stats.min = MAX_SCORE;
    stats.max = MIN_SCORE;
    stats.average = 0.0;
    
    // Gets the min and max values
    int total = 0;
    for (int i = 0; i < valsSize; i++) {
        if (vals[i] < stats.min) stats.min = vals[i];
        if (vals[i] > stats.max) stats.max = vals[i];
        total += vals[i];
    }
    
    // Calculates the average
    stats.average = double(total) / valsSize;
    
    return stats;
}

/*
 * Program entry-point
 */
int main()
{
    // Loads random values into the array
    int *vals = new int[MAX_VALUES];
    for (int i = 0; i < MAX_VALUES; i++) {
        vals[i] = randomInteger(MIN_SCORE, MAX_SCORE);
        cout << vals[i] << endl;
    }
    
    gradeStatsT stats = calculateStats(vals, MAX_VALUES);
    cout << "Grade statistics" << endl;
    cout << "Min score: " << stats.min << endl;
    cout << "Max score: " << stats.max << endl;
    cout << "Average score: " << stats.average << endl;
    
    return 0;
}