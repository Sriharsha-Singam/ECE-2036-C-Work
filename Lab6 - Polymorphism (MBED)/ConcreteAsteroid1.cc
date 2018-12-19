#include "ConcreteAsteroid1.h"

// asteroid_sprite_1 initialization
int asteroid_sprite_1[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
        _,_,_,_,X,X,X,X,X,X,X,X,_,_,_,
        _,_,_,X,_,_,_,_,_,_,_,_,X,_,_,
        _,_,X,_,_,_,_,_,_,_,_,_,X,_,_,
        _,X,_,_,_,_,_,_,_,_,_,_,X,_,_,
        X,X,X,X,_,_,_,_,_,_,_,_,_,X,_,
        _,_,_,X,_,_,_,_,_,_,_,_,_,X,_,
        _,_,X,_,_,_,_,_,_,_,_,_,_,X,_,
        _,X,_,_,_,_,_,X,_,_,_,_,_,X,_,
        X,_,_,_,_,_,X,X,_,_,_,_,X,_,_,
        _,X,_,_,_,X,_,X,_,_,_,_,X,_,_,
        _,_,X,_,X,_,_,X,_,_,_,X,_,_,_,
        _,_,_,X,_,_,_,X,X,X,X,_,_,_,_
};

//Custom virtual function from Screen Object class: draw()
void ConcreteAsteroid1::draw() {
    uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_1);
}

//Custom virtual function from Screen Object class: update()
void ConcreteAsteroid1::update() {
    //Removing current Asteroid
    uLCD.filled_rectangle(x_pos, y_pos, x_pos+ASTEROID_WIDTH, y_pos+ASTEROID_HEIGHT, _);
    //Getting the updated Delta X and Y
    getUpdateDelta();
    //Adding the Delta X and Y to the old X and Y position
    x_pos += deltaX;
    y_pos += deltaY;
    //Making sure the asteroid doesn't go past the edge of the screen
    if(x_pos > 128-ASTEROID_WIDTH || y_pos > 128-ASTEROID_HEIGHT){
        //If the asteroid does go past the edge of the screen then re-draw the position of the Asteroid
        y_pos = (rand() % (127-ASTEROID_HEIGHT) + 7);
        x_pos = 0;
        draw();
    }else{
        //If the asteroid doesn't go past the edge of the screen the update the position of the Asteroid
        uLCD.BLIT(x_pos, y_pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, asteroid_sprite_1);
    }
}