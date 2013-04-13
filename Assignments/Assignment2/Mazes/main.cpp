//
//  main.cpp
//  Mazes
//
//  Created by Rafael Veronezi on 12/04/13.
//
//

#include <iostream>
#include "maze.h"
#include "random.h"

/*
 *  Constant declarations
 */
const int MAZE_COLS = 50;
const int MAZE_ROWS = 30;

/*
 *  Types declarations
 */

/**
 *  Defines for available directions
 */
enum dirT {
    North,
    South,
    East,
    West,
};

/*
 *  Prototype declarations
 */
void generateMaze(Maze &maze);
pointT getRandomDirection(pointT currentPoint, int rows, int cols);

/*
 *  Program entry-point
 */
int main()
{
//    setRandomSeed(1);
    Maze maze(MAZE_ROWS, MAZE_COLS, true);
    maze.draw();
    generateMaze(maze);
    
    return 0;
}

/**
 *  @brief Generate a random perfect maze
 *  @param The Maze object in which the maze will be generated
 *
 *  This functions generate a random perfect maze based on the Aldous-Broder
 *  algorithm. Implementation was based on the explanation of the algorithm as
 *  of the reference site.
 *
 *  @ref http://weblog.jamisbuck.org/2011/1/17/maze-generation-aldous-broder-algorithm
 */
void generateMaze(Maze &maze)
{
    int rows = maze.numRows(), cols = maze.numCols();
    Grid<bool> mazeMark(rows, cols);
    pointT currentPos = {
        randomInteger(0, (rows - 1)),
        randomInteger(0, (cols - 1))
    };
    int remaining = rows * cols;
    
    while (remaining > 0) {
        mazeMark[currentPos.row][currentPos.col] = true;
        
        pointT nextPos = getRandomDirection(currentPos, rows, cols);
        if (!mazeMark[nextPos.row][nextPos.col]) {
            maze.setWall(currentPos, nextPos, false);
            remaining--;
        }
        
        currentPos = nextPos;
    }
}

/**
 *  @brief Gets a random direction for the current point, based on the cardenal coordinates
 *  @param currentPoint The current point to which will take the next random direction
 *  @param rows The number of the rows in the bound
 *  @param cols The number of the cols in the bound
 *  @return A pointT object, representing the valid next random point in the four directions
 *
 *  This functions gets a random direction on the current. It uses a recursive call to prevent
 *  from take a invalid direction that is off the bounds.
 */
pointT getRandomDirection(pointT currentPoint, int rows, int cols)
{
    dirT dir = (dirT)randomInteger(North, West);
    pointT nextDir = currentPoint;
    
    // Adds to the point based on the direction
    switch (dir) {
        case North:
            nextDir.row = nextDir.row - 1;
            break;
        case South:
            nextDir.row = nextDir.row + 1;
            break;
        case West:
            nextDir.col = nextDir.col - 1;
            break;
        case East:
            nextDir.col = nextDir.col + 1;
            break;
    }
    
    // If we have an invalid direction, we call recursively until we found a right one
    if (nextDir.row < 0 || nextDir.row >= rows ||
        nextDir.col < 0 || nextDir.col >= cols) {
        nextDir = getRandomDirection(currentPoint, rows, cols);
    }
    
    return nextDir;
}