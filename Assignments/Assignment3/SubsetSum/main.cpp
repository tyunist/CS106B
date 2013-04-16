/*
 * File: main.cpp
 * --------------
 * This program checks if a given list of numbers can make a sum of a defined target
 */

#include <iostream>
#include "vector.h"
#include "console.h"
using namespace std;

/**
 *  @brief This utility function sums a vector of ints
 *  @param nums The vector of numbers to be sum
 *  @return The sum of the items in the vector
 */
int sumItems(Vector<int> nums)
{
    int sum = 0;
    for (int i = 0; i < nums.size(); i++)
        sum += nums[i];
    
    return sum;
}

/**
 *  @brief Recursively cheks rif the list of numbers haves a combination that mek sum of the target
 *  @param nums The vector of numbers
 *  @param soFar A Vector of the numbers in the list checked so far
 *  @param targetSum The target of the sum
 *  @return Return true if it can make the sum with any combination of those numbers
 *
 *  This function is the recursive solution to the can make sum problem, and uses
 *  the same approach of the SubSets problem.
 */
bool canMakeSumRec(Vector<int> nums, Vector<int> soFar, int targetSum)
{
    if (sumItems(soFar) == targetSum) {
        return true;
    } else if (nums.size() == 0) {
        return false;
    } else {
        int shiftNum = nums[0];
        nums.remove(0);
        
        return canMakeSumRec(nums, soFar, targetSum) ||
               canMakeSumRec(nums, (soFar += shiftNum), targetSum);
    }

    return false;
}

/**
 *  @brief Check if the list of numbers haves a combination that make sum of the target
 *  @param nums The vector of numbers
 *  @param targetSum The target of the sum
 *  @return Return true if it can make the sum with any combination of those numbers
 *
 *  This is the wrapper function around the recursive solution of this problem
 */
bool canMakeSum(Vector<int> &nums, int targetSum)
{
    Vector<int> soFar;
    return canMakeSumRec(nums, soFar, targetSum);
}

/* Program entrypoint */
int main()
{
    Vector<int> nums;
    nums.add(3);
    nums.add(7);
    nums.add(1);
    nums.add(8);
    nums.add(-3);
    
    cout << "Can make sum with 4? " << canMakeSum(nums, 4) << endl;
    cout << "Can make sum with 3? " << canMakeSum(nums, 3) << endl;
    cout << "Can make sum with 2? " << canMakeSum(nums, 2) << endl;
    
    return 0;
}
