#include "../include/Matrix.hpp"

// Constructor
Matrix::Matrix(int numRows, int numCols, bool isRandom) {
    numRows_ = numRows;
    numCols_ = numCols;
    for (int i = 0; i < numRows; i++) {
        vector<double> colValues;
        for (int j = 0; j < numCols; j++) {
            double r = isRandom == true ? generateRandomNumber() : 0.00;
            colValues.push_back(r);
        }
        values_.push_back(colValues);
    }
}


shared_ptr<Matrix> Matrix::transpose() {
    shared_ptr<Matrix> m = shared_ptr<Matrix> (new Matrix(numCols_, numRows_, false));
    for (int i = 0; i < numRows_; i++) {
        for (int j = 0; j < numCols_; j++) {
            m->setMatrixValue(j, i, getMatrixValue(i, j));
        }
    }
    return m;
}


double Matrix::generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.0001, 0.0001);
    return dis(gen);
}
