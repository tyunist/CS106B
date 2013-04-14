/*
 * File: main.cpp
 * --------------
 * This program solves the Problem 2 of Problem Set 3, "Maps"
 */

#include <iostream>
#include "map.h"
#include "console.h"
using namespace std;

/*
 *  Defines a point structure
 */
struct pointT {
    int x, y;
};

/*
 *  Function Prototypes
 */
int comparePointT(pointT p1, pointT p2);

int main()
{
    /*
     *  Defines a structure to hold a list of cities, indexed by
     *  it's map location x, y, defined by the struct pointT.
     *
     *  Notice that we'd taken a differente approach than the proposed
     *  by the Problem Set 3, because by the time the problem was 
     *  proposed, the version of the Map class from the Stanford Library
     *  could only use string keys.
     *
     *  Since the current version now supports the definition of
     *  a custom struct/class as the key type, then we could just
     *  use a pointT as the key of the map. All we needed to do was
     *  to write a custom comparator function that the Map would use
     *  to identify duplicates.
     *
     *  Either way, if we would solve this problem using the older version,
     *  we should specify a string serialization of the struct.
     *
     */
    Map<pointT, string> cities(comparePointT);

    pointT c1p = { 1, 1 };
    cities[c1p] = "São Paulo";
    
    pointT c2p = { 1, 2 };
    cities[c2p] = "Rio de Janeiro";
        
    // Prints out as tests
    cout << cities[c1p] << endl;
    cout << cities[c2p] << endl;
    
    return 0;
}

/**
 *  @brief A function to compare two pointT's
 *  @param p1 The first point
 *  @param p2 The second point
 *  @return Returns the position of e1 relative to e2, or 0 if they equals
 */
int comparePointT(pointT p1, pointT p2)
{
    if (p1.x > p2.x) return 1;
    else if (p1.x < p2.x) return -1;
    else if (p1.y > p2.y) return 1;
    else if (p1.y < p2.y) return -1;
    else return 0;
}