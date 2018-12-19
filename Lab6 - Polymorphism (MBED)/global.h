#ifndef global_h
#define global_h

#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

#define ASTEROID_HEIGHT 12
#define ASTEROID_WIDTH 15
#define SPRITE_MAX 15
#define EARTH_WIDTH 10
#define EARTH_HEIGHT 10
#define EXPLOSION1_WIDTH 20

#define SCREEN_MAX 125
#define SCREEN_MIN 1
#define NUM_ASTEROIDS 4

#define I 0x008000 //GREEN
#define S 0xC0C0C0 //SILVER
#define R 0xF1C40F //YELLOW
#define O 0xF39C12 //ORANGE
#define _ 0x000000 //BLACK
#define X 0xFFFFFF //WHITE
#define r 0xFF0000 //RED
#define transparent 0x00000000
#define TEXTCOLOR 0x720C0C

#include "uLCD_4DGL.h"
#include "MMA8452.h"
#include "PinDetect.h"

extern uLCD_4DGL uLCD;
extern Serial pc;
extern MMA8452 acc;
extern PinDetect button1;

#endif
