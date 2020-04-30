#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <memory>
using namespace std;

class Matrix {
public:
    Matrix(int numRows, int numCols, bool isRandom);
    shared_ptr<Matrix> transpose();
	
    // Setter
    void setMatrixValue(int row, int col, double value) { values_.at(row).at(col) = value; }    

    // Getters
    int getNumRows() { return numRows_; };
    int getNumCols() { return numCols_; };
    double getMatrixValue(int row, int col) { return values_.at(row).at(col); }

private:
    int numRows_;
    int numCols_;
    vector< vector<double> > values_;
    double generateRandomNumber();
};

#endif
