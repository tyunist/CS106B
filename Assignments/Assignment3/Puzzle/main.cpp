/*
 * File: main.cpp
 * --------------
 * This program verifies if a puzzle is Solvable.
 * The code of this program was based on the solution proposed by the GitHub User: dhbikoff
 * https://github.com/dhbikoff/Stanford-CS106B-Solutions/blob/master/Recursion/5_Solvable.cpp
 *
 * My first version implemented the very same ideia and used the same base case, but I had
 * a hard time trying to find how to identify a circular reference, and for most puzzles I've
 * tried it ended on a infinite recursive calls.
 */

#include <iostream>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/**
 *  @brief This function tries to recursively solve the puzzle
 *  @param start The starting point
 *  @param squares The vector of squares representing the puzzle
 *  @param visitedSquares A set of the visited square indexes
 *  @param A reference parameter that keeps track if the puzzle was solved
 *
 *  This function tries every possible path to solve the puzzle, until it reaches
 *  a condition that there are no more ways to try. For this, it keeps track of
 *  a parameter that tells if the solution was found in some iteration.
 *
 *  To avoid circular references, we keep a set of visited indexes.
 */
bool isSolvableRec(int start, Vector<int> &squares, Set<int> &visitedIndexes, bool &solved)
{
    if (visitedIndexes.contains(start)) {
        return solved;
    }
    
    // Base case
    if (start == squares.size()-1) {
        solved = true;
    }
    
    visitedIndexes.add(start);
    
    int nextLeft = start - squares[start];
    if (nextLeft >= 0) {
        isSolvableRec(nextLeft, squares, visitedIndexes, solved);
    }

    int nextRight = start + squares[start];
    if (nextRight < squares.size()) {
        isSolvableRec(start + squares[start], squares, visitedIndexes, solved);
    }
    
    
    return solved;
}

/**
 *  @brief This is the wrapper function to the recursive solution
 *  @param The start point
 *  @return Returns true if the puzzle proposed by squares is solvable
 */
bool isSolvable(int start, Vector<int> & squares)
{
    Set<int> visitedSquares;
    bool solved = false;
    return isSolvableRec(start, squares, visitedSquares, solved);
}

/* Program entry-point */
int main()
{
    Vector<int> board;
    board.add(3);
    board.add(6);
    board.add(4);
    board.add(1);
    board.add(3);
    board.add(4);
    board.add(2);
    board.add(5);
    board.add(3);
    board.add(0);
 
    bool solvable = isSolvable(0, board);
    cout << "Is solvable? " << solvable << endl;

    Vector<int> board2;
    board2.add(3);
    board2.add(1);
    board2.add(2);
    board2.add(3);
    board2.add(0);
    
    solvable = isSolvable(0, board2);
    cout << "Is solvable? " << solvable << endl;
    
    return 0;
}