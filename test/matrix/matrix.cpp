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

class Matrix {

public:
    // constructor
    Matrix ()
    : m_array(std::valarray<double>())
    , m_nRow(0)
    , m_nColumn(0)
    {};

    // constructor
    Matrix
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
    Matrix
    (
        const size_t f_nRow,
        const size_t f_nCol
    )
    : m_nRow(f_nRow)
    , m_nColumn(f_nCol)
    {
        m_array = std::valarray<double>(m_nRow * m_nColumn);
    }

    size_t nRow() const { return m_nRow; }
    void nRow(size_t s) { m_nRow = s; m_array.resize(m_nRow * m_nColumn); }

    size_t nColumn() const { return m_nColumn; }
    void nColumn(size_t s) { m_nColumn = s; m_array.resize(m_nRow * m_nColumn); }

    std::valarray<double> row(size_t f_index) const { 
        assert(f_index < m_nRow);
        return m_array[std::slice(f_index * m_nColumn, m_nColumn, 1)];
    }

    std::valarray<double> column(size_t f_index) const { 
        assert(f_index < m_nColumn);
        return m_array[std::slice(f_index, m_nRow, m_nColumn)]; 
    }

    double &operator[](size_t f_index) {
        assert(f_index < m_nRow * m_nColumn);
        return m_array[f_index];
    }

    Matrix operator*(const Matrix&);
    Matrix transpose();

    void print(std::streamsize width = 0) const {
        std::streamsize originalWidth;
        if (0 != width) {
            originalWidth = std::cout.width(width);
        }
        for (size_t i=0; i<m_nRow; i++) {
            for (size_t j=0; j<m_nColumn; j++) {
                std::cout << ' ' << m_array[i*m_nColumn + j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        if (0 != width) {
            std::cout.width(originalWidth);
        }
    }


protected: 
    std::valarray<double> m_array; // Leo: should use template type T
    size_t                m_nRow;
    size_t                m_nColumn;
};


// matrix transpose
Matrix Matrix::transpose()
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
)
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
