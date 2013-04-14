/*
 * File: main.cpp
 * --------------
 * This program calculates the possibility of trying to weight based on
 * old-fashioned measuring.
 */

#include <iostream>
#include "vector.h"
#include "console.h"
using namespace std;

#define SOLUTION_IMPLEMENTATION

/* Function prototypes */
#ifdef SOLUTION_IMPLEMENTATION
bool isMeasurable(int target, Vector<int> &weights);
#else
bool isMeasurable(int target, Vector<int> weights);
#endif

/* Program entrypoint */
int main()
{
    Vector<int> sampleWeights;
    sampleWeights.add(1);
    sampleWeights.add(3);
    
    cout << isMeasurable(2, sampleWeights) << endl;
    cout << isMeasurable(4, sampleWeights) << endl;
    cout << isMeasurable(5, sampleWeights) << endl;
    
    return 0;
}

#ifdef SOLUTION_IMPLEMENTATION

/**
 *  @brief A recursive solution to the measure problem
 *  @param target The target weight to check against
 *  @param weights The available weights
 *  @param index
 *  @return True if the target is measurable with available weights
 *
 *  This version of function was copied from the solution, and proposes
 *  an implementation free of the problems that mine introduced, yet
 *  being pretty simplier.
 *  
 *  This version consider an additional index parameter, that is
 *  recursively incremented, and at each iteration, represents the
 *  a position in the weights vector to check for the 3 cases. If
 *  any one of them is true, then the measurability of the case is fine.
 *
 *  Notice that the comments was added to guide me on the solution
 */
bool recIsMeasurable(int target, Vector<int> &weights, int index)
{
    // If the target is actually 0, then there's no checking needed
    if (target == 0) {
        return true;
    }
    
    // If we try to check off the bounds of the weights vector
    // Then we checked against all available solutions and it's not valid
    if (index >= weights.size()) {
        return false;
    }
    
    return (
            // Try putting a weight on the other side of the balance
            recIsMeasurable(target + weights[index], weights, index + 1) ||
            // Try putting a weight on the same side
            recIsMeasurable(target, weights, index + 1) ||
            // Try removing the weight
            recIsMeasurable(target - weights[index], weights, index + 1));
}

/**
 *  @brief acts as a wrapper around the recursive solution
 */
bool isMeasurable(int target, Vector<int> &weights)
{
    return recIsMeasurable(target, weights, 0);
}

#else

int sumWeights(Vector<int> &weights)
{
    int total = 0;
    for (int i = 0; i < weights.size(); i++) {
        total += weights[i];
    }
    return total;
}

/**
 *  @brief This is my first implementation of the isMeasurable function
 *  @param target The target weight we may want to check against
 *  @param weights A vector of available weights
 *
 *  In this first version that I wrote, I considered the case problem to be
 *  if the target is equals to the sum of weights. If not, then I called the
 *  funciton recursively trying to solve a smaller problem in the following
 *  fashion:
 *      - Iterate through available weights, at each iteration, move the topmost
 *          to left side, increment a new target with that value, and removing
 *          it from the the weights list
 *      - Check if the new target and weight lists isMeasurable
 *      - if not, remove the weight entirely and check again
 *
 *  This approach worked for the simple tests of this program, but it has several
 *  problems:
 *      - The iteration as it is implemented, does not consider all the cases,
 *          because when it removes the first weight, it's never going to be
 *          considered again on the right side
 *      - There are nested recursive calls, that kind of break the simplicity
 *          that recursive solutions is intended to bring
 *      - Notice I changed the weights parameter in order to not be a reference
 *          parameter. This is because in this implementation, we destroy the
 *          vector in order to try to find the solution, so consecutive calls
 *          using the same vector would not work
 *
 *  Either way I decided to keep the code here, since it's a interesting recursive
 *  exercise that I thought, and is very close to solve the problem, I thouhgt it
 *  to be a good example.
 */
bool isMeasurable(int target, Vector<int> weights)
{
    if (target == sumWeights(weights)) {
        return true;
    } else {
        for (int i = 0; i < weights.size(); i++) {
            int weight = weights[i];
            int newTarget = target + weight;
            weights.remove(i);
            
            if (!isMeasurable(newTarget, weights)) {
                // Removes entirely
                newTarget -= weight;
                return isMeasurable(newTarget, weights);
            } else {
                return true;
            }
        }
    }
    
    return false;
}

#endif