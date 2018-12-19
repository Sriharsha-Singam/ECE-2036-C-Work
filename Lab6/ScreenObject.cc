#include "ScreenObject.h"

//Overall explosion function for all dervied functions
void ScreenObject::explosion() {
    uLCD.filled_rectangle(x_pos, y_pos, x_pos+ASTEROID_WIDTH, y_pos+ASTEROID_HEIGHT, transparent);
}