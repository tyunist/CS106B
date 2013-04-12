//
//  main.cpp
//  HtmlNesting
//
//  Created by Rafael Veronezi on 11/04/13.
//  This program introduces a function that receives a HTML string, and check if it is correctly nested,
//  as proposed by the Problem 3 of the Problem Set 2
//

#include <iostream>
#include "stack.h"
#include "tokenscanner.h"

/*
 * Prototype declarations
 */
 
bool isCorrectlyNested(string htmlStr);

/*
 * Program entry point
 */
int main()
{
    string htmlStr = "<html><b><i>CS106 rules!</i></b></html>";
    cout << isCorrectlyNested(htmlStr);
    
    return 0;
}

/*
 * Function: processOpenTag
 * Usage: b = processOpenTag(scanner, tagStack)
 * --------------------------------------------
 * Receveis a TokenScanner and a stack to push a tag into.
 * Extracts the tag (which in case is the next token) from the TokenScanner
 *  and places it into the stack of tags
 */
bool processOpenTag(TokenScanner &scanner, Stack<string> &tagStack)
{
    string tag = scanner.nextToken();
    tagStack.push(tag);
    
    return true;
}

/*
 * Function: processCloseTag
 * Usage: b = processCloseTag(scanner, tagStack)
 * ---------------------------------------------
 * Process the closing tag of a html string, based on the tokenizer and the current stack
 * This function will determine what tag is currently being closed, and check if it matches
 * last tag put in the stack. If it is, then returns true.
 */
bool processCloseTag(TokenScanner &scanner, Stack<string> &tagStack)
{
    string tag = scanner.nextToken();
    
    if (!tagStack.isEmpty() && tag == tagStack.pop()) {
        return true;
    } else {
        return false;
    }
}

/*
 * Function: processTag
 * Usage: b = processTag(scanner, tagStack)
 * ----------------------------------------
 * Process a html tag, based on the tokenizer and the current tag stack
 * This function will check if the current token of the Tokenizer is an open or closing tag
 * If it's an open tag, it will add it to the stack of tags, marking the open of a tag
 * If it's an close tag, it will check if the closing matches the last opened tag in the stack
 */
bool processTag(TokenScanner &scanner, Stack<string> &tagStack)
{
    // read the next token to see if we found an
    //  opening or closing tag
    string token = scanner.nextToken();
    
    if (token == "/") {
        return processCloseTag(scanner, tagStack);
    } else {
        scanner.saveToken(token);           // So processOpenTag can use it
        return processOpenTag(scanner, tagStack);
    }
}

/*
 * Function: isCorrectlyNested
 * Usage: b = isCorrectlyNested(htmlString)
 * ----------------------------------------
 * This function receives a html string, and checks if it tags is correctly nested
 */
bool isCorrectlyNested(string htmlStr)
{
    TokenScanner scanner(htmlStr);
    scanner.ignoreWhitespace();
    
    Stack<string> tagStack;
    
    // start by assuming it is balanced
    bool isBalanced = true;
    
    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        if (token == "<") {
            if (!processTag(scanner, tagStack)) {
                isBalanced = false;
                break;
            }
            
            // get rid of ">" part of tag
            scanner.nextToken();
        }
    }
    if (!tagStack.isEmpty()) isBalanced = false;
    
    return isBalanced;
}