#include "SpaceShipEarth.h"

// spaceship_earth1 initialization
int spaceship_earth1[EARTH_WIDTH *EARTH_HEIGHT] = {
        _,_,S,S,S,S,S,S,_,_,
        _,S,I,I,I,I,I,I,S,_,
        S,I,I,I,I,I,I,I,I,S,
        S,I,I,I,I,I,I,I,I,S,
        S,I,I,I,I,I,I,I,I,S,
        S,I,I,I,I,I,I,I,I,S,
        S,I,I,I,I,I,I,I,I,S,
        S,I,I,I,I,I,I,I,I,S,
        S,I,I,I,I,I,I,I,S,_,
        _,S,S,S,S,S,S,S,_,_,
};

//Custom virtual function from Screen Object class: draw() for Earth
void SpaceShipEarth::draw(){
    uLCD.BLIT(x_pos, y_pos, EARTH_HEIGHT, EARTH_WIDTH, spaceship_earth1);
}

//Custom virtual function from Screen Object class: update() for Earth movement based on Accelerometer
void SpaceShipEarth::update() {
    //Makes sure the new X and Y position is inside screen boundaries
    if(x_pos < 118 && y_pos < 118 && x_pos > 0 && y_pos > 0){
        //Destroy earth
        uLCD.filled_rectangle(x_pos, y_pos, x_pos+EARTH_HEIGHT, y_pos+EARTH_WIDTH, transparent);
        //Re-draw the earth
        uLCD.BLIT(newX, newY, EARTH_HEIGHT, EARTH_WIDTH, spaceship_earth1);
        //Updating the X and Y position based on the Accelerometer readings
        x_pos = newX;
        y_pos = newY;
    }
    else{
        //Makes sure the new X and Y position does not go past the screen boundaries
        if(x_pos >= 118)
            newX = 117;
        if(y_pos >= 118)
            newY = 117;
        if(x_pos <= 0)
            newX = 0;
        if(y_pos <= 0)
            newY = 0;
        //Re-draw the earth inside the screen
        x_pos = newX;
        y_pos = newY;
        uLCD.BLIT(newX, newY, EARTH_HEIGHT, EARTH_WIDTH, spaceship_earth1);

    }
}

void SpaceShipEarth::explosion() {
    //initializing the explosion for the earth
    int explosion[EARTH_WIDTH*EARTH_HEIGHT] = {
            R,r,O,R,r,O,R,r,O,R,
            R,r,O,R,r,O,R,r,O,R,
            R,r,O,R,r,O,R,r,O,R,
            R,r,O,R,r,O,R,r,O,R,
            R,r,O,R,r,O,R,r,O,R,
            R,r,O,R,r,O,R,r,O,R,
            R,r,O,R,r,O,R,r,O,R,
            R,r,O,R,r,O,R,r,O,R,
            R,r,O,R,r,O,R,r,O,R,
            R,r,O,R,r,O,R,r,O,R
    };
    //destroy the earth
    uLCD.filled_rectangle(x_pos, y_pos, x_pos+EARTH_HEIGHT, y_pos+EARTH_WIDTH, transparent);
    //drawing the explosion of the earth
    uLCD.BLIT(x_pos, y_pos, EARTH_HEIGHT, EARTH_WIDTH, explosion);
}