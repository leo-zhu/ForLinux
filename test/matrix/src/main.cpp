//---------------------------------------------------------
// Filename: main.cpp
//
// Matrix multiplication and transpose
//
// Author:  Leo Zhu
// Date:    06/25/2019
//---------------------------------------------------------

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <valarray>
#include <exception>

#include "matrix.hh"


int main(int argc, char *argv[])
{
    size_t outputWidth = 6;

    Matrix<double> m0 (3, 5);
    Matrix<double> m1 = {std::valarray<double>{1, 2, 3, 4, 5, 6}, 2, 3};
    Matrix<double> m2 = {std::valarray<double>(100, 6), 3, 2};
    Matrix<double> m3 = {std::valarray<double>(100, 8), 4, 2};

    try {
        std::cout << "Matrix 0" << std::endl;
        m0.print(outputWidth);

        std::cout << "Matrix 1" << std::endl;
        m1.print(outputWidth);

        std::cout << "Matrix 2" << std::endl;
        m2.print(outputWidth);

        std::cout << "Matrix 3" << std::endl;
        m3.print(outputWidth);

        std::cout << "Matrix 1 transpose" << std::endl;
        const auto& m1t = m1.transpose();
        m1t.print(outputWidth);

        std::cout << "Multiplication: Matrix 1 * Matrix 2" << std::endl;
        Matrix<double> mm12 = m1 * m2;
        mm12.print(outputWidth);

        std::cout << "Multiplication: Matrix 1 * Matrix 3" << std::endl;
        Matrix<double> mm13 = m1 * m3;
        mm13.print(outputWidth);
    }
    catch(std::string& msg) {
        std::cout << msg << std::endl;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
