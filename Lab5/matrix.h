
#ifndef matrix_h
#define matrix_h

#include <iostream>
#include "complex.h"
#include <string>
#include <iomanip>
#define MATRIX_FIELD 30

using namespace std;

//This is a class prototype to let the compiler know
//that I intend to define a class Matrix. It is needed
//for the global function definition that I put before
class Matrix;
std::ostream& operator<< (std::ostream &, Matrix &);
Matrix operator*(Complex, Matrix &);
class Matrix
{
private:
    int rows;
    int cols;
    Complex* ptr;
    int size;
    int nan;
public:
    Matrix(int rowsV, int colsV);
    Matrix(Matrix& matrix);
    Complex& operator()(int x, int y);
    Complex& operator()(int x, int y) const;
    Matrix operator+(Matrix RHS);
    Matrix & operator=(const Matrix & RHS);
    Matrix operator-(Matrix RHS);
    Matrix operator*(Matrix RHS);
    Matrix operator~();
    Matrix operator!();
    ~Matrix();
    void transpose();
    void printMatrix();
    Complex* getArrayPtr();
    int getRows();
    int getCols();

    friend Matrix operator*(Complex, Matrix &);
    friend Matrix operator*(Matrix& matrix, Complex complex);
    
    
    friend std::ostream& operator<<(std::ostream& os,Matrix& matrix){
        cout << std::setprecision(6);

        Complex* ptr = matrix.getArrayPtr();
        for(int i = 0; i < (matrix.getRows()*matrix.getCols()); i++){
            if(ptr[i].getImag() == 0){
                os << std::setprecision(6) << ptr[i].getReal() << "                                ";
            }else{
                os << std::setprecision(6) << ptr[i] << "                      ";
            }
            if(((i+1)%(matrix.getCols())) == 0){
                os << "\n";
            }
        }
        return os;
    }

};
#endif

