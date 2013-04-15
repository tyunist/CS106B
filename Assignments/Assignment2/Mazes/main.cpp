//
//  main.cpp
//  Mazes
//
//  Created by Rafael Veronezi on 12/04/13.
//
//

#include <iostream>
#include "queue.h"
#include "stack.h"
#include "set.h"
#include "maze.h"
#include "random.h"
#include "gevents.h"
#include "simpio.h"
#include "console.h"

/*
 *  Constant declarations
 */
const int PRINT_SOLVE_TIME = 10;

/**
 *  Defines for available directions
 */
enum dirT { North, South, East, West, };

/* Prototype declarations */
void generateMaze(Maze &maze);
Stack<pointT> solveMaze(Maze &maze);
pointT getNextPointForDirection(pointT p, dirT d);
dirT getPointDirection(pointT p1, pointT p2);
Set<dirT> getAvailableDirections(pointT currentPoint, Maze &maze);
pointT getRandomDirection(pointT currentPoint, int rows, int cols);

/* Program entry-point */
int main()
{
    // Declares a Maze variable that will be used accross the program
    // The declaration runs here, so the program starts with a graphic window
    Maze maze(0, 0, false);
    
    while (true) {
        cout << "This program generates and solves mazes!" << endl;
        cout << "Options: " << endl;
        cout << "1. Generate Maze" << endl;
        cout << "0. Quit" << endl;

        int opt = getInteger("Type your choice: ");
        if (opt == 0) break;
        
        int rows = getInteger("Enter the size of the maze in rows: ");
        int cols = getInteger("Enter the size of the maze in cols: ");
        
        maze = Maze(rows, cols, true);
        maze.draw();
        generateMaze(maze);
        
        cout << "Maze generated! Please RETURN to solve it..." << endl;
        getLine();

        Stack<pointT> solution = solveMaze(maze);
        GTimer timer(PRINT_SOLVE_TIME);
        timer.start();
        while (!solution.isEmpty()) {
            waitForEvent(TIMER_EVENT);
            pointT nextPoint = solution.pop();
            maze.drawMark(nextPoint, "BLUE");
        }
        timer.stop();
        
        cout << "Maze solved!" << endl << endl;
    }
    
    
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
    int remaining = (rows * cols) - 1;
    
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
 *  @brief Reverses a proposed path
 *  @param path The path
 *  @return The reversed path
 *
 *  When we find a valid path in stack, it's currently presented in the reverse order,
 *  since the last point found is the last point in the path. If we want to plot the
 *  solution on correct order, we need to reverse the actual path stack.
 *
 *  This function creates a new Stack with the reversed path.
 */
Stack<pointT> reversePath(Stack<pointT> &path)
{
    Stack<pointT> reversedPath;
    while (!path.isEmpty()) {
        reversedPath.push(path.pop());
    }
    return reversedPath;
}

/**
 *  @brief Solves the proposed maze
 *  @param maze The proposed maze
 *  @return A stack of points representing the solution to the maze
 *
 *  This function uses the breadth-first approach to calculate a solution
 *  to the maze. It keep a list of available paths in a queue, until it finds the
 *  solution.
 *
 *  Several data structures are keep to make this algorithm work:
 *  - Paths: A queue of possible paths
 *  - Stack of points: Keep track of points that forma a possible path
 *  - Set of points: Keep track of visited points and avoid possible circular paths
 */
Stack<pointT> solveMaze(Maze &maze)
{
    // Defines the start and points that the solution must run
    pointT startP = { (maze.numRows() - 1), 0 };
    pointT endP = { 0, (maze.numCols() - 1) };

    // Path discovery data
    Queue<Stack<pointT> > paths;    // Define a structure to hold possible paths
    Set<pointT> usedPoints;         // Holds a set of traversed paths to avoid circular path
    usedPoints.add(startP);         // Adds the start point
    
    // Setup: Create path with just start location and enqueue it
    Stack<pointT> shortestPath;
    shortestPath.push(startP);
    paths.enqueue(shortestPath);
    
    // Dequeue shortest path
    while (!paths.isEmpty()) {
        // Gets the first path in the queue, which will be the shortest
        shortestPath = paths.dequeue();
        
        // Check if we've reached our destination path
        pointT lastPoint = shortestPath.peek();
        if (lastPoint == endP) {
            break;
        } else {
            // Pushes new available paths to the queue
            Set<dirT> directions = getAvailableDirections(lastPoint, maze);
            foreach (dirT d in directions) {
                pointT nextPoint = getNextPointForDirection(lastPoint, d);
                if (!usedPoints.contains(nextPoint)) {
                    Stack<pointT> newPath = shortestPath;
                    newPath.push(nextPoint);
                    paths.enqueue(newPath);
                    usedPoints.add(nextPoint);
                }
            }
        }
    }
    
    return reversePath(shortestPath);
}

/**
 *  @brief Returns the point that represents a move to the specified direction
 *  @param p The reference point
 *  @param d The direction in which you want to run
 *  @return A point representing the next step in the direction
 *
 *  This calculates the next point of a given direction.
 *  Warning: it doesn't bound check the result
 */
pointT getNextPointForDirection(pointT p, dirT d)
{
    switch (d) {
        case North: return { p.row - 1, p.col };
        case South: return { p.row + 1, p.col };
        case West: return { p.row, p.col - 1 };
        case East: return { p.row, p.col + 1 };
    }
}

/**
 *  @brief Gets what is the direction of p1 relative to p2
 *  @param p1 The source point
 *  @param p2 The destination point
 *  @return Returns the direction of p1 relative to p2
 */
dirT getPointDirection(pointT p1, pointT p2)
{
	if ((abs(p1.row-p2.row) + abs(p1.col-p2.col)) != 1)
		error("Points are not neighbors");
	if (p1.row != p2.row)
		return (p1.row < p2.row ? North : South);
	else
		return (p1.col < p2.col ? East : West);
}

/**
 *  @brief Determines The available directions of a given point in a maze
 *  @param currentPoint The current that you wich to check available directions
 *  @param maze The maze
 *  @return A Set containing the possible directions
 *
 *  This function check against each of the cardinal directions if you can
 *  move towards there based on the proposed maze.
 */
Set<dirT> getAvailableDirections(pointT currentPoint, Maze &maze)
{
    Set<dirT> availableDirections;
    
    // North available?
    pointT p2 = { currentPoint.row - 1, currentPoint.col };
    if (currentPoint.row > 0 && !maze.isWall(currentPoint, p2)) {
        availableDirections.add(North);
    }
    
    // South available?
    p2.row = currentPoint.row + 1;
    p2.col = currentPoint.col;
    if (currentPoint.row < (maze.numRows() - 1) && !maze.isWall(currentPoint, p2)) {
        availableDirections.add(South);
    }
    
    // West available?
    p2.row = currentPoint.row;
    p2.col = currentPoint.col - 1;
    if (currentPoint.col > 0 && !maze.isWall(currentPoint, p2)) {
        availableDirections.add(West);
    }
    
    // East available?
    p2.row = currentPoint.row;
    p2.col = currentPoint.col + 1;
    if (currentPoint.col < (maze.numCols() - 1) && !maze.isWall(currentPoint, p2)) {
        availableDirections.add(East);
    }
    
    return availableDirections;
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