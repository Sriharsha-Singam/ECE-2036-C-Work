
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
        void setCipherPosition(int position, std::string fileName);
        void getFileEnryptionOTPPosition(int position);
    private:
        FILE *fp;
        std::string arr;
        std::string file;
//        char code;
        int index;
};


#endif /* OTP_hpp */
