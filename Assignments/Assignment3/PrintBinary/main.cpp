/*
 * File: main.cpp
 * --------------
 * This program prints the binary representation of a given number
 */

#include <iostream>
#include "simpio.h"
#include "strlib.h"
#include "console.h"
using namespace std;

/**
 *  @brief Calculates the binary of a given number
 *  @param num The number to be converted
 *  @return A string representing the binary number
 */
string calcBinary(int num, string soFar)
{
    string result;
    if (num == 0) {
        result = soFar;
    } else {
        string digit = integerToString(num % 2);
        num /= 2;
        result += calcBinary(num, digit + soFar);
    }
    
    return result;
}

/**
 *  @brief Prints out the integer number represented as a binary
 *  @param num The number that wants to print the representation for
 *
 *  This function is a wrapper around the recursive implementation
 */
void printInBinary(int num)
{
    cout << "The number " << num << " binary representation is: " << calcBinary(num, "") << endl;
}

int main()
{
    cout << "This program prints out the binary representation of a given integer number" << endl;
    cout << "Enter the numbers or 0 to exit." << endl;
    while (true) {
        int num = getInteger("? ");
        if (num == 0) break;
        printInBinary(num);
    }
    
    return 0;
}