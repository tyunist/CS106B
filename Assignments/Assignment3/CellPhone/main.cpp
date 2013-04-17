/*
 * File: main.cpp
 * --------------
 * This program reads a digits input and list possible completions, based on a cellphone keypad.
 */

#include <iostream>
#include "simpio.h"
#include "set.h"
#include "lexicon.h"
#include "console.h"
using namespace std;

/* Constant declarations */
const string LEXICON_PATH = "/Users/rafael/Developer/Study/CS106B/Assignments/Assignment3/CellPhone/lexicon.dat";
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUWVXYZ";

/* Function prototypes */
void listCompletions(string digits, Lexicon &lex);
void getCompletions(string word, Lexicon &lex, Set<string> &words);
void getMnemonics(string prefix, string rest, Set<string> &mnemmonics);
string digitLetters(char ch);

/* Program entry-point */
int main()
{
    Lexicon lex(LEXICON_PATH);

    // Print instructions
    cout << "This program enumerates possible completions for a given set of digits, based on typing ";
    cout << "on a cellphone keypad. Enter the digits you want to check, or zero to exit." << endl;
    
    // Asks inputs
    while (true) {
        string digits = integerToString(getInteger("? "));
        if (digits[0] == '0') break;
        listCompletions(digits, lex);
    }
    
    return 0;
}

/**
 *  @brief Lists the completions of a given digits string
 *  @param digits The digits to check for completions
 *  @param lex The lexicon to be used to consider possible words
 *
 *  This functions lists each of the possible completions for a given
 *  digits string.
 */
void listCompletions(string digits, Lexicon &lex)
{
    // Let's first get all possible combinations of the current digits
    Set<string> mnemonics;
    getMnemonics("", digits, mnemonics);
    
    // Then, by each of these combinations, let's enumerate each of it's
    //  possible completions, given a english lexicon
    for (string m : mnemonics) {
        Set<string> words;
        getCompletions(m, lex, words);
        
        for (string w : words) {
            cout << w << endl;
        }
    }
}

/**
 *  @brief Gets possible completions for a given word
 *  @param word The word to check for completions
 *  @param lex The lexicon to check completions against
 *  @param words A set that will be filled with possible completions
 *
 *  This function recursively checks for possible completions of a given
 *  word, using the provided lexicon.
 */
void getCompletions(string word, Lexicon &lex, Set<string> &words)
{
    if (lex.containsWord(word)) {
        words.add(word);
    }

    for (int i = 0; i < ALPHABET.size(); i++) {
        string newWord = word + ALPHABET[i];
        if (lex.containsPrefix(newWord)) {
            getCompletions(newWord, lex, words);
        }
    }
}

/**
 *  @brief Gets the mnemonics based on a cellphone keypad char disposition
 *  @param prefix The prefix of processed chars
 *  @param rest The rest of chars to be processed
 *  @param mnemonics A pointer to a Set that will hold the possible mnemonics
 *  
 *  This function uses recursion to load a Set will all possible mnemonics of
 *  the given digits. This prefix parameter must be a empty string for the first
 *  iteration. The mnemonics will be loaded with each found mnemonic.
 */
void getMnemonics(string prefix, string rest, Set<string> &mnemmonics)
{
    if (rest.length() == 0) {
        mnemmonics.add(prefix);
    } else {
        string options = digitLetters(rest[0]);
        for (int i = 0; i < options.length(); i++) {
            getMnemonics(prefix + options[i], rest.substr(1), mnemmonics);
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
        case '7': return ("QPRS");
        case '8': return ("TUV");
        case '9': return ("WXYZ");
        default: error("Illegal digit");
    }
    
    return "";
}
