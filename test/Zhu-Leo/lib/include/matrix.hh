#ifndef MATRIX_HH
#define MATRIX_HH

//---------------------------------------------------------
// Filename: matrix.hh
//
// Matrix multiplication and transpose
//
// Author:  Leo Zhu
// Date:    06/25/2019
//---------------------------------------------------------

template <class T>
class Matrix {

public:
    // constructors
    Matrix();
    Matrix(const size_t, const size_t);
    Matrix(const std::valarray<T>&, const size_t, const size_t);

    // get the number of rows
    size_t nRow() const;

    // set the number of rows
    void nRow(size_t);

    // get the number of columns
    size_t nColumn() const;

    // set the number of columns
    void nColumn(size_t);

    // get matrix elements at the indexed row, index starting at 0
    std::valarray<T> row(size_t) const;

    // get matrix elements at the indexed column, index starting at 0
    std::valarray<T> column(size_t) const;

    // get reference to the matrix element at specified position
    T &operator()(size_t, size_t);

    // matrix multiplication
    Matrix operator*(const Matrix&) const;

    // matrix transpose
    Matrix transpose() const;

    // print matrix with the specified width for elements, default to 0
    void print(std::streamsize = 0) const;

private: 
    // matrix elements
    std::valarray<T> m_array;

    // number of rows
    size_t           m_nRow;

    // number of columns
    size_t           m_nColumn;
};


#endif // MATRIX_HH
