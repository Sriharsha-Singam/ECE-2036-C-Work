#include <iostream>

using namespace std;

int factInt(int num);
long int factLong(int num);

int main(){
  int factloops = 1241513;
  cout << "Factorial results using int" << endl;
  for(int x = 1; x <= factloops; x++){
    if(factInt(x) == 0){
      break;
    }
    cout << x << "!= " << factInt(x) << endl;
  }
  cout << "Factorial results using long int" << endl;
  for(int x = 1; x <= factloops; x++){
    if(factLong(x) == 0){
      break;
    }
    cout << x << "!= " << factLong(x) << endl;
  }
}

int factInt(int num){
    int fact = 1;
    for(int y = num ; y >= 1; y--){
      fact = fact*y;
    }
    return fact;
}

long int factLong(int num){
    long int fact = 1;
    for(long int y = (long int) num; y >= 1; y--){
      fact = fact*y;
    }
    return fact;
}
