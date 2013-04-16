/*
 * File: main.cpp
 * --------------
 * This program calculates the number of possible ways to climb a ladder of N steps,
 *  using a combination of small strides (1 step) and large strides (2 steps).
 */

#include <iostream>
#include "vector.h"
#include "console.h"
using namespace std;

/* Constant declarations */
const int SMALL_STRIDE = 1;
const int LARGE_STRIDE = 2;

/**
 *  @brief This is the recursive solution
 *  @param stairsLeft The number of stairs left on the calculation
 *  @param stride The number of stairs to step
 *  @return The count of ways
 *
 *  This function solves the count ways problem recursively. Each time
 *  the function is called, we check if the number of stairsLeft is equals
 *  to the number of stride:
 *      - In case true: means we have find a successful way and return 1
 *      - In case stairsLeft is less than the stride, means that the way
 *          being calculated is invalid, and returns 0
 *
 *  Each recursive call does a branch of two possibilities:
 *      - Next step in a small stride
 *      - Next step in a large stride
 *
 *  Then we sun the possible ways when the stack is unwinded
 */
int countWaysRec(int stairsLeft, int stride)
{
    if (stairsLeft == stride) {
        return 1;
    } else if (stairsLeft < stride) {
        return 0;
    }
    
    return countWaysRec(stairsLeft - SMALL_STRIDE, stride) +
            countWaysRec(stairsLeft - LARGE_STRIDE, stride);
}

/**
 *  @brief Wrapper for the recursive countWays function
 *  @param numStaris The number of stairs to check for ways
 *  @return Possible ways
 */
int countWays(int numStairs)
{
    return countWaysRec(numStairs, SMALL_STRIDE) +
            countWaysRec(numStairs, LARGE_STRIDE);
}

/* Program entrypoint */
int main()
{
    for (int i = 1; i <= 30; i++) {
        cout << "Count ways of " << i << " steps: " << countWays(i) << endl;
    }
    return 0;
}
