#ifndef AbstractAsteroid_h
#define AbstractAsteroid_h

#include "ScreenObject.h"

class AbstractAsteroid: public ScreenObject{
public:
    int deltaX;
    int deltaY;
    void getUpdateDelta();
};

#endif
