#ifndef MATRIX_HH
#define MATRIX_HH

//---------------------------------------------------------
// Filename: matrix.hh
//
// Matrix multiplication and transpose
//
// Author:  Leo Zhu
// Date:    06/20/2019
//---------------------------------------------------------

template <class T>
class Matrix {

public:
    // constructor
    Matrix();
    Matrix(const size_t, const size_t);
    Matrix(const std::valarray<T>&, const size_t, const size_t);

    size_t nRow() const { return m_nRow; }
    void nRow(size_t s) { m_nRow = s; m_array.resize(m_nRow * m_nColumn); }

    size_t nColumn() const { return m_nColumn; }
    void nColumn(size_t s) { m_nColumn = s; m_array.resize(m_nRow * m_nColumn); }

    std::valarray<T> row(size_t f_index) const;
    std::valarray<T> column(size_t f_index) const;

    T &operator()(size_t, size_t);
    Matrix operator*(const Matrix&) const;
    Matrix transpose() const;

    void print(std::streamsize = 0) const;

private: 
    std::valarray<T> m_array;
    size_t           m_nRow;
    size_t           m_nColumn;
};

#endif // MATRIX_HH
