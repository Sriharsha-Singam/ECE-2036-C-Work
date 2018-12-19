#include "OTP.h"
#include "mbed.h"
#include <iostream>
#include "SDFileSystem.h"

using namespace std;


//public:
//char encryptLetter();
//char decryptLetter();
//char getFileEnryptionOTP(int position);
//void setFileEnryptionOTP();
//downloadCipherToSD();
//private:
//FILE *fp;

void OTP::downloadCipherToSD(){
    fprintf(fp, arr.c_str());
    fclose(fp);
    printf("Finished\n");
}
void OTP::setOTP(int diff){
    arr = "";
    mkdir("/sd/mydir", 0777);
    fp = fopen("/sd/mydir/OTP.txt", "w");
    if(fp == NULL) {
        printf("Open Error!!!\n");
    }
    for(int i = 0; i<1000; i++)
        arr += ('A'+(((rand()+diff)%26)));
    arr += ""+0;
}
OTP::OTP(){
    file = "/sd/mydir/OTP.txt";
    arr = "";
//    code = 'A';
    FILE *fp12 = fopen("/sd/mydir/OTP.txt", "r"); 
    if(fp12 == NULL) {
        printf("Open Error!!!\n"); 
    }else{
        fscanf(fp12, "%s",arr); 
        fclose(fp12);
    }
}

