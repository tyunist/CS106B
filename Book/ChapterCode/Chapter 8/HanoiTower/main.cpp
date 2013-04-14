/*
 * File: main.cpp
 * --------------
 * This program solves the Twoer of Hanoi puzzle.
 */

#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;


/* Function Prototypes */
void moveTower(int n, char start, char finish, char tmp);
void moveSingleDisk(char start, char finish);

int main()
{
    int n = getInteger("Enter number of disks: ");
    moveTower(n, 'A', 'B', 'C');
    return 0;
}

/**
 *  @function moveTower
 *  @param n The number of disks to move
 *  @param start A char identifying the source spire
 *  @param finish A char identifting the destination spire
 *  @param tmp A char identitying the spire to be temporarly used
 *
 *  Moves a tower of size n from the start spire to the finish
 *  spire using the tmp spire as the temporary repository.
 */
void moveTower(int n, char start, char finish, char tmp)
{
    if (n == 1) {
        moveSingleDisk(start, finish);
    } else {
        moveTower(n - 1, start, tmp, finish);
        moveSingleDisk(start, finish);
        moveTower(n - 1, tmp, finish, start);
    }
}

/**
 *  @function: moveSingleDisk
 *  @param start The source spire of the disk
 *  @param finish The destination spire of the disk
 *
 *  Executes the transfer of a single disk from the start sprie to the
 *  finish spire. In this implementation, the move is simply displayed
 *  on the console; in a graphical implementation, the code would update
 *  the graphics window to show the new arrangement;
 */
void moveSingleDisk(char start, char finish)
{
    cout << start << " -> " << finish << endl;
}