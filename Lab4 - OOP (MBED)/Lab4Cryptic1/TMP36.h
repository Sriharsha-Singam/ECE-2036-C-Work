#ifndef TMP36_H
#define TMP36_H

#include "mbed.h" 

class TMP36
{
    public:
        TMP36(PinName pin);
        TMP36();
        operator float ();
        float read();
    private:
    //class sets up the AnalogIn pin
        AnalogIn _pin;
};
class Temp{
    public:
        int getTempDifferenceReading(TMP36 myTMP36);
    private:
        float tempC;
        float tempF;
        float tempC1;
        float tempF1;    
};
#endif