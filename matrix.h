#ifndef _MAREIX_H_
#define _MAREIX_H_

#include <vector>
#include <utility>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "vector_arithmetic.h"

using std::vector ;

template <typename ValueType>
class matrix
{
public:

    matrix();
    matrix(int row, int col);
    matrix(const matrix<ValueType>& m);
    matrix(matrix<ValueType>&& m);
    matrix(const vector<vector<ValueType>>& vec);
    matrix(vector<vector<ValueType>>&& vec);

    matrix<ValueType>& operator=(const matrix<ValueType>& m);
    matrix<ValueType>& operator=(matrix<ValueType>&& m);
    matrix<ValueType>& operator=(const vector<vector<ValueType>>& vec);
    matrix<ValueType>& operator=(vector<vector<ValueType>>&& vec);
    bool operator==(const matrix<ValueType>& m);
    bool operator!=(const matrix<ValueType>& m);

    matrix<ValueType>& operator+=(const matrix<ValueType>& m);
    matrix<ValueType>& operator-=(const matrix<ValueType>& m);
    matrix<ValueType>& operator*=(const matrix<ValueType>& m); // scaler multiplication
    matrix<ValueType>& operator/=(const matrix<ValueType>& m); // scaler division
    matrix<ValueType>& operator+=(const ValueType& val);
    matrix<ValueType>& operator-=(const ValueType& val);
    matrix<ValueType>& operator*=(const ValueType& val);
    matrix<ValueType>& operator/=(const ValueType& val);
    vector<ValueType>& operator[](int rowIndex);

    matrix<ValueType> multiply(matrix<ValueType>& m); // matrices multiplication
    matrix<ValueType>& invert();
    matrix<ValueType> transpose();
    matrix<ValueType> power(int n);

    matrix<ValueType>& replace_row(vector<ValueType> vec, int index);
    matrix<ValueType>& replace_col(vector<ValueType> vec, int index);
    matrix<ValueType>& push_row(vector<ValueType> vec);
    matrix<ValueType>& push_col(vector<ValueType> vec);
    vector<ValueType> get_row(int index);
    vector<ValueType> get_col(int index);
    matrix<ValueType>& erase_row(int index);
    matrix<ValueType>& erase_col(int index);
    matrix<ValueType>& swap_rows(int row1, int row2);
    matrix<ValueType>& swap_cols(int col1, int col2);



    matrix<ValueType>& print_r();
    matrix<ValueType>& print_r(std::ostream& os);
    matrix<ValueType>& print_l(); // matlab format
    matrix<ValueType>& print_l(std::ostream& os);

    matrix<ValueType>& resize(int row, int col);
    std::pair<int, int> get_dims();
    int get_rows();
    int get_cols();
    static std::pair<int, int> check_dims(const vector<vector<ValueType>>& vec);

    template <typename T> friend
    std::ostream& operator<<(std::ostream& os,const matrix<T>& m);
    template <typename T> friend
    matrix<T> subMatrix(matrix<T> m, int row, int col);
private:
    int rows ; int cols ;
    vector<vector<ValueType>> elements;
};

template <typename ValueType>
matrix<ValueType>::matrix()
    : rows(0), cols(0) {}

template <typename ValueType>
matrix<ValueType>::matrix(int row, int col)
    : rows(row), cols(col)
{
    elements.resize(row);
    for(int i = 0; i < row; i++)
        elements[i].resize(col);
}

template <typename ValueType>
matrix<ValueType>::matrix(const matrix<ValueType>& m)
    : rows(m.rows), cols(m.cols), elements(m.elements) {}

template <typename ValueType>
matrix<ValueType>::matrix(matrix<ValueType>&& m)
    : rows(m.rows), cols(m.cols), elements(std::move(m.elements)) {}

template <typename ValueType>
matrix<ValueType>::matrix(const vector<vector<ValueType>>& vec)
{
    std::pair<int, int> p = check_dims(vec);
    if(p.first < 0)
        throw std::length_error("matrix -> vectors dimentions are not consistent");
    rows = p.first;
    cols = p.second;
    elements = vec ;
}

template <typename ValueType>
matrix<ValueType>::matrix(vector<vector<ValueType>>&& vec)
{
    std::pair<int, int> p = check_dims(vec);
    if(p.first < 0)
        throw std::length_error("matrix -> vectors dimentions are not consistent");
    rows = p.first;
    cols = p.second;
    elements = std::move(vec) ;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator=(const matrix<ValueType>& m)
{
    rows = m.rows; cols = m.cols;
    elements = m.elements;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator=(matrix<ValueType>&& m)
{
    rows = m.rows; cols = m.cols;
    elements = std::move(m.elements);
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator=(const vector<vector<ValueType>>& vec)
{
    std::pair<int, int> p = check_dims(vec);
    if(p.first < 0)
        throw std::length_error("matrix -> vectors dimentions are not consistent");
    rows = p.first;
    cols = p.second;
    elements = vec ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator=(vector<vector<ValueType>>&& vec)
{
    std::pair<int, int> p = check_dims(vec);
    if(p.first < 0)
        throw std::length_error("matrix -> vectors dimentions are not consistent");
    rows = p.first;
    cols = p.second;
    elements = std::move(vec) ;
    return *this;
}

template <typename ValueType>
bool matrix<ValueType>::operator==(const matrix<ValueType>& m)
{
    return elements == m.elements ;
}

template <typename ValueType>
bool matrix<ValueType>::operator!=(const matrix<ValueType>& m)
{
    return elements != m.elements ;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::print_r()
{
    for(const auto& items : elements)
    {
        for(const auto& element : items)
            std::cout << element << " " ;
        std::cout << std::endl ;
    }
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::print_r(std::ostream& os)
{
    for(const auto& items : elements)
    {
        for(const auto& element : items)
            os << element << " " ;
        os << std::endl ;
    }
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::print_l()
{
    std::cout << "[" ;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++) {
            std::cout << elements[i][j] ;
            if(j<(cols-1)) std::cout << " " ;
        }
        if(i<(rows-1)) std::cout << ";" ;
    }
    std::cout << "]" ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::print_l(std::ostream& os)
{
    os << "[" ;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++) {
            os << elements[i][j] ;
            if(j<(cols-1)) os << " " ;
        }
        if(i<(rows-1)) os << ";" ;
    }
    os << "]" ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::resize(int row, int col)
{
    rows = row; cols = col;
    elements.resize(row);
    for(int i = 0; i < row; i++)
        elements[i].resize(col);
    return *this;
}

template <typename ValueType>
inline std::pair<int, int> matrix<ValueType>::get_dims()
{
    return std::make_pair(rows, cols);
}

template <typename ValueType>
inline int matrix<ValueType>::get_rows()
{
    return rows;
}

template <typename ValueType>
inline int matrix<ValueType>::get_cols()
{
    return cols;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator+=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("matrix::addition -> Matrices dimentions must be the same") ;
    auto itm = m.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
            iite += *iitm ;
            iitm++;
        });
        itm++;
    });
    /* another simple way, use one only */
    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] += m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator-=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("matrix::subtraction -> Matrices dimentions must be the same") ;
    auto itm = m.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
            iite -= *iitm ;
            iitm++;
        });
        itm++;
    });
    /* another simple way, use one only */
    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] -= m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator*=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("matrix::secalar_multiplication -> Matrices dimentions must be the same") ;
    auto itm = m.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
            iite *= *iitm ;
            iitm++;
        });
        itm++;
    });
    /* another simple way, use one only */
    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] *= m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator/=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("matrix::divsion -> Matrices dimentions must be the same") ;
    auto itm = m.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
            iite /= *iitm ;
            iitm++;
        });
        itm++;
    });
    /* another simple way, use one only */
    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] /= m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator+=(const ValueType& val)
{
    for(auto& row : elements)
        for(auto& col : row)
            col += val;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator-=(const ValueType& val)
{
    for(auto& row : elements)
        for(auto& col : row)
            col -= val;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator*=(const ValueType& val)
{
    for(auto& row : elements)
        for(auto& col : row)
            col *= val;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator/=(const ValueType& val)
{
    for(auto& row : elements)
        for(auto& col : row)
            col /= val;
    return *this;
}

template <typename ValueType>
matrix<ValueType> matrix<ValueType>::multiply(matrix<ValueType>& m)
{
    if(cols != m.rows)
        throw std::length_error("matrix::multiply -> dimentions error");
    matrix<ValueType> res(rows, m.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < m.cols; j++)
            for (int k = 0 ; k < m.rows ; k++ )
                res[i][j] += elements[i][k] * m[k][j];
    return res;
}

template <typename ValueType>
matrix<ValueType> matrix<ValueType>::power(int n)
{
    if(rows != cols)
        throw std::length_error("matrix::power -> matrix must be square");
    matrix<ValueType> res = *this;
    for(int i = 0; i < n-1; i++)
        res = res.multiply(*this);
    return res;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::invert()
{
    if(rows != cols)
        throw std::length_error("matrix::invert -> matrix must be square");
    matrix<ValueType> adj (rows, cols);
    ValueType signRow = 1 ;
    ValueType signCol = signRow ;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            adj[i][j] = det(subMatrix(*this, i, j)) * signCol;
            signCol = -signCol;
        }
        signRow = -signRow;
        signCol = signRow;
    }
    ValueType det = det(*this);
    if(det == static_cast<ValueType>(0))
        throw std::out_of_range("matrix::invert -> det equal zero");
    *this = adj.transpose() / det;
    return *this;
}

template <typename ValueType>
matrix<ValueType> matrix<ValueType>::transpose()
{
    matrix<ValueType> res(cols, rows);
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            res[j][i] = elements[i][j];
    return res;
}

template <typename ValueType>
std::pair<int, int> matrix<ValueType>::check_dims(const vector<vector<ValueType>>& vec)
{
    size_t rows = vec.size();
    size_t cols = vec[0].size();
    for(const auto& row : vec)
        if(row.size() != cols)
            return std::make_pair(-1,-1);
    return std::make_pair(rows, cols);
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::replace_row(vector<ValueType> vec, int index)
{
    if(index < 0 || index >= rows)
        throw std::out_of_range("matrix::replace_row -> trying to acess non existing row");
    if(vec.size() != cols)
        throw std::length_error("matrix::replace_row -> vector.size() must be equal to matrix::cols");
    elements[index] = vec;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::replace_col(vector<ValueType> vec, int index)
{
    if(index < 0 || index >= cols)
        throw std::out_of_range("matrix::replace_col -> trying to acess non existing column");
     if(vec.size() != rows)
        throw std::length_error("matrix::replace_col -> vector.size() must be equal to matrix::rows");
    int i = 0;
    for(auto& row : elements)
        row[index] = vec[i++];
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::push_row(vector<ValueType> vec) 
{
    if(vec.size() != cols)
        throw std::length_error("matrix::push_row -> vector.size() must be equal to matrix::cols");
    elements.push_back(vec);
    rows++;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::push_col(vector<ValueType> vec) 
{
    if(vec.size() != rows)
        throw std::length_error("matrix::push_col -> vector.size() must be equal to matrix::rows");
    int i = 0;
    for(auto& row : elements)
        row.push_back(vec[i++]);
    cols++;
    return *this;
}

template <typename ValueType>
vector<ValueType> matrix<ValueType>::get_row(int index)
{
    if(index < 0 || index >= rows)
        throw std::out_of_range("matrix::get_row -> trying to acess non existing row");
    return elements[index];
}

template <typename ValueType>
vector<ValueType> matrix<ValueType>::get_col(int index)
{
    if(index < 0 || index >= cols)
        throw std::out_of_range("matrix::get_col -> trying to acess non existing column");
    vector<ValueType> vec;
    for(const auto& row : elements)
        vec.push_back(row[index]);
    return vec;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::erase_row(int index)
{
    if(index < 0 || index >= rows)
        throw std::out_of_range("matrix::erase_row -> trying to erase non existing row");
    elements.erase(elements.begin()+index);
    rows--;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::erase_col(int index)
{
    if(index < 0 || index >= cols)
        throw std::out_of_range("matrix::erase_col -> trying to erase non existing column");
    for(auto& row : elements)
        row.erase(row.begin()+index);
    cols--;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::swap_rows(int row1, int row2)
{
    if(row1 != row2)
    {
        vector<ValueType> temp = elements[row1];
        replace_row(elements[row2], row1);
        elements[row2] = temp;
    }
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::swap_cols(int col1, int col2)
{
    if(col1 != col2)
    {
        vector<ValueType> temp = get_col(col1);
        replace_col(get_col(col2), col1);
        replace_col(temp, col2);
    }
    return *this;
}

template <typename ValueType>
matrix<ValueType> subMatrix(matrix<ValueType> m, int row, int col)
{
    m.erase_row(row);
    m.erase_col(col);
    return m;
}

template <typename ValueType>
vector<ValueType>& matrix<ValueType>::operator[](int rowIndex)
{
    return elements[rowIndex];
}

template <typename ValueType>
std::ostream& operator<<(std::ostream& os, const matrix<ValueType>& m)
{
    for(const auto& items : m.elements)
    {
        for(const auto& element : items)
            os << element << " " ;
        os << std::endl ;
    }
    return os ;
}

template <typename ValueType>
ValueType det(matrix<ValueType> m)
{
    using namespace vector_arithmetic_operations;

    if(m.get_rows() != m.get_cols())
        throw std::length_error("Error: check matrix dimentions");
    ValueType sign = 1 ;
    for(int i = 0; i < m.get_rows(); i++)
    {
        // find max in this col
        ValueType max = m[i][i];
        int index_max = i;
        for(int k = i+1; k < m.get_rows(); k++)
            if(abs(m[k][i]) > max)
            {
                max = m[k][i];
                index_max = k;
            }
        // swap the max to the beginging
        if(index_max != i)
        {
            m.swap_rows(i, index_max);
            sign -= 1 ;
        }
        // elemenate the numbers blow 
        for(int j = i+1; j < m.get_rows(); j++)
        {
            m[j] += m[i] * (-m[j][i]/m[i][i]);
            m[j][i] = 0;
        } 
    }
    // clac the determenit
    ValueType det_val = 1;
    for(int i = 0; i < m.get_rows(); i++)
        det_val *= m[i][i];
    return det_val * sign;
}
template <typename ValueType>
vector<ValueType> backSub(matrix<ValueType> m, vector<ValueType> v)
{
    using namespace vector_arithmetic_operations;
    
    if(m.get_rows() != m.get_cols())
        throw std::length_error("Error: check matrix dimentions");
    m.push_col(v);
    for(int i = 0; i < m.get_rows(); i++)
    {
        ValueType max = m[i][i];
        int index_max = i;
        for(int k = i+1; k < m.get_rows(); k++)
            if(abs(m[k][i]) > max)
            {
                max = m[k][i];
                index_max = k;
            }
        m.swap_rows(i, index_max);
        for(int j = i+1; j < m.get_rows(); j++)
        {
            m[j] += m[i] * (-m[j][i] / m[i][i]);
            m[j][i] = 0;
        }
    }
    v = m.get_col(m.get_cols()-1);
    for(int i = m.get_rows()-1; i >= 0; i--)
    {
        for(int j = i+1; j < m.get_rows(); j++)
            v[i] -= m[i][j] * v[j] ;
        v[i] /= m[i][i];
    }
    return v;
}

template <typename ValueType>
matrix<ValueType> operator+(matrix<ValueType> m1, matrix<ValueType> m2)
{
    return m1 += m2;
}

template <typename ValueType>
matrix<ValueType> operator-(matrix<ValueType> m1, matrix<ValueType> m2)
{
    return m1 -= m2;
}

template <typename ValueType>
matrix<ValueType> operator*(matrix<ValueType> m1, matrix<ValueType> m2)
{
    return m1 *= m2;
}

template <typename ValueType>
matrix<ValueType> operator/(matrix<ValueType> m1, matrix<ValueType> m2)
{
    return m1 /= m2;
}

template <typename ValueType>
matrix<ValueType> operator+(matrix<ValueType> m1, const ValueType& val)
{
    return m1 += val;
}

template <typename ValueType>
matrix<ValueType> operator-(matrix<ValueType> m1, const ValueType& val)
{
    return m1 -= val;
}

template <typename ValueType>
matrix<ValueType> operator*(matrix<ValueType> m1, const ValueType& val)
{
    return m1 *= val;
}

template <typename ValueType>
matrix<ValueType> operator/(matrix<ValueType> m1, const ValueType& val)
{
    return m1 /= val;
}

#endif
