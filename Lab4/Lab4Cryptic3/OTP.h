
#ifndef OTP_h
#define OTP_h

#include <iostream>
#include <string>
#include "mbed.h"
#include <cstdlib>


using namespace std;

class OTP{
    public:
        char encryptLetter(char letter);
        char decryptLetter(char letter);
        char getFileEnryptionOTP(int position);
        int getCipherPosition(std::string filename);
        void downloadCipherToSD();
        OTP();
        void setOTP(int diff);
        char arr[1001];
        char* ptr;
        void setCipherPosition(std::string fileName);
        void getFileEnryptionOTPPosition(int position);
//        std::string getArr();
        void close();
    private:
        FILE *fp;
            FILE *fp12; 
        std::string file;
//        char code;
        int index;
};


#endif /* OTP_hpp */
