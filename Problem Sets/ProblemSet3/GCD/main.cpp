/*
 * File: main.cpp
 * --------------
 * This program implements the GCD function, that calculates the greatest common
 * divisor of two numbers, as proposed by the Problem 6 of Problem Set 3.
 */

#include <iostream>
#include "console.h"
using namespace std;

/*
 *  Function prototypes
 */
int GCD(int x, int y);

int main()
{
    cout << "GCD of 2, 3: " << GCD(2, 3) << endl;
    cout << "GCD of 3, 6: " << GCD(3, 6) << endl;
    cout << "GCD of 12, 64: " << GCD(12, 64) << endl;
    cout << "GCD of 50, 75: " << GCD(50, 75) << endl;
    
    return 0;
}

/**
 *  @brief Calculates the greatest common divisor of two numbers
 *  @param x X Number
 *  @param y Y Number
 *  @return Returns the greatest common divisor of the numbers
 *
 */
int GCD(int x, int y)
{
    // If x is evenly divisible by y, then y is the greatest common divisor
    if ((x % y) == 0) {
        return y;
    }
    
    // Otherwise, the greatest common divisor of x and y is always equal to the
    // greatest common divisor of y and the remainder of x divided y.
    return GCD(y, (x % y));
}