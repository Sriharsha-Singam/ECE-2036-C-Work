#include "TMP36.h"
#include "mbed.h" 

using namespace std;


TMP36::TMP36(PinName pin) : _pin(pin)
{
// _pin(pin) means pass pin to the AnalogIn constructor
}

float TMP36::read()
{
//convert sensor reading to temperature in degrees C
    return ((_pin.read()*3.3)-0.500)*100.0;
}
//overload of float conversion (avoids needing to type .read() in equations)
TMP36::operator float ()
{
//convert sensor reading to temperature in degrees C
    return ((_pin.read()*3.3)-0.500)*100.0;
}
int Temp::getTempDifferenceReading(TMP36 myTMP36){
        tempC = myTMP36.read(); //convert to degrees F
        printf("tempc :%f/n",tempC);
         tempF = (9.0*tempC)/5.0 + 32.0; //print current temp
        wait(2.0);
        tempC1 = myTMP36.read(); //convert to degrees F
        printf("tempc1 :%f/n",tempC1);
        tempF1 = (9.0*tempC)/5.0 + 32.0; //print current temp
        return ((tempF1-tempF)*1000);
}