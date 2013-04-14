/*
 * File: main.cpp
 * --------------
 * This program generates a list of all possible mnemonics in a string
 */

#include <iostream>
#include "map.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "console.h"
using namespace std;

/* Function prototypes */
void listMnemonics(string str);
void recursiveMnemonics(string prefix, string rest);
string digitLetters(char ch);

int main()
{
    // Asks for an input number
    string s = integerToString(getInteger("Please enter the number you want th mnemonics for: "));
    listMnemonics(s);
    
    return 0;
}

void listMnemonics(string str)
{
    recursiveMnemonics("", str);
}

/**
 *  @function recurisveMnemonics
 *  @param prefix
 *  @param rest
 *
 *  This function does all of the real work for listMnemonics and
 *  implements a more general problem with a recursive solution
 *  that is easier to see. The call to recursiveMnemonics generates
 *  all mnemonics for the digits in the string rest prefixed by the
 *  mnemonic string in prefix. As the recursion proceeds, the rest
 *  string gets shorter and the prefix string gest longer.
 */
void recursiveMnemonics(string prefix, string rest)
{
    if (rest.length() == 0) {
        cout << prefix << endl;
    } else {
        string options = digitLetters(rest[0]);
        for (int i = 0; i < options.length(); i++) {
            recursiveMnemonics(prefix + options[i], rest.substr(1));
        }
    }
}

/**
 *  @function digitLetters
 *  @param ch The digit on the dial
 *  @return Returns the letters associated with the digit
 *
 *  This function returns a string consisting o the legal
 *  substitutions for a given digit character. Note that 0 and
 *  1 are handled just by leaving that digit in its position.
 */
string digitLetters(char ch)
{
    switch (ch) {
        case '0': return ("0");
        case '1': return ("1");
        case '2': return ("ABC");
        case '3': return ("DEF");
        case '4': return ("GHI");
        case '5': return ("JKL");
        case '6': return ("MNO");
        case '7': return ("PRS");
        case '8': return ("TUV");
        case '9': return ("WXY");
        default: error("Illegal digit");
    }
}