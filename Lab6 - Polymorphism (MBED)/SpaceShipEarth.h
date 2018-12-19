#ifndef SpaceShipEarth_h
#define SpaceShipEarth_h

#include "ScreenObject.h"

class SpaceShipEarth: public ScreenObject{
public:
    int newX;
    int newY;
    void draw();
    void update();
    void explosion();
};

#endif
