/******************************************************************************
 * Copyright (C) 2019 by Hassan El-shazly
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright.
 *
 *****************************************************************************/
/**
 * @file matrix_impl.h
 * @brief 
 * 
 * This file implements the <code>matrix</code> class, which provides an
 * efficient, safe, convenient matrix type in C++ that can be used in 
 * mathematical computations
 *
 * @author Hassan El-shazly
 * @date Last Edit Jun-2020
 *
 */

#ifndef _MAREIX_IMPL_H_
#define _MAREIX_IMPL_H_

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "matrix_def.h"
#include "vector_arithmetic.h"

template <typename ValueType>
matrix<ValueType>::matrix()
    : rows(0), cols(0)
{
    // do nothing
}

template <typename ValueType>
matrix<ValueType>::matrix(int row, int col)
    : rows(row), cols(col)
{
    elements.resize(row);
    for (int i = 0; i < row; i++)
        elements[i].resize(col);
}

template <typename ValueType>
matrix<ValueType>::matrix(const matrix<ValueType> &mat)
    : rows(mat.rows), cols(mat.cols), elements(mat.elements)
{
    // do nothing
}

template <typename ValueType>
matrix<ValueType>::matrix(matrix<ValueType> &&mat)
    : rows(mat.rows), cols(mat.cols), elements(std::move(mat.elements))
{
    // do nothing
}

template <typename ValueType>
matrix<ValueType>::matrix(const vector<vector<ValueType>> &vec)
{
    std::pair<int, int> p = check_dim(vec);
    if (p.first < 0)
        throw std::length_error("matrix -> vectors dimentions are not consistent");
    rows = p.first;
    cols = p.second;
    elements = vec;
}

template <typename ValueType>
matrix<ValueType>::matrix(vector<vector<ValueType>> &&vec)
{
    std::pair<int, int> p = check_dim(vec);
    if (p.first < 0)
        throw std::length_error("matrix -> vectors dimentions are not consistent");
    rows = p.first;
    cols = p.second;
    elements = std::move(vec);
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator=(const matrix<ValueType> &mat)
{
    rows = mat.rows;
    cols = mat.cols;
    elements = mat.elements;
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator=(matrix<ValueType> &&mat)
{
    rows = mat.rows;
    cols = mat.cols;
    elements = std::move(mat.elements);
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator=(const vector<vector<ValueType>> &vec)
{
    std::pair<int, int> p = check_dim(vec);
    if (p.first < 0)
        throw std::length_error("matrix -> vectors dimentions are not consistent");
    rows = p.first;
    cols = p.second;
    elements = vec;
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator=(vector<vector<ValueType>> &&vec)
{
    std::pair<int, int> p = check_dim(vec);
    if (p.first < 0)
        throw std::length_error("matrix -> vectors dimentions are not consistent");
    rows = p.first;
    cols = p.second;
    elements = std::move(vec);
    return *this;
}

template <typename ValueType>
bool matrix<ValueType>::operator==(const matrix<ValueType> &mat)
{
    return elements == mat.elements;
}

template <typename ValueType>
bool matrix<ValueType>::operator!=(const matrix<ValueType> &mat)
{
    return elements != mat.elements;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::print_r()
{
    for (const auto &items : elements)
    {
        for (const auto &element : items)
            std::cout << element << " ";
        std::cout << std::endl;
    }
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::print_r(std::ostream &os)
{
    for (const auto &items : elements)
    {
        for (const auto &element : items)
            os << element << " ";
        os << std::endl;
    }
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::print_l()
{
    std::cout << "[";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << elements[i][j];
            if (j < (cols - 1))
                std::cout << " ";
        }
        if (i < (rows - 1))
            std::cout << ";";
    }
    std::cout << "]";
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::print_l(std::ostream &os)
{
    os << "[";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            os << elements[i][j];
            if (j < (cols - 1))
                os << " ";
        }
        if (i < (rows - 1))
            os << ";";
    }
    os << "]";
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::resize(int row, int col)
{
    rows = row;
    cols = col;
    elements.resize(row);
    for (int i = 0; i < row; i++)
        elements[i].resize(col);
    return *this;
}

template <typename ValueType>
inline std::pair<int, int> matrix<ValueType>::get_dim()
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
matrix<ValueType> &matrix<ValueType>::operator+=(const matrix<ValueType> &mat)
{
    if (rows != mat.rows || cols != mat.cols)
        throw std::length_error("matrix::addition -> Matrices dimentions must be the same");
    auto itm = mat.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto &ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto &iite) {
            iite += *iitm;
            iitm++;
        });
        itm++;
    });

    /* Another simple way, use one only */

    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] += mat.elements[i][j] ;

    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator-=(const matrix<ValueType> &mat)
{
    if (rows != mat.rows || cols != mat.cols)
        throw std::length_error("matrix::subtraction -> Matrices dimentions must be the same");
    auto itm = mat.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto &ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto &iite) {
            iite -= *iitm;
            iitm++;
        });
        itm++;
    });

    /* Another simple way, use one only */

    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] -= mat.elements[i][j] ;

    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator*=(const matrix<ValueType> &mat)
{
    if (rows != mat.rows || cols != mat.cols)
        throw std::length_error("matrix::scalar_multiplication -> Matrices dimentions must be the same");
    auto itm = mat.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto &ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto &iite) {
            iite *= *iitm;
            iitm++;
        });
        itm++;
    });
    /* Another simple way, use one only */
    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] *= mat.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator/=(const matrix<ValueType> &mat)
{
    if (rows != mat.rows || cols != mat.cols)
        throw std::length_error("matrix::divsion -> Matrices dimentions must be the same");
    auto itm = mat.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto &ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto &iite) {
            iite /= *iitm;
            iitm++;
        });
        itm++;
    });

    /* Another simple way, use one only */

    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] /= mat.elements[i][j] ;

    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator+=(const ValueType val)
{
    for (auto &row : elements)
        for (auto &col : row)
            col += val;
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator-=(const ValueType val)
{
    for (auto &row : elements)
        for (auto &col : row)
            col -= val;
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator*=(const ValueType val)
{
    for (auto &row : elements)
        for (auto &col : row)
            col *= val;
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::operator/=(const ValueType val)
{
    for (auto &row : elements)
        for (auto &col : row)
            col /= val;
    return *this;
}

template <typename ValueType>
matrix<ValueType> matrix<ValueType>::multiply(matrix<ValueType> &mat)
{
    if (cols != mat.rows)
        throw std::length_error("matrix::multiply -> check matrices dimentions");
    matrix<ValueType> res(rows, mat.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < mat.cols; j++)
            for (int k = 0; k < mat.rows; k++)
                res[i][j] += elements[i][k] * mat[k][j];
    return res;
}

template <typename ValueType>
matrix<ValueType> matrix<ValueType>::power(int n)
{
    if (rows != cols)
        throw std::length_error("matrix::power -> matrix must be square");
    matrix<ValueType> res = *this;
    for (int i = 0; i < n - 1; i++)
        res = res.multiply(*this);
    return res;
}

template <typename ValueType>
matrix<ValueType> matrix<ValueType>::invert()
{
    if (rows != cols)
        throw std::length_error("matrix::invert -> matrix must be square");
    matrix<ValueType> adj(rows, cols);
    ValueType signRow = 1;
    ValueType signCol = signRow;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            adj[i][j] = determinant(sub_matrix(*this, i, j)) * signCol;
            signCol = -signCol;
        }
        signRow = -signRow;
        signCol = signRow;
    }
    ValueType det = determinant(*this);
    if (det == static_cast<ValueType>(0))
        throw std::out_of_range("matrix::invert -> Determinant equal zero");
    return adj.transpose() /= det;
}

template <typename ValueType>
matrix<ValueType> matrix<ValueType>::transpose()
{
    matrix<ValueType> res(cols, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[j][i] = elements[i][j];
    return res;
}

template <typename ValueType>
inline ValueType matrix<ValueType>::det()
{
    return determinant(*this);
}

template <typename ValueType>
inline ValueType matrix<ValueType>::det_recursive()
{
    return determinant_recursive(*this);
}

template <typename ValueType>
inline vector<ValueType> matrix<ValueType>::back_sub(vector<ValueType> vec)
{
    return back_substitution(*this, vec);
}

template <typename ValueType>
std::pair<int, int> matrix<ValueType>::check_dim(const vector<vector<ValueType>> &vec)
{
    int rows = vec.size();
    int cols = vec[0].size();
    for (const auto &row : vec)
        if (row.size() != cols)
            return std::make_pair(-1, -1);
    return std::make_pair(rows, cols);
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::replace_row(vector<ValueType> vec, int index)
{
    if (index < 0 || index >= rows)
        throw std::out_of_range("matrix::replace_row -> trying to acess non existing row");
    if (vec.size() != cols)
        throw std::length_error("matrix::replace_row -> vector.size() must be equal to matrix::cols");
    elements[index] = vec;
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::replace_col(vector<ValueType> vec, int index)
{
    if (index < 0 || index >= cols)
        throw std::out_of_range("matrix::replace_col -> trying to acess non existing column");
    if (vec.size() != rows)
        throw std::length_error("matrix::replace_col -> vector.size() must be equal to matrix::rows");
    int i = 0;
    for (auto &row : elements)
        row[index] = vec[i++];
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::push_row(const vector<ValueType> &vec)
{
    if (vec.size() != cols)
        throw std::length_error("matrix::push_row -> vector.size() must be equal to matrix::cols");
    elements.push_back(vec);
    rows++;
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::push_col(vector<ValueType> vec)
{
    if (vec.size() != rows)
        throw std::length_error("matrix::push_col -> vector.size() must be equal to matrix::rows");
    int i = 0;
    for (auto &row : elements)
        row.push_back(vec[i++]);
    cols++;
    return *this;
}

template <typename ValueType>
vector<ValueType> matrix<ValueType>::get_row(int index)
{
    if (index < 0 || index >= rows)
        throw std::out_of_range("matrix::get_row -> trying to acess non existing row");
    return elements[index];
}

template <typename ValueType>
vector<ValueType> matrix<ValueType>::get_col(int index)
{
    if (index < 0 || index >= cols)
        throw std::out_of_range("matrix::get_col -> trying to acess non existing column");
    vector<ValueType> vec;
    for (const auto &row : elements)
        vec.push_back(row[index]);
    return vec;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::erase_row(int index)
{
    if (index < 0 || index >= rows)
        throw std::out_of_range("matrix::erase_row -> trying to erase non existing row");
    elements.erase(elements.begin() + index);
    rows--;
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::erase_col(int index)
{
    if (index < 0 || index >= cols)
        throw std::out_of_range("matrix::erase_col -> trying to erase non existing column");
    for (auto &row : elements)
        row.erase(row.begin() + index);
    cols--;
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::swap_rows(int row1, int row2)
{
    if ((row1 < 0 || row1 >= rows) || (row2 < 0 || row2 >= rows))
        throw std::out_of_range("matrix::swap_rows -> trying to swap non existing rows");
    if (row1 != row2)
    {
        vector<ValueType> temp = elements[row1];
        replace_row(elements[row2], row1);
        elements[row2] = temp;
    }
    return *this;
}

template <typename ValueType>
matrix<ValueType> &matrix<ValueType>::swap_cols(int col1, int col2)
{
    if ((col1 < 0 || col1 >= cols) || (col1 < 0 || col1 >= cols))
        throw std::out_of_range("matrix::swap_rows -> trying to swap non existing columns");
    if (col1 != col2)
    {
        vector<ValueType> temp = get_col(col1);
        replace_col(get_col(col2), col1);
        replace_col(temp, col2);
    }
    return *this;
}

template <typename ValueType>
vector<ValueType> &matrix<ValueType>::operator[](int rowIndex)
{
    return elements[rowIndex];
}

template <typename ValueType>
std::ostream &operator<<(std::ostream &os, const matrix<ValueType> &mat)
{
    for (const auto &items : mat.elements)
    {
        for (const auto &element : items)
            os << element << " ";
        os << std::endl;
    }
    return os;
}

template <typename ValueType>
matrix<ValueType> sub_matrix(matrix<ValueType> mat, int row, int col)
{
    for (int i = 0; i < mat.get_rows(); i++)
        mat[i].erase(mat[i].begin() + col);
    mat.elements.erase(mat.elements.begin() + row);
    return matrix<ValueType>(std::move(mat.elements));
}

template <typename ValueType>
ValueType determinant_recursive(matrix<ValueType> mat)
{
    if (mat.get_rows() != mat.get_cols())
        throw std::length_error("matrix::determinant_recursive -> check matrix dimentions");
    if (mat.get_rows() == 1)
        return mat[0][0];

    ValueType det = ValueType();
    ValueType sign = 1;
    for (int i = 0; i < mat.get_cols(); i++)
    {
        det += mat[0][i] * determinant_recursive(sub_matrix(mat, 0, i)) * sign;
        sign = -sign;
    }
    return det;
}

template <typename ValueType>
ValueType determinant(matrix<ValueType> mat)
{
    using namespace vector_arithmetic_operations;

    if (mat.get_rows() != mat.get_cols())
        throw std::length_error("matrix::determinant -> check matrix dimentions");
    ValueType sign = 1;
    for (int i = 0; i < mat.get_rows(); i++)
    {
        // find max in this col
        ValueType max = mat[i][i];
        int index_max = i;
        for (int k = i + 1; k < mat.get_rows(); k++)
        {
            if (abs(mat[k][i]) > abs(max))
            {
                max = mat[k][i];
                index_max = k;
            }
        }
        // swap the max to the beginging
        if (index_max != i)
        {
            mat.swap_rows(i, index_max);
            sign -= 1;
        }
        // elemenate the numbers blow
        for (int j = i + 1; j < mat.get_rows(); j++)
        {
            mat[j] += mat[i] * (-mat[j][i] / mat[i][i]);
            mat[j][i] = 0;
        }
    }
    // calc the determinant
    ValueType det_val = static_cast<ValueType>(1);
    for (int i = 0; i < mat.get_rows(); i++)
        det_val *= mat[i][i];
    return det_val * sign;
}

template <typename ValueType>
vector<ValueType> back_substitution(matrix<ValueType> mat, vector<ValueType> vec)
{
    using namespace vector_arithmetic_operations;
    std::cout << mat;
    if (mat.get_rows() != mat.get_cols())
        throw std::length_error("back_substitution -> check matrix dimentions");
    mat.push_col(vec);
    for (int i = 0; i < mat.get_rows(); i++)
    {
        ValueType max = mat[i][i];
        int index_max = i;
        for (int k = i + 1; k < mat.get_rows(); k++)
        {
            if (abs(mat[k][i]) > max)
            {
                max = mat[k][i];
                index_max = k;
            }
        }
        mat.swap_rows(i, index_max);
        for (int j = i + 1; j < mat.get_rows(); j++)
        {
            mat[j] += mat[i] * (-mat[j][i] / mat[i][i]);
            mat[j][i] = 0;
        }
    }
    std::cout << mat;
    vec = mat.get_col(mat.get_cols() - 1);
    for (const auto &i : vec)
        std::cout << i << " ";
    std::cout << "\n";
    for (int i = mat.get_rows() - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < mat.get_rows(); j++)
            vec[i] -= mat[i][j] * vec[j];
        vec[i] /= mat[i][i];
    }
    for (const auto &i : vec)
        std::cout << i << " ";
    std::cout << "\n";
    return vec;
}

template <typename ValueType>
inline matrix<ValueType> operator+(matrix<ValueType> m1, const matrix<ValueType> &m2)
{
    return m1 += m2;
}

template <typename ValueType>
inline matrix<ValueType> operator-(matrix<ValueType> m1, const matrix<ValueType> &m2)
{
    return m1 -= m2;
}

template <typename ValueType>
inline matrix<ValueType> operator*(matrix<ValueType> m1, const matrix<ValueType> &m2)
{
    return m1 *= m2;
}

template <typename ValueType>
inline matrix<ValueType> operator/(matrix<ValueType> m1, const matrix<ValueType> &m2)
{
    return m1 /= m2;
}

template <typename ValueType>
matrix<ValueType> operator+(matrix<ValueType> m1, const ValueType val)
{
    return m1 += val;
}

template <typename ValueType>
inline matrix<ValueType> operator-(matrix<ValueType> m1, const ValueType val)
{
    return m1 -= val;
}

template <typename ValueType>
inline matrix<ValueType> operator*(matrix<ValueType> m1, const ValueType val)
{
    return m1 *= val;
}

template <typename ValueType>
inline matrix<ValueType> operator/(matrix<ValueType> m1, const ValueType val)
{
    return m1 /= val;
}

#endif // End of the file