#include "SpaceShipEarth.h"
#include "ConcreteAsteroid1.h"
#include "ConcreteAsteroid2.h"
#include "ConcreteAsteroid3.h"
#include "ConcreteAsteroid4.h"

#include "Speaker.h"

//Initializing the Hardware Variables
uLCD_4DGL uLCD(p9,p10,p11);
Serial pc(USBTX,USBRX);
MMA8452 acc(p28, p27, 100000);
PinDetect button1(p21);
Speaker mySpeaker(p26);


double x,y,z;
double sounds[10] = {100.0,200.0,300.0,400.0,500.0,600.0,700.0,800.0,900.0,1000.0};
bool BombUsed = false;

//Array for the pointers for all asteroids
ScreenObject * ActiveAsteroids[NUM_ASTEROIDS];

//Push Button Interrupt
void pb1_hit_callback (void) {
    //Check if the bomb is not already used
    if (!BombUsed ) {
        //Set that the bomb IS used
        BombUsed = true;
        //Go through each Asteroid pointer, destroying it and reinitializing its positions
        for (int i = 0; i < NUM_ASTEROIDS  ; i++) {
            ActiveAsteroids[i]->explosion();
            ActiveAsteroids[i]->y_pos = (rand() % 127 + 7);
            ActiveAsteroids[i]->x_pos = 0;
        }
        wait_ms(1000);
        //Go through each Asteroid pointer and re-drawing them
        for (int j = 0; j < NUM_ASTEROIDS; j++) {
            ActiveAsteroids[j]->draw();
        }
    }
}

//Reading the Accelerometer reading for x,y,z
void readAccValues(){
    acc.readXYZGravity(&x,&y,&z);
}

//Check if the 2 Screen Objects overlap
bool overlap(ScreenObject & objectA, ScreenObject & objectB) {

    //Object A's X & Y position
    int oneXLeftTop = objectA.x_pos;
    int oneYLeftTop = objectA.y_pos;

    //Object B's X & Y position
    int twoXLeftTop = objectB.x_pos;
    int twoYLeftTop = objectB.y_pos;

    //Checking if the x_pos of one object is inside the other and if the y_pos of one object is inside the other -- then return true
    if(oneXLeftTop >= twoXLeftTop && oneXLeftTop <= twoXLeftTop+ASTEROID_WIDTH){
        if(oneYLeftTop >= twoYLeftTop && oneYLeftTop <= twoYLeftTop+ASTEROID_HEIGHT){
            return true;
        }
    }
    if(twoXLeftTop >= oneXLeftTop && twoXLeftTop <= oneXLeftTop+EARTH_WIDTH){
        if(twoYLeftTop >= oneYLeftTop && twoYLeftTop <= oneYLeftTop+EARTH_HEIGHT){
            return true;
        }
    }

    return false;
}

//Main Function
int main()
{
    //ULCD Baudrate
    uLCD.baudrate(3000000);
    wait(0.2);

    //Button1 PullUp
    button1.mode(PullUp);

    wait(0.1);

    //Creating the interrupt
    button1.attach_deasserted(&pb1_hit_callback);
    button1.setSampleFrequency();

    //Setting up the pc baudrate
    pc.baud(115200);

    //Setting up srand
    srand(time(0));

    //Setting up ActiveAsteroid array withe different Asteroid Pointers
    ActiveAsteroids[0] = new ConcreteAsteroid1();
    ActiveAsteroids[1] = new ConcreteAsteroid2();
    ActiveAsteroids[2] = new ConcreteAsteroid3();
    ActiveAsteroids[3] = new ConcreteAsteroid4();

    //Drawing all the Asteroids
    for(int i = 0; i< NUM_ASTEROIDS; i++){
        ActiveAsteroids[i]->x_pos = 0;
        ActiveAsteroids[i]->y_pos = (rand() % (127-ASTEROID_HEIGHT) + 7);
        ActiveAsteroids[i]->draw();
    }

    //Initializing the Earth
    SpaceShipEarth ship;

    //Setting up the Earth's position
    ship.x_pos = 64;
    ship.y_pos = 64;
    ship.newY = 64;
    ship.newX = 64;

    //Drawing the earth
    ship.draw();

    //Setting overlapping to false
    bool overlapping = false;

    //Starting the overall timer -- 30 seconds
    Timer overall;
    overall.start();

    //Setting up the timer progress bar
    uLCD.filled_rectangle(0,     0, 127,  7, GREEN);

    while(1)
    {
        //Making sure the program does not go to fast by waiting 400 ms
        Timer t; t.start();

        //Checking if any of the Asteroids collide with the Earth -- then Exit main()
        for(int i = 0; i < NUM_ASTEROIDS; i++){
            overlapping = overlap(ship, *ActiveAsteroids[i]);
            if(overlapping) break;
        }
        if(overlapping) break;

        //Updating the x_pos and y_pos of the Asteroids
        for(int i = 0; i< NUM_ASTEROIDS; i++){
            ActiveAsteroids[i]->update();
        }

        //Read the Accelerometer Values again
        readAccValues();

        //Updating the Earth's position based on the Accelerometer's reading
        if(y > 0.2){ ship.newX += 10;}
        else if(y < -0.2){ ship.newX -= 10;}
        if(x > 0.2){ ship.newY += 10;}
        else if(x < -0.2){ship.newY -= 10;}

        //UPDATE EARTH POSITION
        ship.update();

        //Making sure the program does not go to fast by waiting 400 ms
        t.stop();
        int dt = t.read_ms();
        if (dt < 400) wait_ms(400 - dt);

        //Checking the overall timer -- 30 seconds
        int dOverall = overall.read_ms();
        if(dOverall >= 30000){ break; }

        //Setting the progress bar position based on the timer
        double percent = (127.0-((dOverall/30000.0)*127.0));
        uLCD.filled_rectangle(0, 0, 127,  7, _);
        uLCD.filled_rectangle(0, 0, percent,  7, GREEN);

    }

    //Remove the entire screen and showing either GAME OVER or YOU WIN based on whether anything overlapped or not
    if(overlapping){
        ship.explosion();
        //Losing Tune
        for(int i = 9; i >= 0; i--){
            mySpeaker.PlayNote(sounds[i],0.2,1);
        }
        wait_ms(700);
        //Display GAME OVER!!!
        uLCD.cls();
        uLCD.filled_rectangle(0,     0, 127,  127, _);
        uLCD.locate(5,2);
        uLCD.color(TEXTCOLOR);
        uLCD.textbackground_color(_);
        uLCD.text_width(2);
        uLCD.text_height(2);
        uLCD.printf("GAME");
        uLCD.printf("OVER!!");
    }else{
        //Display YOU WIN!!!
        uLCD.cls();
        uLCD.filled_rectangle(0,     0, 127,  127, _);
        uLCD.locate(5,2);
        uLCD.color(TEXTCOLOR);
        uLCD.textbackground_color(_);
        uLCD.text_width(2);
        uLCD.text_height(2);
        uLCD.printf("YOU");
        uLCD.locate(5,4);
        uLCD.printf("WIN!!");
    }

}