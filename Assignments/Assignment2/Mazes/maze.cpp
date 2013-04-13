/* 
 * File: maze.cpp
 * --------------
 * A maze is mostly a grid of walls. plus a little drawing code.
 */

#include "maze.h"
#include "gobjects.h"

Maze::Maze(int numRows, int numCols, bool hasWalls) : cells(numRows, numCols) 
{
	for (int r = 0; r < numRows; r++)
		for (int c = 0; c < numCols; c++)
			for (int d = 0; d < NumDirs; d++)
				cells[r][c].walls[d] = hasWalls;
	configured = false;
}

int Maze::numRows() 
{ 
	return cells.numRows(); 
}

int Maze::numCols() 
{ 
	return cells.numCols(); 
}

bool Maze::pointInBounds(pointT p)
{
	return (p.row >= 0 && p.row < numRows() && p.col >=0 && p.col < numCols());
}


void Maze::draw()
{
    gw.clear();
	if (!configured) configureGraphics();
	for (int r = 0; r < cells.numRows(); r++) {
		for (int c = 0; c < cells.numCols(); c++) {
			pointT p = {r, c};
			drawWallsForCell(p);
		}
	}
}

bool Maze::isWall(pointT p1, pointT p2)
{
	if (!pointInBounds(p1) || !pointInBounds(p2))
		error("Point is not in bounds for maze");
	return cells[p1.row][p1.col].walls[neighborDir(p1, p2)];
}

void Maze::setWall(pointT p1, pointT p2, bool state)
{
	if (!pointInBounds(p1) || !pointInBounds(p2))
		error("Point is not in bounds for maze");
	cells[p1.row][p1.col].walls[neighborDir(p1, p2)] = state;
	cells[p2.row][p2.col].walls[neighborDir(p2, p1)] = state;
	if (!configured) configureGraphics();
	drawWallsForCell(p1);
}

void Maze::drawMark(pointT p, string color)
{
	if (!pointInBounds(p))
		error("Point is not in bounds for maze");
	if (!configured) configureGraphics();
	double margin = cellSize*.3;
	double length = cellSize - 2*margin;
    
    int x0 = originX + p.col*cellSize + margin;
    int y0 = originY + p.row*cellSize + margin;
    int x1 = x0 + length;
    int y1 = y0 + length;
    gw.setColor(color);
    gw.drawLine(x0, y0, x1, y1);
    
    x0 = originX + p.col*cellSize + margin;
    y0 = originY + p.row*cellSize + cellSize - margin;
    x1 = x0 + length;
    y1 = y1 - length;
    gw.drawLine(x0, y0, x1, y1);
}


Maze::dirT Maze::neighborDir(pointT p1, pointT p2)
{
	if ((abs(p1.row-p2.row) + abs(p1.col-p2.col)) != 1)
		error("Points are not neighbors");
	if (p1.row != p2.row)
		return (p1.row < p2.row ? North : South);
	else
		return (p1.col < p2.col ? East : West);
}

void Maze::drawWallsForCell(pointT p)
{
    int x0 = originX + p.col*cellSize;
    int y0 = originY + p.row*cellSize;
    int x1 = x0 + cellSize;
    int y1 = y0;
    gw.setColor(cells[p.row][p.col].walls[South] ? "Black" : "White");
    gw.drawLine(x0, y0, x1, y1);
    
    x0 = x1;
    y0 = y1;
    x1 = x0;
    y1 = y1 + cellSize;
    gw.setColor(cells[p.row][p.col].walls[East] ? "Black" : "White");
    gw.drawLine(x0, y0, x1, y1);
    
    x0 = x1;
    y0 = y1;
    x1 = x0 - cellSize;
    y1 = y0;
    gw.setColor(cells[p.row][p.col].walls[North] ? "Black" : "White");
    gw.drawLine(x0, y0, x1, y1);

    x0 = x1;
    y0 = y1;
    x1 = x0;
    y1 = y0 - cellSize;
    gw.setColor(cells[p.row][p.col].walls[West] ? "Black" : "White");
    gw.drawLine(x0, y0, x1, y1);
}

void Maze::configureGraphics()
{
	cellSize = min(gw.getWidth()/numCols(), gw.getHeight()/numRows());
	originX = (gw.getWidth() - numCols()*cellSize)/2;
	originY = (gw.getHeight() - numRows()*cellSize)/2;
	configured = true;
}