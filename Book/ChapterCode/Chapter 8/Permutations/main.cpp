/*
 * File: main.cpp
 * --------------
 * This file ngenerates all permutations of an input string
 * This code is based on the Sample Code of the Chapter 8 of the Book
 * The code is presented in the figure 8-2.
 */

#include <iostream>
#include "set.h"
#include "simpio.h"
#include "gevents.h"
#include "console.h"
using namespace std;

//#define SIMULATE

/* Function prototypes */
Set<string> generatePermutations(string str);

/* Main Program */
int main()
{
    string str = getLine("Enter string: ");
    cout << "The permutations of \"" << str << "\" are: " << endl;
    foreach (string s in generatePermutations(str)) {
        cout << "  \"" << s << "\"" << endl;
    }
    
    return 0;
}

/**
 *  @function generatePermutations
 *  @param str The string to generate a set of permutations
 *  @return Return a set of strings with all possible permutations
 *
 *  Returns a set consisting of all permutations of the specified string.
 *  This implementation uses the recursive insight that you can generate
 *  all permutations of a string by selecting each character in turn,
 *  generating all permutations of the string without that character,
 *  and then concatenating the selected character on the front of each
 *  string generated.
 */
Set<string> generatePermutations(string str)
{
    Set<string> result;
    if (str == "") {
        result += "";
    } else {
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];
            string rest = str.substr(0, i) + str.substr(i + 1);
            foreach (string s in generatePermutations(rest)) {
                result += ch + s;
            }
        }
    }
    
#ifdef SIMULATE
    
    GTimer timer(2000);
    timer.start();
    while (true) {
        GEvent e = waitForEvent(TIMER_EVENT);
        cout << "Current step - input: " << str << ", result: " << result << endl;
        timer.stop();
        break;
    }
    
#endif
    
    return result;
}