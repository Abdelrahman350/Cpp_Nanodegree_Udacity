#ifndef _MATH_HPP_
#define _MATH_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cmath>
#include "../include/Matrix.hpp"
#include<memory>
using namespace std;

namespace utils {
    class Math {
    public:
        static shared_ptr<Matrix> multiplyMatrix(shared_ptr<Matrix> a, shared_ptr<Matrix> b);
    private:
    };
}

#endif
