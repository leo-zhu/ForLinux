//---------------------------------------------------------
// Filename: matrix.cpp
//
// Matrix multiplication and transpose
//
// Author:  Leo Zhu
// Date:    06/20/2019
//---------------------------------------------------------

#include <assert.h>
#include <cstddef>
#include <iostream>
//#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <valarray>
#include <iterator>
#include <thread>
#include <exception>

#include "matrix.hh"


std::string errof_message
(
    const std::string& f_fileName,
    const std::string& f_function,
    const size_t       f_line,
    const std::string& msg
)
{
    std::stringstream eMessage;
    eMessage << "[Error] file : " << f_fileName << std::endl;
    eMessage << "    function : " << f_function << std::endl;
    eMessage << "        line : " << f_line << std::endl;
    eMessage << "     message : " << msg << std::endl;
    return eMessage.str();

}


// constructor
template <class T>
Matrix<T>::Matrix ()
: m_array(std::valarray<T>())
, m_nRow(0)
, m_nColumn(0)
{};

// constructor
template <class T>
Matrix<T>::Matrix
(
    const std::valarray<T>& f_array, 
    const size_t            f_nRow,
    const size_t            f_nCol
) 
: m_array(f_array)
, m_nRow(f_nRow)
, m_nColumn(f_nCol)
{};

// constructor
template <class T>
Matrix<T>::Matrix
(
    const size_t f_nRow,
    const size_t f_nCol
)
: m_nRow(f_nRow)
, m_nColumn(f_nCol)
{
    m_array = std::valarray<T>(m_nRow * m_nColumn);
}


// matrix element at index
template <class T>
T &Matrix<T>::operator[]
(
    size_t f_index
)
{
    assert(f_index < m_nRow * m_nColumn);
    return m_array[f_index];
}


// matrix transpose
template <class T>
Matrix<T> Matrix<T>::transpose() const
{
    std::valarray<T> resultArray(m_nColumn * m_nRow);
    for (size_t i=0; i<m_nColumn; i++) {
        resultArray[std::slice(i*m_nRow, m_nRow, 1)] = m_array[std::slice(i, m_nRow, m_nColumn)];
    }
    return std::move(Matrix(resultArray, m_nColumn, m_nRow));
}


// matrix multiplication
template <class T>
Matrix<T> Matrix<T>::operator* 
(
    const Matrix& f_m
) const
{
    if (m_nColumn != f_m.nRow()) {
        std::stringstream msg;
        msg << "left-hand matrix column number (" << m_nColumn << ") != right-hand matrix row number (" << f_m.nRow() << ")" << std::endl;
        throw errof_message(__FILE__, __PRETTY_FUNCTION__, __LINE__, msg.str());
    }

    Matrix result(m_nRow, f_m.nColumn());
    for(size_t i = 0; i < m_nRow; ++i)
        for(size_t j = 0; j < f_m.nColumn(); ++j) {
            result[i*f_m.nColumn() + j] = (row(i) * f_m.column(j)).sum();
        }
    return std::move(result);
}


// dump matrix
template <class T>
void Matrix<T>::print
(
    std::streamsize f_width
) const 
{
    std::streamsize originalWidth;
    if (0 != f_width) {
        originalWidth = std::cout.width(f_width);
    }
    for (size_t i=0; i<m_nRow; i++) {
        for (size_t j=0; j<m_nColumn; j++) {
            std::cout << ' ' << m_array[i*m_nColumn + j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    if (0 != f_width) {
        std::cout.width(originalWidth);
    }
}


int main(int argc, char *argv[])
{
    Matrix<double> m1 = {std::valarray<double>{1, 2, 3, 4, 5, 6}, 2, 3};
    Matrix<double> m2 = {std::valarray<double>(10, 6), 3, 2};
    Matrix<double> m3 = {std::valarray<double>(10, 8), 4, 2};

    try {
        std::cout << "m0" << std::endl;
        Matrix<int> m0(5, 6);
        m0.print();

        std::cout << "Matrix 1" << std::endl;
        m1.print();

        std::cout << "Matrix 2" << std::endl;
        m2.print();

        std::cout << "Matrix 1 transpose" << std::endl;
        const auto& m1t = m1.transpose();
        m1t.print();

        std::cout << "m1 * m2" << std::endl;
        Matrix<double> mr1 = m1 * m2;
        mr1.print();

        std::cout << "m1 * m3" << std::endl;
        Matrix<double> mr2 = m1 * m3;
        mr2.print();
    }
    catch(std::string& msg) {
        std::cout << msg << std::endl;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
