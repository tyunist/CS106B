//
//  main.cpp
//  Soudex
//
//  Created by Rafael Veronezi on 10/04/13.
//
//

#include <iostream>
#include <cctype>
#include "simpio.h"
#include "strlib.h"

using namespace std;

const string codes[] = {
    "AEIOUHWY",
    "BFPV",
    "CGJKQSXZ",
    "DT",
    "MN",
    "L",
    "R",
};

/*
 * Function: computeSoundex
 * Usage: soundexCode = computeSoundex(surname)
 * --------------------------------------------
 * Computes the soundex code for a given name
 */
string computeSoundex(string surname)
{
    int codesSize = sizeof codes / sizeof(codes[0]);
    string soundex;
    soundex += toupper(surname[0]);
    
    // Converts the characters into digits
    for (int i = 1; i < surname.length(); i++) {
        for (int j = 0; j < codesSize; j++) {
            bool isBreak = false;
            for (int k = 0; k < codes[j].length(); k++) {
                if (toupper(surname[i]) == toupper(codes[j][k]))  {
                    soundex += integerToString(j);
                    isBreak = true;
                    break;
                }
            }
            
            if (isBreak) {
                break;
            }
        }
    }
    
    // Remove any consecutive duplicate digits and zeros
    for (int i = 1; i < (soundex.length() - 1); i++) {
        // Removes consecutive duplicates
        if (soundex[i] == soundex[i+1]) {
            soundex.erase(i+1, 1);
        }
    }
    
    // Removes zeros
    for (int i = 1; i < soundex.length(); i++)
        if (soundex[i] == '0') soundex.erase(i, 1);
    
    // Make the result length 4
    if (soundex.length() < 4) {
        for (int i = 0; i < (4 - soundex.length()); i++) {
            soundex += '0';
        }
    } else if (soundex.length() > 4) {
        soundex = soundex.substr(0, 4);
    }
    
    return soundex;
}

/*
 * Program Entry Point
 */
int main()
{
    string surname;
    while (true) {
        cout << "Enter surname (RETURN to quit): ";
        surname = getLine();
        if (surname == "") break;
        cout << "Soundex code for " << surname << " is " << computeSoundex(surname) << endl;
    }
    
    return 0;
}
