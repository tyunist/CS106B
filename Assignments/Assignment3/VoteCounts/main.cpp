/*
 * File: main.cpp
 * --------------
 * Counts critical votes on given sets
 */

#include <iostream>
#include "vector.h"
#include "console.h"
using namespace std;

/**
 *  @brief Calculates the win target of given blocks
 *  @param blocks The blocks of votes
 */
int calculateTargetVotes(Vector<int> &blocks)
{
    int total = 0;
    for (int i = 0; i < blocks.size(); i++) {
        total += blocks[i];
    }
    return (total / 2) + 1;
}

/**
 *  @brief Calculates the count of critical votes recursively
 *  @param blocks The blocks to calculate
 *  @param index The index of the current block being processed
 *  @param blockNum The num of block that we want to test if it is critical
 *  @param soFar Keeps track of what has been processed so far
 *  @param targetNum The target we want to check against
 *  @return Count of critical votes for the given blocks
 */
int countCriticalVotesRec(Vector<int> &blocks, int index, int blockNum, int soFar, int targetNum)
{
    if (soFar < targetNum && (soFar + blockNum) >= targetNum) return 1;
    if (index == blocks.size()) return 0;
    
    return countCriticalVotesRec(blocks, (index + 1), blockNum, soFar, targetNum) +
           countCriticalVotesRec(blocks, (index + 1), blockNum, (soFar + blocks[index]), targetNum);
}

/**
 *  @brief A wrapper for the recurisve function
 *  @param blocks The set of blocks to count critical votes
 *  @return The number of critical votes in the given set
 */
int countCriticalVotes(Vector<int> &blocks)
{
    int target = calculateTargetVotes(blocks);
    int critical = 0;
    
    for (int i = 0; i < blocks.size(); i++) {
        int blockNum = blocks[i];
        blocks.remove(i);
        critical += countCriticalVotesRec(blocks, 0, blockNum, 0, target);
        blocks.insert(i, blockNum);
    }
    
    return critical;
}

int main()
{
    Vector<int> blocks1;
    blocks1.add(4);
    blocks1.add(2);
    blocks1.add(7);
    blocks1.add(4);
    cout << "Critical votes for set: " << countCriticalVotes(blocks1) << endl;
    
    Vector<int> blocks2;
    blocks2.add(9);
    blocks2.add(9);
    blocks2.add(7);
    blocks2.add(3);
    blocks2.add(1);
    blocks2.add(1);
    cout << "Critical votes for set: " << countCriticalVotes(blocks2) << endl;

    return 0;
}
