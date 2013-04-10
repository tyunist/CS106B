//
//  main.cpp
//  CensorString
//
//  Created by Rafael Veronezi on 10/04/13.
//
//

#include <iostream>
using namespace std;

/*
 * Prototypes declaration
 */
string censorString1(string text, string remove);
void censorString2(string &text, string remove);

/*
 * Program entry-point
 */
int main()
{
    string texts[2][2] = {
        { "Stanford University", "nt" },
        { "Lamas like to laugh", "la" }
    };

    cout << "Removing '" << texts[0][1] << "' from the string '" << texts[0][0] << "'" << endl;
    cout << censorString1(texts[0][0], texts[0][1]);
    
    cout << "Removing '" << texts[1][1] << "' from the string '" << texts[1][0] << endl;
    string newText = texts[1][0];
    censorString2(newText, texts[1][1]);
    cout << newText;
    
    return 0;
}

/*
 * Function: censorString1
 * Usage: value = censorString1(text, remove)
 * ------------------------------------------
 * Returns a string removing all instances of singular characters present in the remove string
 */
string censorString1(string text, string remove)
{
    censorString2(text, remove);
    return text;
}

/*
 * Function: censorString2
 * Usage: censorString2(&text, remove)
 * ----------------------------------
 * Removes all character instances present in the remove string, from the text string
 */
void censorString2(string &text, string remove)
{
    for (int i = 0; i < remove.length(); i++) {
        int pos = 0;
        while ((pos = text.find(remove[i], pos)) != string::npos) {
            text.erase(pos, 1);
        }
    }
}
