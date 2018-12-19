
#include "matrix.h"

using namespace std;

//get the current array ptr for the particular object
Complex* Matrix::getArrayPtr(){
    return ptr;
}
//get the number of total rows
int Matrix::getRows(){return rows;}
//get total number of columns
int Matrix::getCols(){return cols;}

//print the matrix
void Matrix::printMatrix(){
    cout << std::setprecision(6);
    for(int i = 0; i < (size); i++){
        //check if the imaginary value is zero -- special output
        if(ptr[i].getImag() == 0){
            cout << std::setprecision(6) << ptr[i].getReal() << "                                ";
        }else{
            cout << std::setprecision(6) << ptr[i] << "                      ";
        }
        //Goes to the next row when it is at the end of the matrix row
        if((i+1)%(cols) == 0){
            cout << "\n";
        }
    }
}
//two parameter constructor -- set values: total rows, total columns, and the overall size of the matrix single array
Matrix::Matrix(int rowsV, int colsV){
    rows = rowsV;
    cols = colsV;
    size = rowsV*colsV;
    ptr = new Complex[size];
    nan = 0;
}
//Copy Constructor -- copies each individual value from one matrix to the next
Matrix::Matrix(Matrix& matrix){
    rows = matrix.getRows();
    cols = matrix.getCols();
    size = rows*cols;
    ptr = new Complex[size];
    for(int i = 1; i <= matrix.getRows(); i++){
        for(int j = 1; j <= matrix.getCols(); j++){
            int index = cols*(i-1) + (j-1);
            ptr[index] = matrix(i,j);
        }
    }
}
//Operator overloading for = --> assignment operator overloading
Matrix & Matrix::operator=(const Matrix & RHS){
    if(RHS.nan == 1){
        return (*this);
    }
    if(this->rows == RHS.rows && this->cols == RHS.cols){
        for(int i = 1; i <= this->rows; i++){
            for(int j = 1; j <= this->cols; j++){
                (*this)(i,j) = RHS(i,j);
            }
        }
    }else{
        delete [] this->ptr;
        this->ptr = new Complex[RHS.size];
        for(int i = 1; i <= RHS.rows; i++){
            for(int j = 1; j <= RHS.cols; j++){
                (*this)(i,j) = RHS(i,j);
            }
        }
    }
    
    return (*this);
}
//Destructor to prevent memory leaks
Matrix::~Matrix(){
    delete []ptr;
}
//Operator overloading for parenthese to access 2 dimensional array
Complex & Matrix::operator()(int x, int y){
    int index = cols*(x-1) + (y-1);
    return ptr[index];
}
//Operator overloading for parenthese to access 2 dimensional array -- constant
Complex & Matrix::operator()(int x, int y) const{
    int index = cols*(x-1) + (y-1);
    return ptr[index];
}
//Operator overloading for '+' --> to add each indiviual value from one matrix to the other
Matrix Matrix::operator+(Matrix RHS){
    Matrix sum(this->rows, this-> cols);
    if(this->rows != RHS.rows && this->cols != RHS.cols){
        sum.nan = 1;
        return sum;
    }
    sum.nan = 0;
    for(int i = 1; i <= sum.getRows(); i++){
        for(int j = 1; j <= sum.getCols(); j++){
            sum(i,j) = ((*this)(i, j) + RHS(i,j));
        }
    }
    return sum;
}
//Operator overloading for '-' --> to add each indiviual value from one matrix to the other
Matrix Matrix::operator-(Matrix RHS){
    Matrix sum(this->rows, this-> cols);
    if(this->rows != RHS.rows && this->cols != RHS.cols){
        sum.nan = 1;
        return sum;
    }
    sum.nan = 0;
    for(int i = 1; i <= sum.rows; i++){
        for(int j = 1; j <= sum.cols; j++){
            sum(i,j) = ((*this)(i, j) - RHS(i,j));
        }
    }
    return sum;
}
//Operator overloading for '*' --> to add each indiviual value from one matrix to the other
Matrix Matrix::operator*(Matrix RHS){
    Matrix sum(this->rows, this->cols);
    cout<<this->cols << this->rows << RHS.rows<< RHS.cols << endl;
    if(this->rows == RHS.rows && this->cols == RHS.cols){
        for(int i = 1; i <= this->rows; i++){
            for(int j = 1; j<= RHS.cols; j++){
                sum(i,j) = 0;
                for(int k = 1; k <= this->cols; k++){
                    sum(i,j) = sum(i,j) + ((*this)(i,k)*RHS(k,j));
                }
            }
        }
    }else{
        sum.nan = 1;
        return sum;
    }
    sum.nan = 0;
    return sum;
}
//Operator overloading for '*' --> to add each indiviual value from one matrix to the complex number
Matrix operator*(Complex complex, Matrix& matrix){
    Matrix sum(matrix.rows, matrix.cols);
    for(int i = 1; i <= sum.rows; i++){
        for(int j = 1; j <= sum.cols; j++){
            sum(i,j) = complex*(matrix(i,j));
        }
    }
    return sum;
}
//Operator overloading for '*' --> to add each indiviual value from one matrix to the complex number
Matrix operator*(Matrix& matrix, Complex complex){
    Matrix sum(matrix.rows, matrix.cols);
    for(int i = 1; i <= sum.rows; i++){
        for(int j = 1; j <= sum.cols; j++){
            sum(i,j) = (matrix(i,j))*complex;
        }
    }
    return sum;
}
//Operator overloading for the transpose of the matrix '~'
Matrix Matrix::operator~(){
    Matrix sum(this->rows, this-> cols);
    for(int i = 1; i <= sum.rows; i++){
        for(int j = 1; j <= sum.cols; j++){
            sum(i,j) = (*this)(j,i);
        }
    }
    return sum;
}
//Operator overloading for the conjugate transpose of the matrix '!'
Matrix Matrix::operator!(){
    Matrix sum(this->rows, this-> cols);
    for(int i = 1; i <= sum.rows; i++){
        for(int j = 1; j <= sum.cols; j++){
            sum(i,j) = !((*this)(i,j));
        }
    }
    return sum;
}
//return the transpose of the matrix
void Matrix::transpose(){
    Matrix sum(rows,cols);
    for(int i = 1; i <= sum.rows; i++){
        for(int j = 1; j <= sum.cols; j++){
            sum(i,j) = (*this)(j,i);
        }
    }
    sum.printMatrix();
}
