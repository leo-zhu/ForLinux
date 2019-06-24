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
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
//#include <vector>
#include <valarray>
//#include <iterator>
//#include <thread>
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


// matrix row at index
template <class T>
std::valarray<T> Matrix<T>::row(size_t f_index) const { 
    if (not (f_index < m_nRow)) {
        std::stringstream msg;
        msg << "row index " << f_index << " is out of range - total number of rows: " << m_nRow << std::endl;
        throw errof_message(__FILE__, __PRETTY_FUNCTION__, __LINE__, msg.str());
    }
    return m_array[std::slice(f_index * m_nColumn, m_nColumn, 1)];
}


// matrix column at index
template <class T>
std::valarray<T> Matrix<T>::column(size_t f_index) const { 
    if (not (f_index < m_nColumn)) {
        std::stringstream msg;
        msg << "column index " << f_index << " is out of range - total number of columns: " << m_nColumn << std::endl;
        throw errof_message(__FILE__, __PRETTY_FUNCTION__, __LINE__, msg.str());
    }
    return m_array[std::slice(f_index, m_nRow, m_nColumn)]; 
}


// matrix element at (rowIndex, columnIndex)
template <class T>
T &Matrix<T>::operator()
(
    size_t f_rowIndex, 
    size_t f_columnIndex
)
{
    if (not (f_rowIndex < m_nRow)) {
        std::stringstream msg;
        msg << "row index " << f_rowIndex << " is out of range - total number of rows: " << m_nRow << std::endl;
        throw errof_message(__FILE__, __PRETTY_FUNCTION__, __LINE__, msg.str());
    }
    if (not (f_columnIndex < m_nColumn)) {
        std::stringstream msg;
        msg << "column index " << f_columnIndex << " is out of range - total number of columns: " << m_nColumn << std::endl;
        throw errof_message(__FILE__, __PRETTY_FUNCTION__, __LINE__, msg.str());
    }
    return m_array[f_rowIndex*m_nColumn + f_columnIndex];

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
            result(i, j) = (row(i) * f_m.column(j)).sum();
        }
    return std::move(result);
}


// print matrix
template <class T>
void Matrix<T>::print
(
    std::streamsize f_width
) const 
{
    for (size_t i=0; i<m_nRow; i++) {
        for (size_t j=0; j<m_nColumn; j++) {
            std::cout << " " << std::setw(f_width) << m_array[i*m_nColumn + j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


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
