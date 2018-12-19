
#include "complex.h"
#include <cmath>
#include <iomanip>

using namespace std;

//default constructor
Complex::Complex(){
    real = 0;
    imag = 0;
    nan = 0;
}
//single parameter constructor for real values
Complex::Complex(double realV){
    real = realV;
    imag = 0;
    nan = 0;
}
//double parameter constructor for real and imaginary values
Complex::Complex(double realV, double imagV){
    real = realV;
    imag = imagV;
    nan = 0;
}
//get the real value
double Complex::getReal(){
    return real;
}
//get the imaginary value
double Complex::getImag(){
    return imag;
}
//display polar values of the complex numbers
void Complex::displayPolar(){
    //Get r value
    double rVal = sqrt(pow(real,2)+pow(imag,2));
    //get the angle/theta value
    double thetaVal = acos(real/rVal);
    cout << rVal << " < "<<  thetaVal << endl;
}
///display rectangular values of the complex numbers
void Complex::displayRect(){
    cout << std::setprecision(6) <<  real << " + "<<  std::setprecision(6) << imag << "j" << endl;
}
//Set complex values -- real and imaginary values
void Complex::setComplex(double realV, double imagV){
    real = realV;
    imag = imagV;
    nan = 0;
}
//Operator overloader for <<
ostream& operator<<(ostream& os, const Complex& complex)
{
    //return nan if the divsion of the complex value is with zero as the denominator
    if(complex.nan == 1){
        os << "NaN"<< endl;
        return os;
    }
    os << std::setprecision(6) <<  complex.real << " + " << std::setprecision(6) << complex.imag << "j";
    return os;
}
//Operator overloader for +
Complex Complex::operator+(Complex RHS) {
    real = this->getReal()+RHS.getReal();
    imag = this->getImag()+RHS.getImag();
    return (*this);
}
//Operator overloader for -
Complex Complex::operator-(Complex RHS) {
    Complex sum;
    sum.real = this->getReal()-RHS.getReal();
    sum.imag = this->getImag()-RHS.getImag();
    return (sum);
}
//Operator overloader for *
Complex Complex::operator*(Complex RHS) {
    Complex sum;
    sum.real = (this->getReal())*(RHS.getReal()) - (this->getImag())*(RHS.getImag());
    sum.imag = (this->getReal())*(RHS.getImag()) + (this->getImag())*(RHS.getReal());
    return (sum);
}
//Operator overloader for /
Complex Complex::operator/(Complex RHS) {
    Complex sum;
    //Checks if inputs are zero.
    if(RHS.getReal() == 0 || RHS.getImag() == 0){
        sum.nan = 1;
        return sum;
    }else{
        sum.real=(((this->real)*(RHS.real))+((this->imag)*(RHS.imag)))/(pow(RHS.real,2)+pow(RHS.imag,2));
        sum.imag=(((RHS.real)*(this->imag))-((this->real)*(RHS.imag)))/(pow(RHS.real,2)+pow(RHS.imag,2));
        return (sum);
    }
}
//Operator overloader for ! --> get conjugate
Complex Complex::operator!(){
    (*this).imag = -((*this).imag);
    return (*this);
}

