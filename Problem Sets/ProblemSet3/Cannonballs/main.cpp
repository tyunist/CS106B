/*
 * File: main.cpp
 * --------------
 * This program calculates the quantity of cannonballs on a pile,
 * considering the pile to be a pyramid composed of squares until the top 1,
 * as proposed by Problem 4 in the Problem Set 3.
 */

#include <iostream>
#include "console.h"

using namespace std;

/**
 *  @brief Calculate the cannonballs on a pile of given height
 *  @param height The height of the pile
 *  @return Returns the count of cannon balls in the pile
 *
 *  This function implements a recursive solution to calculate the count of cannonbals,
 *  considering that each step on the pile is a square of the above and so on
 */
int cannonBall(int height)
{
    if (height <= 1) {
        return 1;
    }
    return height * height + cannonBall(height - 1);
}

int main() {
    
    cout << cannonBall(5) << endl;
    
    return 0;
}
