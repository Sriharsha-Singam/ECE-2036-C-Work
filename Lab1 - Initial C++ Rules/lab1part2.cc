#include <cmath>
#include <iostream>

using namespace std;

float quadFloat(float type);
double quadDouble(double type);
float errorOneFloat(float in);
float errorTwoFloat(float in);
double errorOneDouble(double in);
double errorTwoDouble(double in);

int main(){
  cout << "Using the float data type the roots are:" << endl;
  cout << "x1 = " << quadFloat(1) << "  error = " << errorOneFloat(quadFloat(1)) << endl;
  cout << "x2 = " << quadFloat(-1) << "  error = " << errorTwoFloat(quadFloat(-1)) << endl;

  cout << "Using the double data type the roots are:" << endl;

  cout << "x1 = " << quadDouble(1) << "  error = " << errorOneDouble(quadDouble(1)) << endl;
  cout << "x2 = " << quadDouble(-1) << "  error = " << errorTwoDouble(quadDouble(-1)) << endl;
}

float quadFloat(float type){
  float a = (float) 1;
  float b = (float) 3000.001;
  float c = (float) 3;
  float ans =  (float) ((-b/(2*a))+(type*((sqrt((pow(b,2) - 4*a*c)))/(2*a))));
  return ans;
}
double quadDouble(double type){
  double a = (double) 1;
  double b = (double) 3000.001;
  double c = (double) 3;
  double ans = (double) ((-b/(2*a))+(type*((sqrt((pow(b,2) - 4*a*c)))/(2*a))));
  return ans;
}
float errorOneFloat(float in){
  return (100*(((-0.001 - in))/((-0.001))));
}
float errorTwoFloat(float in){
  return (100*(((-3000 - in))/((-3000))));
}

double errorOneDouble(double in){
  return (100*(((-0.001 - in))/((-0.001))));
}
double errorTwoDouble(double in){
  return (100*(((-3000 - in))/((-3000))));
}
