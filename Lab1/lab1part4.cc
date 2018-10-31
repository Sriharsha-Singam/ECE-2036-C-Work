#include <cmath>
#include <iostream>

using namespace std;

float ans = 1;
double ans1 = 1;
void findLoop();
void findLoopDouble();
float errorFloat(float in);
double errorDouble(double in);
float sumArrForward();
float sumArrBackward();
double sumArrForward1();
double sumArrBackward1();
float overall[100];
double overall1[100];

int main(){
  overall[0] = ans;
  findLoop();
  overall1[0] = ans1;
  findLoopDouble();
  cout << "FLOAT:\n-----------------" << endl;
  printf("forward approx = %.50f\nforward error = %.50f\nbackward approx = %.50f\nbackward error = %.50f\n\n",sumArrForward(),errorFloat(sumArrForward()),sumArrBackward(),errorFloat(sumArrBackward()));
  cout << "DOUBLE:\n-----------------" << endl;
  printf("forward approx = %.50f\nforward error = %.50f\nbackward approx = %.50f\nbackward error = %.50f\n\n",sumArrForward1(),errorDouble(sumArrForward1()),sumArrBackward1(),errorDouble(sumArrBackward1()));
}
float sumArrForward(){
  float sum = overall[0];
  for(int x = 1; x <100; x++){
    sum += overall[x];
  }
  return sum;
}
float sumArrBackward(){
  float sum = 0;
  for(int x = 99; x>=1; x--){
    sum += overall[x];
  }
  sum+= overall[0];
  return sum;
}
double sumArrForward1(){
  double sum = overall1[0];
  for(int x = 1; x <100; x++){
    sum += overall1[x];
  }
  return sum;
}
double sumArrBackward1(){
  double sum = 0;
  for(int x = 99; x>=0; x--){
    sum += overall1[x];
  }
  return sum;
}
float factFloat(float num){
    float fact = 1;
    for(float y = num ; y >= 1; y--){
      fact = fact*y;
    }
    return fact;
}

double factDouble(double num){
    double fact = 1;
    for(double y = (double) num; y >= 1; y--){
      fact = fact*y;
    }
    return fact;
}
float errorFloat(float in){
  return (100*(((2.71828182845904523536028747135266249775724709369995 - in))/((2.71828182845904523536028747135266249775724709369995))));
}
double errorDouble(double in){
  return (100*(((2.71828182845904523536028747135266249775724709369995 - in))/((2.71828182845904523536028747135266249775724709369995))));
}

void findLoop(){
  int counter = 0;
  for(;;){
    counter += 1;
    float newans = (1/factFloat(counter));
    if(counter == 100){
      return;
    }else{
      ans = newans;
      overall[counter] = newans;
    }
  }
}

void findLoopDouble(){
  int counter = 0;
  for(;;){
    counter += 1;
    double newans = (1/factDouble(counter));
    if(counter == 100){
      return;
    }else{
      ans1 = newans;
      overall1[counter] = newans;
    }
  }
}
