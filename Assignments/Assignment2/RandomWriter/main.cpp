//
//  main.cpp
//  RandomWriter
//
//  Created by Rafael Veronezi on 12/04/13.
//  This program generates random text based on given input file
//

#include <iostream>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "hashmap.h"
#include "vector.h"

/*
 * Constants declaration
 */
const int MIN_MODEL_ORDER = 1;
const int MAX_MODEL_ORDER = 10;
const int OUTPUT_SIZE = 2000;

/*
 * Defines a structure to hold how many occurrences of a given char
 * is found following a specific pattern
 */
struct patternOccurrenceT {
    int occurrences;
    HashMap<char, int> nextCharOccurrences;
};

// Defines the type to hold the map of patterns
typedef HashMap<string, patternOccurrenceT> patternMapT;

/*
 * Function prototypes
 */
void analyseInput(string text, int order, patternMapT &patternsMap);
string getMostCommonPattern(patternMapT &patternsMap);
char getNextCharFromOccurence(patternOccurrenceT &occurrence);
string generateRandomText(patternMapT &patternsMap, int size);

/**
 *  @brief Asks the user for a filename
 *
 */
string getInputFromFile()
{
    string filename;
    string input;
    ifstream infile;

    // Asks the file
    while (true) {
        cout << "Please enter the filename: ";
        filename = getLine();
        infile.open(filename.c_str());
        if (!infile.fail()) break;
        cout << "Invalid filename!" << endl;
    }
    
    // Reads the file
    int ch;
    while ((ch = infile.get()) != EOF) {
        input += ch;
    }
    
    return input;
}

/**
 *  @brief Asks the user for the order number for the analysis
 *  @param minModel The minimum order number
 *  @param maxModel The maximum order number
 *  @return The given order number respecting the boundaries
 */
int getOrder(int minModel, int maxModel)
{
    int order;
    while (true) {
        cout << "Please enter the order of the analysis: ";
        order = getInteger();
        if (order >= minModel && order <= maxModel) break;
        cout << "The model must be a number between " << MIN_MODEL_ORDER << " and "<< MAX_MODEL_ORDER;
    }
    return order;
}

/*
 * Program entry-point
 */
int main()
{
    cout << "Welcome to RandomWriter!" << endl;
    cout << "This program generates random text derived from an input file, based on the Markov model" << endl << endl;
    
    string input = getInputFromFile();
    int order = getOrder(MIN_MODEL_ORDER, MAX_MODEL_ORDER);
    
    patternMapT patterns;
    analyseInput(input, order, patterns);
    cout << generateRandomText(patterns, OUTPUT_SIZE);
    
    return 0;
}

/**
 *  @brief Analyses an input to produce a map of patterns in the Markov model
 *  @param text The text to be analyzed
 *  @param order The order of the markov model
 *  @param patternsMap The map to store the model
 *
 *  Notice that the "over commenting" is held on purpose to keep me on track of the algorithm.
 */
void analyseInput(string text, int order, patternMapT &patternsMap)
{
    // Let's navigate by each char in the string, to extract the patterns
    int length = (text.length() - order - 1);
    for (int i = 0; i < length; i++) {
        string pattern = text.substr(i, order);         // Gets the pattern given the current order
        char nextChar = text[i + order];                // Gets the next char after the pattern
        
        // First we check if the pattern exists, if not, we'll set the pattern and the next char
        // as initiliazed values.
        // The else case states that the pattern already exists, so we need to check if the char
        // ocurrence exists, if it's not the case, then initialize it with a 0 value
        if (!patternsMap.containsKey(pattern)) {
            patternsMap[pattern].occurrences = 0;
            patternsMap[pattern].nextCharOccurrences[nextChar] = 0;
        } else if (!patternsMap[pattern].nextCharOccurrences.containsKey(nextChar)) {
            patternsMap[pattern].nextCharOccurrences[nextChar] = 0;
        }
        
        // Notice that the map was initialized with 0, that's because we just can keep a simple call
        // to increment the ocurrences of a next char
        patternsMap[pattern].occurrences++;
        patternsMap[pattern].nextCharOccurrences[nextChar]++;
    }
}

/**
 *  @brief Generates random text based on a given map
 *  @param patternsMap The map of patterns to base the randomization
 *  @param size The size of the text to be generated
 *  @return A string containing the random generated text
 *
 *  This function uses the Markov model to generate random text output based on a given map
 */
string generateRandomText(patternMapT &patternsMap, int size)
{
    // Setup the algorithm
    string currentPattern = getMostCommonPattern(patternsMap);          // Gets the staring sequence
    string result = currentPattern;                                     // And sets it's to initial result
    
    // The pattern shift size, represent how many chars we want to extract from the right of the current pattern
    // We do this based on the current order, but if the order of the model is 1, we can't extract 0 chars from it
    // to get to the next pattern, so we need to set a fixed value.
    int patternShiftSize = currentPattern.size() > 1 ? (currentPattern.size() - 1) : 1;

    // We're going to generate random chars one by one, until we reach the proposed size or until there are no more
    //  patterns left
    while (true) {
        char nextChar = getNextCharFromOccurence(patternsMap[currentPattern]);
        result += nextChar;
        currentPattern = currentPattern.substr(1, patternShiftSize) + nextChar;
        if (!patternsMap.containsKey(currentPattern) || result.size() >= size) break;
    }
    
    return result;
}

/**
 *  @brief Get the most random pattern in a given   map
 *  @param patternsMap The of patterns to check for
 *
 *  This function analysise the patterns map to find out the one with most occurrences.
 *  If the given map has more patterns with the same max occurrences size, then the function
 *  will get a random one.
 */
string getMostCommonPattern(patternMapT &patternsMap)
{
    Vector<string> patternsWithMaxSize;         // Keep track of the patterns that have max occurrences size
    int maxOccurrences = 0;                     // Keep track of the maximum number of occurrences of any pattern
    string pattern;
    
    // First we need to find the max number of occurrences of any pattern
    for (string key : patternsMap) {
        if (patternsMap[key].occurrences > maxOccurrences) maxOccurrences = patternsMap[key].occurrences;
    }
    
    // Then we fill the vector with patterns that have the max size
    for (string key : patternsMap) {
        if (patternsMap[key].occurrences == maxOccurrences) {
            patternsWithMaxSize.add(key);
        }
    }
    
    // If we have more than one pattern with the max size, we'll need to randomize among indexes
    if (patternsWithMaxSize.size() > 1) {
        int index  = randomInteger(0, patternsWithMaxSize.size() - 1);
        pattern = patternsWithMaxSize[index];
    } else {
        pattern = patternsWithMaxSize[0];
    }
    
    return pattern;
}

/**
 *  @brief Gets a random next char of a pattern
 *  @param occurrence The pattern occurrence to check for
 *
 *  This functions returns a random next char available from the pattern, based on the frequency percentage
 */
char getNextCharFromOccurence(patternOccurrenceT &occurrence)
{
    Vector<char> possibleChars;             // Keeps an vector of possible chars
    for (char ch : occurrence.nextCharOccurrences) {
        // Adds to the vector of possible chars, based on it's occurrences
        for (int i = 0; i < occurrence.nextCharOccurrences[ch]; i++) {
            possibleChars.add(ch);
        }
    }
    
    // Returns the next char, based on a randomization of available chars
    int charIndex = 0;
    if (possibleChars.size() > 1) {
        charIndex = randomInteger(0, (possibleChars.size() - 1));
    }
    
    return possibleChars[charIndex];
}