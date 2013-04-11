//
//  main.cpp
//  CountLetters
//
//  Created by Rafael Veronezi on 10/04/13.
//
//

#include <iostream>
#include <cctype>
using namespace std;

/*
 * Defines a structure to count a number of occurrences of a word
 */
struct letterCountT {
    char letter;
    int occurrences;
};

/*
 * Function: countLetters
 * Usage: countLetters(text, letters, letterCount
 * ----------------------------------------------
 * Counts each of the letters on the passed string, and stores it into the the letters array of letterCountT
 */
letterCountT *countLetters(string text, int &letterCount)
{
    letterCount = 'Z' - 'A' + 1;            // Counts the letters from A to Z
    letterCountT *letters = new letterCountT[letterCount];
    
    // Initialize the letter count array
    for (int i = 0; i < letterCount; i++) {
        letterCountT letterCount;
        letterCount.letter = 'A' + i;
        letterCount.occurrences = 0;
        letters[i] = letterCount;
    }
    
    for (int i = 0; i <= letterCount; i++) {
        char ch = letters[i].letter;
        for (int c = 0; c < text.length(); c++) {
            if (toupper(text[c]) == ch) letters[i].occurrences++;
        }
    }
    
    return letters;
}

/*
 * The program entry-point
 */
int main()
{
    int lettersCount;
    letterCountT *letters = countLetters("Abcd K..\nijk;;\ncab-Bage\nfad", lettersCount);
    
    // Prints out
    for (int i = 0; i < lettersCount; i++) {
        cout << letters[i].letter << ": " << letters[i].occurrences << endl;
    }
    
    return 0;
}