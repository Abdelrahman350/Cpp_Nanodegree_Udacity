#include "../include/Math.hpp"

shared_ptr<Matrix> utils::Math::multiplyMatrix(shared_ptr<Matrix> a, shared_ptr<Matrix> b) {
    shared_ptr<Matrix> c = shared_ptr<Matrix> (new Matrix(a->getNumRows(), b->getNumCols(), false));
    for (int i = 0; i < a->getNumRows(); i++) {
        for (int j = 0; j < b->getNumCols(); j++) {
            for (int k = 0; k < b->getNumRows(); k++) {
                double p = a->getMatrixValue(i, k) * b->getMatrixValue(k, j);
                double newVal = c->getMatrixValue(i, j) + p;
                c->setMatrixValue(i, j, newVal);
            }
            c->setMatrixValue(i, j, c->getMatrixValue(i, j));
        }
    }
    return c;
}
