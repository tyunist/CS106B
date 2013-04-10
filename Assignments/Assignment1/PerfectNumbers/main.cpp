//
//  main.cpp
//  PerfectNumbers
//
//  Created by Rafael Veronezi on 10/04/13.
//  A program that calculates perfect numbers in the range of 1 to 10000
//

#include <iostream>
#include "simpio.h"

/*
 * Constants declaration
 */
const int MIN_NUMBER = 1;
const int MAX_NUMBER = 10000;


/*
 * Function: isPerfect
 * Usage: b = isPerfect(number)
 * -------------------
 * This predicate calculates if the specified number is a Perfect Number
 * as described by Greeks.
 */
bool isPerfect(int n)
{
    int sum = 0;            // The sum of the proper divisors
    
    // Pass by each number between 1 and n-1 to see what are their proper divisors
    for (int i = 1; i < (n - 1); i++) {
        if ((n % i) == 0) {
            sum += i;
        }
    }
    
    // If the sum of the divisors is equals to the number, then it's perfect
    return (sum == n);
}

/*
 * The program entry point
 */
int main()
{
    // Progrma header
    std::cout << "This program prints out the perfect numbers from " << MIN_NUMBER << " to " << MAX_NUMBER;
    std::cout << "\n\n";
    
    // Pass by each number to check if it's a perfect number
    for (int i = MIN_NUMBER; i <= MAX_NUMBER; i++) {
        if (isPerfect(i)) {
            std::cout << i << " is a perfect number!" << std::endl;
        }
    }
}