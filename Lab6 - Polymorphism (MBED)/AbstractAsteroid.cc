#include "AbstractAsteroid.h"

//Get random values for the Delta X and Delta Y
void AbstractAsteroid::getUpdateDelta() {
    deltaY = (rand() % 5 + 1);
    deltaX = (rand() % 35 + 1);
}