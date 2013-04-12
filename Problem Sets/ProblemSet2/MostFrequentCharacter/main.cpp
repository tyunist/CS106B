//
//  main.cpp
//  MostFrequentCharacter
//
//  Created by Rafael Veronezi on 11/04/13.
//  This program defines a function "mostFrequentCharacter", as proposed by the Problem 4 of the Problem Set 2.
//  The original proposition was to pass a file stream as a parameter of the function, but I've deliberately changed
//  to receive a string, so I could keep focus on the implementation of the desired function, and forget about the
//  needs of creating a text file for testing, loading it up, etc.
//

#include <iostream>
#include <cctype>
#include "hashmap.h"
using namespace std;

/*
 * Function: mostFrequentCharacter
 * Usage: mostFrequentCharacter(str, occurrences)
 * ----------------------------------------------
 * Calculates the mostFrequent character on the received file input string
 */
char mostFrequentCharacter(string str, int &numOccurrences)
{
    // A map to keep count references for each char found in the string
    HashMap<char, int> charOccurrences;
    
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];

        // Skips whitespaces
        if (isspace(ch)) continue;
        
        // If there are no occurrences of the current char, then we intitialize it
        if (!charOccurrences.containsKey(ch)) {
            charOccurrences[ch] = 0;
        }
        charOccurrences[ch]++;
    }
    
    // Let's find what's the char with most occurrences
    char maxChar;
    numOccurrences = 0;
    for (char c : charOccurrences)
    {
        if (charOccurrences[c] > numOccurrences) {
            maxChar = c;
            numOccurrences = charOccurrences[c];
        }
    }
    
    return maxChar;
}

/*
 * Program entry-point
 */
int main()
{
    string text = "This is a test string to check occurrences program.";
    int numOccurrences = 0;
    cout << "The most frequent char is '" << mostFrequentCharacter(text, numOccurrences) << "' with " << numOccurrences << " occurrences." << endl;
    
    return 0;
}