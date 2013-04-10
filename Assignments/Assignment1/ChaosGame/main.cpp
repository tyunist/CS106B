//
//  main.cpp
//  ChaosGame
//
//  Created by Rafael Veronezi on 10/04/13.
//
//

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "gobjects.h"
#include "gevents.h"
#include "random.h"

const int ANIMATION_TIMER = 50;
const int VERTEXES = 3;
const double POINT_RADIUS = 1.5;

/*
 * Function: getMidPoint
 * Usage: getMidPoint(p1, p2)
 * --------------------------
 * Calculates the middle point between p1 and p2
 */
double getMidPoint(int p1, int p2)
{
    int midDiff = abs(p1 - p2) / 2;
    return (p1 < p2) ? midDiff + p1 : midDiff + p2;
}

int main()
{
    GWindow gw;
    GPolygon *triangle = new GPolygon();
    GPoint vertexes[3];
    int vertexCount = 0;
    
    // Gets the triangle
    while (true) {
        GMouseEvent e = waitForEvent();
        if (e.getEventType() == MOUSE_PRESSED) {
            GPoint vertex(e.getX(), e.getY());
            vertexes[vertexCount++] = vertex;
            triangle->addVertex(vertex.getX(), vertex.getY());
            
            GOval *oval = new GOval(10, 10);
            oval->setFilled(true);
            oval->setColor("Red");
            gw.add(oval, vertex.getX(), vertex.getY());
        }
        
        if (vertexCount >= 3) {
            gw.clear();
            gw.add(triangle);
            break;
        }
    }
    
    // Includes an artificial delay of 2 seconds before starting the randomg drawing
    GTimer sleep(2000);
    sleep.start();
    waitForEvent(TIMER_EVENT);
    sleep.stop();
    
    // Starts random drawing
    GTimer timer(ANIMATION_TIMER);
    timer.start();
    
    int currentVertex = randomInteger(0, (VERTEXES - 1));
    GPoint currentPoint(vertexes[currentVertex].getX(), vertexes[currentVertex].getY());
    while (true) {
        GEvent e = waitForEvent(CLICK_EVENT | TIMER_EVENT);
        if (e.getEventType() == MOUSE_CLICKED) break;
        
        // Gets the next vertex to which will draw a point
        int nextVertex = randomInteger(0, (VERTEXES - 1));
        
        // Gets the mid point between the vertexes
        GPoint nextPoint = vertexes[nextVertex];
        GPoint midPoint(getMidPoint(currentPoint.getX(), nextPoint.getX()), getMidPoint(currentPoint.getY(), nextPoint.getY()));
        
        GOval *oval = new GOval(POINT_RADIUS * 2, POINT_RADIUS * 2);
        oval->setFilled(true);
        oval->setColor("Black");
        gw.add(oval, midPoint.getX() - POINT_RADIUS, midPoint.getY() - POINT_RADIUS);
        
        currentPoint = midPoint;
    }
    
    return 0;
}