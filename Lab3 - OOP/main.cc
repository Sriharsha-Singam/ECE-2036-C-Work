//
//  main.cc
//
//
//  Created by Sriharsha Singam on 9/30/18.
//

#include "maps.h"
#include "schedule.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#define NUM_LOCATIONS 25

using namespace std;

int main()
{

//get input for coordinates and store in an internal array
//For simplicity you may assume that this is fixed at 24 locations

   Map PawneeMapCoordinates;
   PawneeMapCoordinates.initializeMap("PawneeMapCoordinates.txt");

//Now instantiate a LeslieKnopeSchedule object and get the locations
//that she needs to visit today. Remember she needs to
//begin and end at City Hall.

   Schedule LeslieKnopeSchedule("Leslie Knope");
   LeslieKnopeSchedule.getToDoList();
   LeslieKnopeSchedule.generateRoute(PawneeMapCoordinates);
    
//Loading entire output in the output.txt -- using std::string output variable from Schedule class
   ofstream outfileObject("output.txt", ios::out);
   outfileObject << LeslieKnopeSchedule.getOutPut()<< endl;
   outfileObject.close();
}






#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "mbed.h"
#include "uLCD_4DGL.h"
#include "SDFileSystem.h"
#include <string>
#include "PinDetect.h"
#include "TMP36.h"

//declare objects for pins used with pushbuttons
PinDetect pb1(p15);
PinDetect pb2(p16);
PinDetect pb3(p18);

using namespace std;

uLCD_4DGL uLCD(p28, p27, p29); // serial tx, serial rx, reset pin;
SDFileSystem sd(p5, p6, p7, p8, "sd");
//instantiate new class to set p15 to analog input
//to read and convert TMP36 sensor's voltage output

enum InputType {FWD, BACK,STAY};
enum StateType {Q0, Q1, Q2, Q3};

InputType input = STAY;
StateType state = Q0;

//// Callback routine is interrupt activated by a debounced pb3 hit
void pb3_hit_callback (void)
{
    // ADD CODE HERE THAT YOU WHAT TO RUN WHEN INTERUPT IS GENERATED
    input = STAY;
}
// Callback routine is interrupt activated by a debounced pb1 hit
void pb1_hit_callback (void)
{
    // ADD CODE HERE THAT YOU WHAT TO RUN WHEN INTERUPT IS GENERATED
    input = FWD;
}
// Callback routine is interrupt activated by a debounced pb2 hit
void pb2_hit_callback (void)
{
    input = BACK;
}

TMP36 myTMP36(p15);
Temp temp;
OTP otp;
otp.OTP(uLCD);
//std::string arr = "";
//FILE *fp;

//void makeOTP(){
//    //    uLCD.printf("Starting OTP Process\n");
//    srand(time(0));
//    int diff = temp.getTempDifferenceReading(myTMP36);
//
//    mkdir("/sd/mydir", 0777);
//    fp = fopen("/sd/mydir/OTP.txt", "w");
//    if(fp == NULL) {
//        uLCD.printf("Open Error!!!\n");
//    }
//    for(int i = 0; i<1000; i++)
//        arr += ('A'+(((rand()+diff)%26)));
//
//    arr += ""+0;
//    input = FWD;
//
//    //    uLCD.printf("Finished--%s\n",arr.c_str());
//}

//void downloadCipher(){
//    fprintf(fp, arr.c_str());
//    fclose(fp);
//    uLCD.printf("Finished\n");
//    input = STAY;
//}
int main(){
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    
    // Delay for initial pullup to take effect
    wait(.01);
    
    // Setup Interrupt callback functions for a pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
    pb3.attach_deasserted(&pb3_hit_callback);
    
    // Start sampling pb inputs using interrupts
    pb1.setSampleFrequency(); //default is 20KHz sampling
    pb2.setSampleFrequency();
    pb3.setSampleFrequency();
    
    
    
    while(1) {
        switch(state) {
            case(Q0):
                makeOTP();
                //calculate next state
                if (input == FWD){
                    state = Q1;
                    uLCD.printf("Download Cipher Key to microSD Card?\nYES  NO\n");
                }
                else //input should be stay
                    state = Q0;
                break;
            case (Q1):
                
                if (input == FWD){
                    state = Q2;
                    otp.downloadCipherToSD();
                }
                else if (input == BACK)
                    state = Q0;
                else //input should be stay
                    state = Q1;
                break;
            case (Q2):
                
                //calculate next state
                if (input == FWD){
                    state = Q3;
                    uLCD.printf("Download Cipher Key to --Another-- microSD Card?\nYES  NO\n");
                }
                else if (input == BACK)
                    state = Q1;
                else //input should be stay
                    state = Q2;
                break;
            case (Q3):
                
                //calculate next state
                if (input == FWD){
                    state = Q1;
                    uLCD.printf("Download Cipher Key to microSD Card?\nYES  NO\n");
                }
                else //input should be stay
                    state = Q3;
                break;
        }//end switch
        wait (0.5);
    }
    //    uLCD.printf("Download Cipher Key to microSD Card?\nYES  NO\n");
}
