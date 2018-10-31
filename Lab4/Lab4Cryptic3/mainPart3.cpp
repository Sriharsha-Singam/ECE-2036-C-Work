#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "mbed.h"
#include "uLCD_4DGL.h"
#include "SDFileSystem.h"
#include <string>
#include "PinDetect.h"
#include "OTP.h"

//declare objects for pins used with pushbuttons
PinDetect pb1(p16);
PinDetect pb2(p17);
PinDetect pb3(p18);

using namespace std;
enum InputType {FWD, BACK,STAY,ENCRYPT};

//enum InputType  {  UP , DOWN , ENCRYPT };
enum StateType  {Q0, Q1, Q2, Q3};

//Serial pc(USBTX, USBRX); // tx, rx
uLCD_4DGL uLCD(p28, p27, p29); // serial tx, serial rx, reset pin;
SDFileSystem sd(p5, p6, p7, p8, "sd");
//instantiate new class to set p15 to analog input
//to read and convert TMP36 sensor's voltage output




InputType input = STAY;
StateType state = Q0;
//Serial pc(USBTX, USBRX); // tx, rx

OTP otp;
//// Callback routine is interrupt activated by a debounced pb3 hit
void pb3_hit_callback (void)
{
    // ADD CODE HERE THAT YOU WHAT TO RUN WHEN INTERUPT IS GENERATED
    input = ENCRYPT;
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
char currLetter = 'A';
void outputLetter(){
    uLCD.locate(0,0);
    uLCD.text_width(5);
    uLCD.text_height(5);
    uLCD.printf("%c",currLetter);
}
void encryptNow(char letter){
    uLCD.locate(9,0);
    uLCD.text_width(5);
    uLCD.text_height(5);
    uLCD.printf("%c",letter);
//    if(letter == 'a'){}
}
int index = 0;
int main(){
//    std::string arr = otp.getArr();

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
    
    outputLetter();
    index = otp.getCipherPosition("/sd/mydir/positionCipherReceiver.txt");
//    uLCD.printf("%i",index);
//    otp.getFileEnryptionOTPPosition(++index);
    
    while(1) {
        switch(state) {
            //wait
            case(Q0):
                //calculate next state
                if (input == FWD)
                    state = Q1;
                else if(input == BACK)
                    state = Q2;
                else if(input == ENCRYPT)
                    state = Q3;
                else //input should be stay
                    state = Q0;
                break;
            //scroll up
            case (Q1):
                currLetter += 1;
                if(currLetter > ('Z')){
                    currLetter = 'A';
                }
                outputLetter();
                state = Q0;
                input = STAY;
                break;
            //scroll down
            case (Q2):
                   currLetter -= 1;
                   if(currLetter < ('A')){
                       currLetter = 'Z';
                   }
                   outputLetter();
                   state = Q0;
                   input = STAY;
                break;
                
            //encrypt
            case (Q3):
//                   uLCD.printf("%s",otp.arr);
//                   uLCD.printf("HELLO");
                   encryptNow(otp.decryptLetter(currLetter));
                   otp.setCipherPosition("/sd/mydir/positionCipherReceiver.txt");
                   wait(2);
                   state = Q0;
                   input = STAY;
                break;
        }//end switch
        wait (0.5);
    }
    otp.close();
    
    //    uLCD.printf("Download Cipher Key to microSD Card?\nYES  NO\n");
}
