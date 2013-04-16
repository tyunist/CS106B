/*
 * File: main.cpp
 * --------------
 * This program draw a ruler on the screen
 */

#include <iostream>
#include "gwindow.h"
#include "console.h"
using namespace std;

/* Constants declarations */
const int WIDTH = 300;
const int HEIGHT = 50;
const int MIN_HEIGHT = 1;

/**
 *  @brief draw a ruler on the window
 *  @param x The x coordinate of the rectangle of the ruler
 *  @param y The y coordinate of the rectangle of the ruler
 *  @param w The width of the ruler
 *  @param y The height of the ruler
 *  @param gw The window object to draw the ruler
 *
 *  This function recursively draws a ruler on the screen
 */
void drawRuler(double x, double y, double w, double h, GWindow &gw)
{
    if (h <= MIN_HEIGHT) {
        return;
    }
    
    // Draws the base line
    int x0 = x;
    int y0 = y + h;
    int x1 = x + w;
    int y1 = y0;
    gw.drawLine(x0, y0, x1, y1);
    
    // Draws the middle line
    x0 = x + (w / 2);
    y0 = y;
    x1 = x0;
    y1 = y + h;
    gw.drawLine(x0, y0, x1, y1);
    
    // Recursively draws each new side
    drawRuler(x, y + (h / 2), w / 2, h / 2, gw);
    drawRuler(x + (w / 2), y + (h / 2), w / 2, h / 2, gw);
}

/* Program entrypoint */
int main()
{
    GWindow gw;
    int x = (gw.getWidth() - WIDTH) / 2;
    int y = (gw.getHeight() - HEIGHT) / 2;
    drawRuler(x, y, WIDTH, HEIGHT, gw);
    
    return 0;
}