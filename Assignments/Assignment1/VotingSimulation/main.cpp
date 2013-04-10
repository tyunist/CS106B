//
//  main.cpp
//  VotingSimulation
//
//  Created by Rafael Veronezi on 10/04/13.
//
//

#include <iostream>
#include "simpio.h"
#include "random.h"

/*
 * Define constants
 */
const int TRIALS = 500;             // How many trials will be taken

/*
 * Function: askInteger
 * Usage: number = askInteger(message)
 * -----------------------------------
 * Asks the user for a integer number, using the ask message
 */
int askInteger(std::string message)
{
    std::cout << message;
    return getInteger();
}

/*
 * Function: askPercentage
 * Usage: number = askPercentage(message)
 * --------------------------------------
 * Asks the user for a percentage number between 0.0 and 1.0
 * Displays a message as the prompt
 */
double askPercentage(std::string message)
{
    while (true) {
        std::cout << message;
        double spread = getReal();
        if (spread >= 0.0 && spread <= 1.0) {
            return spread;
        }
        std::cout << "Invalid percentage number, must be between 0.0 and 1.0";
    }
}

/*
 * Function: runTrial
 * Usage: votes = runTrial(votes, errorPerc)
 * -----------------------------------------
 * This function runs a trial of a votation based on the current number of votes
 * and an error percentage.
 */
int runTrial(int votes, double errorPerc)
{
    // randomChance expectes the percentage of chance to be true, so we need to subtract
    //  the error percentage from 1 to get the chance number
    double chance = 1.0 - errorPerc;
    int simVotes = 0;                       // The number of valid votes in the simulation
    
    // Runs for each vote, and based on the chance, adds up to the simulation votes
    for (int i = 0; i < votes; i++) {
        if (randomChance(chance)) {
            simVotes++;
        }
    }
    
    return simVotes;
}

/*
 * Function: runSimulation
 * Usage: chance = runSimulation(voters, spread, errorPerc)
 * --------------------------------------------------------
 * Runs the simulation and returns the percentage of chance to be a invalid election result
 */
double runSimulation(int voters, double spread, double errorPerc)
{
    // Calculates expected votes from each candidate
    int candidateAVotes = voters * (0.5 + spread);      // A is expected to receive more votes
    int candidateBVotes = voters * (0.5 - spread);      // B is expected to lose
    int invalidTrials = 0;
    
    // Run the trials
    for (int i = 0; i < TRIALS; i++) {
        int trialCandidateA = runTrial(candidateAVotes, errorPerc);
        int trialCandidateB = runTrial(candidateBVotes, errorPerc);
        
        if (trialCandidateB > trialCandidateA) {
            invalidTrials++;
        }
    }
    
    return ((double)invalidTrials / TRIALS) * 100.0;
}

/* Program entry-point */
int main()
{
    int voters = askInteger("Enter number of voters: ");
    double spread = askPercentage("Enter percentage spread between candidates: ");
    double errorPerc = askPercentage("Enter voting error percentage: ");
    
    // Calculates the invalid election chance
    std::cout << "Chance of an invalid election result after " << TRIALS << " trials = " << runSimulation(voters, spread, errorPerc) << "%";
}