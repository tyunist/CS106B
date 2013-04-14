/*
 * File: main.cpp
 * --------------
 * This program solves the exercises proposed by the Problem 1 of Problem Set 3,
 * "Set Callbacks", for creating callbacks for comparing values of a Set
 */

#include <iostream>
#include "set.h"
#include "strlib.h"
#include "console.h"
using namespace std;

/*
 *  Defines a struct to hold a record of an address book
 */
struct entryT {
    string firstName;
    string lastName;
    string phoneNumber;
};

/*
 *  Function Prototypes
 */
int compareEntryT(entryT e1, entryT e2);
int compareStringCaseIncensitive(string s1, string s2);

int main()
{
    /*
     *  Declares a set of entries, passing the function "compareEntryT"
     *  as comparator of entries, as proposed by the exercise a.
     */
    Set<entryT> entries(compareEntryT);
    entryT e1 = { "Rafael", "Veronezi", "123" };
    entryT e2 = { "Fernanda", "Alves", "456" };
    entries.add(e1);
    entries.add(e2);
    
    for (entryT e : entries) {
        cout << e.firstName << " " << e.lastName << ", tel: " << e.phoneNumber << endl;
    }
    cout << endl;
    
    /*
     *  Declares a set of strings that ignore cases
     */
    Set<string> strings(compareStringCaseIncensitive);
    strings.add("Word");
    strings.add("word");
    strings.add("Test");
    strings.add("test");

    for (string s : strings) {
        cout << s << endl;
    }
    
    return 0;
}

/**
 *  @brief A function to compare two entries
 *  @param e1 The first entry
 *  @param e2 The second entry
 *  @return Returns the position of e1 relative to e2, or 0 if they equals
 *
 *  This function compares two entries of type entryT, considering the field
 *  "firstName" as the primary key, and "secondName" as the secondary key
 *  in the composition.
 *
 *  This functions solves problem proposed by the exercise a.
 *
 *  If we try to set two entries that have the same name and first name in the
 *  set, only one of them will be stored, and the other will be discarded. To
 *  avoid this behavior, we may have to find another way of comparing entryT's,
 *  that takes another informations into account to compare.
 */
int compareEntryT(entryT e1, entryT e2)
{
    if (e1.firstName > e2.firstName) return 1;
    else if (e1.firstName < e2.firstName) return -1;
    else if (e1.lastName > e2.lastName) return 1;
    else if (e1.lastName < e2.lastName) return -1;
    else return 0;
}

/**
 *  @brief Compares two string ignoring the case
 *  @param s1 The first string
 *  @param s2 The second string
 *  @return Returns the position of s1 relative to s2, or 0 if they are equals
 *
 *  This function compares two strings, ignoring their cases. It's useful in
 *  cases where case doesn't matter.
 *  
 *  This functions solves problem proposed by the exercise b.
 */
int compareStringCaseIncensitive(string s1, string s2)
{
    s1 = toLowerCase(s1);
    s2 = toLowerCase(s2);
    
    if (s1 > s2) return 1;
    else if (s1 < s2) return -1;
    else return 0;
}