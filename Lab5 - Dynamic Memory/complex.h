
#ifndef complex_h
#define complex_h

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Complex {
private:
    double real;
    double imag;
    int nan;
    
public:
    double getReal();
    double getImag();
    Complex();
    Complex(double real, double imag);
    Complex(double real);
    void displayPolar();
    void displayRect();
    void setComplex(double realV, double imagVal);
    Complex operator+(Complex RHS);
    Complex operator-(Complex RHS);
    Complex operator*(Complex RHS);
    Complex operator/(Complex RHS);
    Complex operator!();
    friend ostream& operator<<(ostream& os, const Complex& complex);
};
#endif /* complex_h */
