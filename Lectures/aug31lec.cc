#include <iostream>
#include <iomanip>

using namespace std;

void numbers();

char name[100];
int main(){
    // std::cout << "Hi! \n";
    // std::cout << "Please Enter Your Name: \n";
    // std::cin >> name;
    // std::cout << "What's up "<< name << "\n";
    //
    // cout << "Hello\n";
    // cout << setw(15) << "Hello\n";
    // cout << "Hello";
    // cout << setw(15) << "Hello" << "Hello\n";
    // //example of sticky
    // cout << setfill('*');
    // cout << setw(15) << "Hello\n";
    // cout << setfill(' ');
    // cout << setw(30) << "Hello\n";
    //
    // numbers();
    fileio();

    return 0;
}

int value;

void numbers(){
  cout<< "Please Enter a Number\n";
  cin>> value;

  cout<<"The Hex Version of that: "<< hex<< value << "\n";
  cout<<"The Oct Version of that: "<< oct<< value << "\n";
}

void fileio(){
  ifstream myInputFileObjectName("input.txt",ios::in);
  ofstream oneOutputFileObjectName("ouput1.txt", ios::out); // ios::out overwrites the file
  ofstream secondOutputFileObjectName("ouput2.txt", ios::app); // ios::app appends new value to original file

  int temp = 0;

  while(myInputFileObjectName >> temp){
    oneOutputFileObjectName<< temp << endl;
  }
  int temp = 0;

  while(myInputFileObjectName >> temp){
    secondOutputFileObjectName<< temp << endl;
  }

  myInputFileObjectName.close();
  oneOutputFileObjectName.close();
  secondOutputFileObjectName.close();
}
