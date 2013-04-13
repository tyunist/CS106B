/*
 * File: main.cpp
 * --------------
 * This program introduces a function to produce the cartesian product of two sets,
 * as proposed by the Problem 3 in the Problem Set 3.
 */

#include <iostream>
#include "set.h"
#include "console.h"
using namespace std;

// Defines a struct to hold a pair of values
struct pairT {
    string first;
    string second;
};

/*
 *  Prototypes
 */
Set<pairT> cartesianProduct(Set<string> &one, Set<string> &two);
int pairTComparator(pairT p1, pairT p2);

int main()
{
    Set<string> one;
    one.add("A");
    one.add("B");
    one.add("C");
    
    Set<string> two;
    two.add("X");
    two.add("Y");
    
    Set<pairT> cartesian = cartesianProduct(one, two);
    for (pairT p : cartesian) {
        cout << "{(\"" << p.first << "\", \"" << p.second << "\"), ";
    }
    cout << endl;
    
    return 0;
}

/**
 *  @brief Computes the cartesian product of the two sets
 *  @param one The first set
 *  @param two The second set
 *  @param Returns a sets that pairs all possible combinations
 */
Set<pairT> cartesianProduct(Set<string> &one, Set<string> &two)
{
    Set<pairT> cartesian(pairTComparator);
    for (string first: one) {
        for (string second : two) {
            pairT pair = { first, second };
            cartesian.add(pair);
        }
    }
    
    return cartesian;
}

/**
 *  @brief Defines a comparator for type pairT
 *  @param p1 The first pairT
 *  @param p2 The second pairT
 *  @return A number representing how p1 compares to the p2
 */
int pairTComparator(pairT p1, pairT p2)
{
    if (p1.first < p2.first) {
        return -1;
    } else if (p1.first > p2.first) {
        return 1;
    } else if (p1.second < p2.second) {
        return -1;
    } else if (p1.second > p2.second) {
        return 1;
    } else {
        return 0;
    }
}
