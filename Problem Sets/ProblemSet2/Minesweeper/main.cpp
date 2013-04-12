//
//  main.cpp
//  Minesweeper
//
//  Created by Rafael Veronezi on 12/04/13.
//
//

#include <iostream>
#include "grid.h"

/*
 * Function: calculateBombsForLocation
 * Usage: bombs = calculateBombsForLocation(row, col, bombLocations)
 * -----------------------------------------------------------------
 * Calculates the number of the rows in the neighboorhood and location itself, given a row and col
 */
int calculateBombsForLocation(int row, int col, Grid<bool> &bombLocations)
{
    int bombCount = 0;
    
    // Determines the bounds of rows to check, that may vary if I'm on the first or last rows
    int strRow = (row == 0) ? 0 : (row - 1);
    int endRow = row == (bombLocations.numRows() - 1) ? row : (row + 1);
    
    // Determines the bounds of columns to check
    int strCol = (col == 0) ? 0 : (col - 1);
    int endCol = col == (bombLocations.numCols() - 1) ? col : (col + 1);
    
    for (int r = strRow; r <= endRow; r++) {
        for (int c = strCol; c <= endCol; c++) {
            if (bombLocations[r][c]) bombCount++;
        }
    }
    
    return bombCount;
}

/*
 * Function: makeGridOfCounts
 * Usage: g = makeGridOfCounts(bombLocations)
 * ------------------------------------------
 * This function receives a grid defining bomb locations as boolean values, and creates and returns
 * a new grid, containing the cont of bombs in the neighborhood of each location, just like a grid
 * of a minesweeper game.
 */
Grid<int> makeGridOfCounts(Grid<bool> &bombLocations)
{
    // Make a grid of the same size of the bombs grid
    Grid<int> countGrid(bombLocations.numRows(), bombLocations.numCols());
    
    for (int r = 0; r < countGrid.numRows(); r++) {
        for (int c = 0; c < countGrid.numCols(); c++) {
            countGrid[r][c] = calculateBombsForLocation(r, c, bombLocations);
        }
    }
    
    return countGrid;
}

int main()
{
    // Initializes a grid based on the locations proposed by the exercise
    Grid<bool> bombLocations(6, 6);
    bombLocations[0][0] = true;
    bombLocations[0][1] = false;
    bombLocations[0][2] = false;
    bombLocations[0][3] = false;
    bombLocations[0][4] = false;
    bombLocations[0][5] = true;

    bombLocations[1][0] = false;
    bombLocations[1][1] = false;
    bombLocations[1][2] = false;
    bombLocations[1][3] = false;
    bombLocations[1][4] = false;
    bombLocations[1][5] = true;
    
    bombLocations[2][0] = true;
    bombLocations[2][1] = true;
    bombLocations[2][2] = false;
    bombLocations[2][3] = true;
    bombLocations[2][4] = false;
    bombLocations[2][5] = true;

    bombLocations[3][0] = true;
    bombLocations[3][1] = false;
    bombLocations[3][2] = false;
    bombLocations[3][3] = false;
    bombLocations[3][4] = false;
    bombLocations[3][5] = false;

    bombLocations[4][0] = false;
    bombLocations[4][1] = false;
    bombLocations[4][2] = true;
    bombLocations[4][3] = false;
    bombLocations[4][4] = false;
    bombLocations[4][5] = false;
    
    bombLocations[5][0] = false;
    bombLocations[5][1] = false;
    bombLocations[5][2] = false;
    bombLocations[5][3] = false;
    bombLocations[5][4] = false;
    bombLocations[5][5] = false;
 
    // Gets the calculation and prints out
    Grid<int> bombCount = makeGridOfCounts(bombLocations);
    
    for (int r = 0; r < bombCount.numRows(); r++) {
        for (int c = 0; c < bombCount.numCols(); c++) {
            cout << "| " << bombCount[r][c] << " ";
        }
        cout << "|" << endl;
    }
    
    return 0;
}