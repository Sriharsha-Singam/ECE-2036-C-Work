#include "OTP.h"
#include "mbed.h"
#include <iostream>
#include "SDFileSystem.h"
#include <fstream>

using namespace std;
Serial pc(USBTX, USBRX); // tx, rx


//public:
//char encryptLetter();
//char decryptLetter();
//char getFileEnryptionOTP(int position);
//void setFileEnryptionOTP();
//downloadCipherToSD();
//private:
//FILE *fp;

char OTP::encryptLetter(char letter){
    pc.printf("encrypt index: %i\n", arr[index]);
    int let = ((int)letter +  (int)arr[index]);
    let = let%26 + 65;
    index += 1;
    pc.printf("letter: %c at %i\n",let,index);
    return let;
}
char OTP::decryptLetter(char letter){
    pc.printf("encrypt index: %i\n", arr[index]);
    int let = (((int)letter) - ((int)arr[index])) +26;
//    int diff = 65 - let;
//    if(let < 0){
//        diff = 90 - diff;
//        pc.printf("letter: %c at %i\n",diff,index);
//        return diff;
//    }
    let = let%26 + 65;
    index += 1;
    pc.printf("letter: %c at %i\n",let,index);
    return let;
}
void OTP::getFileEnryptionOTPPosition(int position){
//    code = arr.at(position);
    index = position;
    pc.printf("index: %i\n",index);
}
void OTP::setCipherPosition(std::string fileName){
    FILE *fp2 = fopen(fileName.c_str(), "w");
    if(fp2 == NULL) {
        pc.printf("Error Open \n");
    }else{
        fprintf(fp2, "%i", (index));
        fclose(fp2);
    }
}
int OTP::getCipherPosition(std::string filename){
    int position = 0;
    FILE *fp2 = fopen(filename.c_str(), "r");
    if(fp2 == NULL) {
        pc.printf("Open Error!!!\n");
    }else{
        fscanf(fp2, "%i",&position);
        index = position+1;
        pc.printf("index: %i\n",index);

        fclose(fp2);
    }
    return position;
}
void OTP::downloadCipherToSD(){
    std::string h(arr);
    fprintf(fp, h.c_str());
    fclose(fp);
    pc.printf("Finished\n");
}
void OTP::setOTP(int diff){
//    arr = "";
    mkdir("/sd/mydir", 0777);
    fp = fopen("/sd/mydir/OTP.txt", "w");
    if(fp == NULL) {
        printf("Open Error!!!\n");
    }
    for(int i = 0; i<1000; i++)
        arr[i] = ('A'+(((rand()+diff)%26)));
    arr[1000] = '\0';
}
OTP::OTP(){
    file = "/sd/mydir/OTP.txt";
//    arr = "";
//    code = 'A';
    fp12 = fopen("/sd/mydir/OTP.txt", "r");
//    ifstream inputObjectForFile("/sd/mydir/OTP.txt", ios::in);
    std::string out;
    //while (inputObjectForFile >> out)
//    {
//        arr = out;
//    }
//    inputObjectForFile.close();
    if(fp12 == NULL) {
        printf("Open Error!!!\n"); 
    }else{
        fscanf(fp12, "%s",arr); 
//        arr += out;
        pc.printf("arr: %s\n",arr);
//        fclose(fp12);
    }
//    pc.printf("arr: %s\n",arr);
    fclose(fp12);
//    pc.printf("arr: %s\n",arr);
    ptr = &arr[0];
    
}
//std::string OTP::getArr(){
//    fp12 = fopen("/sd/mydir/OTP.txt", "r");
////    ifstream inputObjectForFile("/sd/mydir/OTP.txt", ios::in);
//    std::string out;
//    //while (inputObjectForFile >> out)
////    {
////        arr = out;
////    }
////    inputObjectForFile.close();
//    if(fp12 == NULL) {
//        printf("Open Error!!!\n"); 
//    }else{
//        fscanf(fp12, "%s",out); 
//        arr += out;
//        pc.printf("arr: %s\n",arr);
////        fclose(fp12);
//    }
//    pc.printf("arr: %s\n",arr);
////    fclose(fp12);
//    pc.printf("arr: %s\n",arr);
//    return arr;
//}
void OTP::close(){
    fclose(fp12);
    fclose(fp);
}
