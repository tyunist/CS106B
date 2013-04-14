//
//  HanoiTower.h
//  HanoiTowerGraph
//
//  Created by Rafael Veronezi on 14/04/13.
//
//

#ifndef __HanoiTowerGraph__HanoiTower__
#define __HanoiTowerGraph__HanoiTower__

#include <iostream>
#include "vector.h"
#include "stack.h"
#include "gwindow.h"

class HanoiTower
{
public:
    struct spireT {
        char spireId;
        Stack<int> disks;
    };
    
    HanoiTower(int n);
    HanoiTower() { };

    void draw();
    
private:
    const int SCENE_SIZE = 300;
    const int SPIRE_HEIGHT = 100;
    const int SPIRE_THICKNESS = 10;
    
    GWindow gw;
    Vector<spireT> spires;
    
    void drawScene();
    void drawSpires();
};

#endif /* defined(__HanoiTowerGraph__HanoiTower__) */