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


std::string errorMessage
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


//template <class T>

// constructor
Matrix::Matrix ()
: m_array(std::valarray<double>())
, m_nRow(0)
, m_nColumn(0)
{};

// constructor
Matrix::Matrix
(
    const std::valarray<double>& f_array, 
    const size_t                 f_nRow,
    const size_t                 f_nCol
) 
: m_array(f_array)
, m_nRow(f_nRow)
, m_nColumn(f_nCol)
{};

// construct
Matrix::Matrix
(
    const size_t f_nRow,
    const size_t f_nCol
)
: m_nRow(f_nRow)
, m_nColumn(f_nCol)
{
    m_array = std::valarray<double>(m_nRow * m_nColumn);
}


double &Matrix::operator[]
(
    size_t f_index
)
{
    assert(f_index < m_nRow * m_nColumn);
    return m_array[f_index];
}


// matrix transpose
Matrix Matrix::transpose() const
{
    std::valarray<double> resultArray(m_nColumn * m_nRow);
    for (size_t i=0; i<m_nColumn; i++) {
        resultArray[std::slice(i*m_nRow, m_nRow, 1)] = m_array[std::slice(i, m_nRow, m_nColumn)];
    }
    return std::move(Matrix(resultArray, m_nColumn, m_nRow));
}


// matrix multiplication
Matrix Matrix::operator* 
(
    const Matrix& rm
) const
{
    //assert(m_nColumn == rm.nRow());

    if (m_nColumn != rm.nRow()) {

        std::stringstream msg;
        msg << "left-hand matrix column number (" << m_nColumn << ") != right-hand matrix row number (" << rm.nRow() << ")" << std::endl;
        throw errorMessage(__FILE__, __PRETTY_FUNCTION__, __LINE__, msg.str());
    }

    Matrix result(m_nRow, rm.nColumn());
    for(size_t i = 0; i < m_nRow; ++i)
        for(size_t j = 0; j < rm.nColumn(); ++j) {
            result[i*rm.nColumn() + j] = (row(i) * rm.column(j)).sum();
        }
    return std::move(result);
}


// dump matrix
void Matrix::print
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
    Matrix m1 = {std::valarray<double>{1, 2, 3, 4, 5, 6}, 2, 3};
    Matrix m2 = {std::valarray<double>(10, 6), 3, 2};
    Matrix m3 = {std::valarray<double>(10, 8), 4, 2};

    try {
        std::cout << "Matrix 1" << std::endl;
        m1.print();

        std::cout << "Matrix 2" << std::endl;
        m2.print();

        std::cout << "Matrix 1 transpose" << std::endl;
        const auto& m1t = m1.transpose();
        m1t.print();

        std::cout << "m1 * m2" << std::endl;
        Matrix mr1 = m1 * m2;
        mr1.print();

        std::cout << "m1 * m3" << std::endl;
        Matrix mr2 = m1 * m3;
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
