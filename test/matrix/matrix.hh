#ifndef MATRIX_HH
#define MATRIX_HH

//---------------------------------------------------------
// Filename: matrix.cpp
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
    Matrix(const std::valarray<T>&, const size_t, const size_t);
    Matrix(const size_t, const size_t);

    size_t nRow() const { return m_nRow; }
    void nRow(size_t s) { m_nRow = s; m_array.resize(m_nRow * m_nColumn); }

    size_t nColumn() const { return m_nColumn; }
    void nColumn(size_t s) { m_nColumn = s; m_array.resize(m_nRow * m_nColumn); }

    // Leo: do we need this?
    std::valarray<T> row(size_t f_index) const { 
        assert(f_index < m_nRow);
        return m_array[std::slice(f_index * m_nColumn, m_nColumn, 1)];
    }

    // Leo: do we need this?
    std::valarray<T> column(size_t f_index) const { 
        assert(f_index < m_nColumn);
        return m_array[std::slice(f_index, m_nRow, m_nColumn)]; 
    }

    T &operator[](size_t);
    Matrix operator*(const Matrix&) const;
    Matrix transpose() const;

    void print(std::streamsize = 0) const;

private: 
    std::valarray<T> m_array; // Leo: should use template type T
    size_t                m_nRow;
    size_t                m_nColumn;
};

#endif // MATRIX_HH
