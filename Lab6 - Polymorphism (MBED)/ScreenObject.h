#ifndef ScreenObject_h
#define ScreenObject_h

#include "global.h"

class ScreenObject{

public:
    int x_pos;
    int y_pos;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void explosion();
    virtual void afterExplode();
};

#endif
