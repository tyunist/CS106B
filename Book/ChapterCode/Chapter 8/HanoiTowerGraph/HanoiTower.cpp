//
//  HanoiTower.cpp
//  HanoiTowerGraph
//
//  Created by Rafael Veronezi on 14/04/13.
//
//

#include "HanoiTower.h"

HanoiTower::HanoiTower(int n)
{
    spireT spireA = { 'A', Stack<int>() };
    spireT spireB = { 'B', Stack<int>() };
    spireT spireC = { 'C', Stack<int>() };
    
    for (int i = n; i > 0; i--) {
        spireA.disks.push(i);
    }
    
    spires.add(spireA);
    spires.add(spireB);
    spires.add(spireC);
}

void HanoiTower::drawScene()
{
    int x = (gw.getWidth() - SCENE_SIZE) / 2;
    int y = ((gw.getHeight() / 2) + SPIRE_HEIGHT) - SPIRE_THICKNESS;
    int width = SCENE_SIZE;
    int height = SPIRE_THICKNESS;
    
    gw.setColor("BLACK");
    gw.fillRect(x, y, width, height);
}

void HanoiTower::drawSpires()
{
    double x = (gw.getWidth() - SCENE_SIZE) / 2;
    double y = (gw.getHeight() - SPIRE_HEIGHT) / 2;
    double width = SPIRE_THICKNESS;
    double height = SPIRE_HEIGHT;
    
    gw.setColor("BLACK");
    gw.fillRect(x, y, width, height);
    gw.fillRect(((gw.getWidth()) / 2) - (SPIRE_THICKNESS / 2), y, width, height);
    gw.fillRect(x + SCENE_SIZE - SPIRE_THICKNESS, y, width, height);
}

void HanoiTower::draw()
{
    drawScene();
    drawSpires();
}