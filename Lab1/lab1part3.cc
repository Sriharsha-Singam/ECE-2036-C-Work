#include <cmath>
#include <iostream>

using namespace std;

float ans = 0;
double ans1 = 0;
float times = 0;
double times1 = 0;
void findLoop();
void findLoopDouble();
float errorFloat(float in);
double errorDouble(double in);
double findLoopDouble(double next);

int main(){
  cout << "Input the number of terms in the power series using FLOATS: ";
  cin >> times;
  cout << "-----------\n" << "#terms = 1"<< "\napprox = " << ans+1 << "\nerror  = " << errorFloat(ans + 1) << endl;
  if(times > 1){
    findLoop();
  }
  cout << "Input the number of terms in the power series using DOUBLE: ";
  cin >> times1;
  cout << "-----------\n" << "#terms = 1"<< "\napprox = " << ans1+1 << "\nerror  = " << errorDouble(ans1 + 1) << endl;
  if(times1 > 1){
    findLoopDouble();
  }
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

float prevFraction = 1;
void findLoop(){
  float counter = 0;
  for(;;){
    counter += 1;
    prevFraction = ((prevFraction))/counter;
    float newans = ans + prevFraction;
    if(ans == newans || counter == times){
      return;
    }else{
      printf("-----------\n#terms = %f\napprox = %.50f\nerror = %.50f\n",counter+1,newans+1, errorDouble(newans));
      ans = newans;
    }
  }
}
double prevFraction1 = 1;
void findLoopDouble(){
  double counter = 0;
  for(;;){
    counter += 1;
    prevFraction1 = ((prevFraction1))/counter;
    double newans = ans1 + prevFraction1;
    if(ans1 == newans || counter == times1){
      return;
    }else{
      printf("-----------\n#terms = %f\napprox = %.50f\nerror = %.50f\n",counter+1,newans+1, errorDouble(newans));
      ans1 = newans;
    }
  }
}
