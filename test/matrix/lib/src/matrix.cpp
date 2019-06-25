//---------------------------------------------------------
// Filename: matrix.cpp
//
// Matrix multiplication and transpose
//
// Author:  Leo Zhu
// Date:    06/25/2019
//---------------------------------------------------------

#include <assert.h>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <valarray>
#include <exception>

#include "../include/matrix.hh"


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

// default constructor
template <class T>
Matrix<T>::Matrix ()
: m_array(std::valarray<T>())
, m_nRow(0)
, m_nColumn(0)
{};

// constructor
// initialize matrix with specified number of rows and columns
// all matrix elements are set to 0
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

// constructor
// initialize matrix with specified elements and number of rows and columns
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

// get the number of rows
template <class T>
size_t Matrix<T>::nRow() const
{ 
    return m_nRow; 
}

// set the number of rows
template <class T>
void Matrix<T>::nRow
(
    size_t s
) 
{ 
    m_nRow = s; 
    m_array.resize(m_nRow * m_nColumn); 
}

// get the number of columns
template <class T>
size_t Matrix<T>::nColumn() const
{ 
    return m_nColumn; 
}

// set the number of columns
template <class T>
void Matrix<T>::nColumn
(
    size_t s
) 
{ 
    m_nColumn = s; 
    m_array.resize(m_nRow * m_nColumn); 
}

// get matrix elements at the indexed row
template <class T>
std::valarray<T> Matrix<T>::row(size_t f_index) const { 
    if (not (f_index < m_nRow)) {
        std::stringstream msg;
        msg << "row index " << f_index << " is out of range - total number of rows: " << m_nRow << std::endl;
        throw errof_message(__FILE__, __PRETTY_FUNCTION__, __LINE__, msg.str());
    }
    return m_array[std::slice(f_index * m_nColumn, m_nColumn, 1)];
}

// get matrix elements at the indexed column
template <class T>
std::valarray<T> Matrix<T>::column(size_t f_index) const { 
    if (not (f_index < m_nColumn)) {
        std::stringstream msg;
        msg << "column index " << f_index << " is out of range - total number of columns: " << m_nColumn << std::endl;
        throw errof_message(__FILE__, __PRETTY_FUNCTION__, __LINE__, msg.str());
    }
    return m_array[std::slice(f_index, m_nRow, m_nColumn)]; 
}

// get matrix element at the specified position
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
        msg << "left-hand matrix number of columns (" << m_nColumn << ") != right-hand matrix number of rows (" << f_m.nRow() << ")" << std::endl;
        throw errof_message(__FILE__, __PRETTY_FUNCTION__, __LINE__, msg.str());
    }

    Matrix result(m_nRow, f_m.nColumn());
    for(size_t i = 0; i < m_nRow; ++i)
        for(size_t j = 0; j < f_m.nColumn(); ++j) {
            result(i, j) = (row(i) * f_m.column(j)).sum();
        }
    return std::move(result);
}

// print matrix with specified width for elements
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

template class Matrix<double>;
template class Matrix<float>;
template class Matrix<long>;
template class Matrix<unsigned long>;
template class Matrix<int>;
template class Matrix<unsigned int>;

