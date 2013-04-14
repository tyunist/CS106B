/*
 * File: main.cpp
 * --------------
 *
 */

#include <iostream>
#include "console.h"
using namespace std;

/*
 *  Function prototypes
 */
string reverseStringIterative(string str);
string reverseStringRecursive(string str);

int main()
{
    cout << "Reverse word 'palindrome', using iterative function: " << reverseStringIterative("palindrome") << endl;
    cout << "Reverse word 'computer science', using recursive function: " << reverseStringRecursive("computer science") << endl;
    
    return 0;
}

/**
 *  @brief Returns the string reversed using a iterative algorithm
 *  @param str The string to be reversed
 *  @return Return the reversed string
 *
 *  This is the simple iterative reverse algorithm.
 */
string reverseStringIterative(string str)
{
    string result;
    for (int i = (str.length()-1); i >= 0; i--) {
        result += str[i];
    }
    return result;
}

/**
 *  @brief Returns the string reversed using a recursive algorithm
 *  @param str The string to be reversed
 *  @return Return the reversed string
 *
 *  This function uses a recursive approach to solve the reverse string problem.
 *  At each iteration of the recursion, it removes the first char of the word and
 *  and expects that this substring to be reversed by the recursive call, when it
 *  returns, it will concatenate the first char to end of the reverse string,
 *  forming the full reversed string.
 *
 *  This recursive example was kind of hard to get at first, but it makes a lot sense.
 *  From the efficience standpoint, it's seen no better than the iterative method,
 *  and it's working is not a lot obvious at first glance, so I don't know if this
 *  case, even being prone to a recursive solution, is best suited to that.
 */
string reverseStringRecursive(string str)
{
    if (str.length() == 0) {
        return "";
    }
    
    return reverseStringRecursive(str.substr(1)) + str[0];
}