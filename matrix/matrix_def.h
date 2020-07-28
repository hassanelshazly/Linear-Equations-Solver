/******************************************************************************
 * Copyright (C) 2019 by Hassan El-shazly
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. 
 *
 *****************************************************************************/
/**
 * @file matrix_def.h
 * @brief 
 * 
 * This file provides Decleration and Documentation of the <code>matrix</code> 
 * class, which provides an efficient, safe, convenient matrix type in C++ 
 * that can be used in mathematical computations.
 *
 * @author Hassan El-shazly
 * @date Last Edit Jun-2020
 *
 */

#ifndef _MAREIX_DEF_H_
#define _MAREIX_DEF_H_

#include <vector>
#include <utility>
#include <sstream>

using std::vector;

template <typename ValueType>
class matrix
{
public:
  /**
     * Initializes a new empty matix.
     * @bigoh O(1)
     */
  matrix();

  /**
     * Initializes a new matrix of (rows x columns) dimensions
     * @bigoh O(rows x columns)
     */
  matrix(int row, int col);

  /**
     * Copy constructor
     * @bigoh O(rows x columns)
     */
  matrix(const matrix<ValueType> &mat);

  /**
     * Move constructor
     * @bigoh O(1)
     */
  matrix(matrix<ValueType> &&mat);

  /**
     * Initializes a new matrix from a given STL vector of vectors
     * @throw length_error if the dimentions are not consistent
     * @bigoh O(rows x columns)
     */
  matrix(const vector<vector<ValueType>> &vec);

  /**
     * Initializes a new matrix from a given STL vector of vectors
     * Destroies the given vector
     * @throw length_error if the dimentions are not consistent
     * @bigoh O(1)
     */
  matrix(vector<vector<ValueType>> &&vec);

  /**
     * Copy assignment constructor
     * @returns Reference to the current object so that it can
     *          be used in further calculations 
     * @bigoh O(rows x columns)
     */
  matrix<ValueType> &operator=(const matrix<ValueType> &mat);

  /**
     * Move assignment constructor
     * @returns Reference to the current object so that it can
     *          be used in further calculations 
     * @bigoh O(1)
     */
  matrix<ValueType> &operator=(matrix<ValueType> &&mat);

  /**
     * Assignment from STL vector of vectors 
     * @returns Reference to the current object so that it can
     *          be used in further calculations 
     * @throw length_error if the dimentions are not consistent
     * @bigoh O(rows x columns)
     */
  matrix<ValueType> &operator=(const vector<vector<ValueType>> &vec);

  /**
     * Assignment from STL vector of vectors 
     * Destroies the given vector
     * @returns Reference to the current object so that it can
     *          be used in further calculations 
     * @throw length_error if the dimentions are not consistent
     * @bigoh O(1)
     */
  matrix<ValueType> &operator=(vector<vector<ValueType>> &&vec);

  /**
     * Compares two matrices for equality.
     * The ValueType must have an == operator.
     * @bigoh O(rows x columns)
     */
  bool operator==(const matrix<ValueType> &mat);

  /**
     * Compares two matrices for inequality.
     * The ValueType must have a != operator.
     * @bigoh O(rows x columns)
     */
  bool operator!=(const matrix<ValueType> &mat);

  /**
     * Overloads <code>+=</code> for addition.
     * Very useful in mathematical operation.
     * The ValueType must have a += operator.
     * @throw   length_error if the dimensions are not the same 
     * @returns Reference to the current object
     * @bigoh   O(rows x columns x additon operation)
     */
  matrix<ValueType> &operator+=(const matrix<ValueType> &mat);

  /**
     * Overloads <code>-=</code> for subtraction.
     * Very useful in mathematical operation.
     * The ValueType must have a -= operator.
     * @throw   length_error if the dimensions are not the same 
     * @returns Reference to the current object
     * @bigoh   O(rows x columns x subtraction operation)
     */
  matrix<ValueType> &operator-=(const matrix<ValueType> &mat);

  /**
     * Overloads <code>*=</code> for scaler multiplication.
     * Very useful in mathematical operation.
     * The ValueType must have a *= operator.
     * @throw   length_error if the dimensions are not the same 
     * @returns Reference to the current object
     * @bigoh   O(rows x columns x multiplication operation)
     */
  matrix<ValueType> &operator*=(const matrix<ValueType> &mat);

  /**
     * Overloads <code>/=</code> for scaler division.
     * Very useful in mathematical operation.
     * The ValueType must have a /= operator.
     * @throw   length_error if the dimensions are not the same 
     * @returns Reference to the current object
     * @bigoh   O(rows x columns x division operation)
     */
  matrix<ValueType> &operator/=(const matrix<ValueType> &mat);

  /**
     * Add every item in the matrix to val.
     * Very useful in mathematical operation.
     * The ValueType must have a += operator.
     * @returns Reference to the current object
     * @bigoh   O(rows x columns x additon operation)
     */
  matrix<ValueType> &operator+=(const ValueType val);

  /**
     * Subtract val from every item in the matrix.
     * Very useful in mathematical operation.
     * The ValueType must have a -= operator.
     * @returns Reference to the current object
     * @bigoh   O(rows x columns x subtraction operation)
     */
  matrix<ValueType> &operator-=(const ValueType val);

  /**
     * Multiply every item in the matrix with val.
     * Very useful in mathematical operation.
     * The ValueType must have a *= operator.
     * @returns Reference to the current object
     * @bigoh   O(rows x columns x multiplication operation)
     */
  matrix<ValueType> &operator*=(const ValueType val);

  /**
     * Divide every item in the matrix on val.
     * Very useful in mathematical operation.
     * The ValueType must have a /= operator.
     * @returns Reference to the current object
     * @bigoh   O(rows x columns x division operation)
     */
  matrix<ValueType> &operator/=(const ValueType val);

  /**
     * Overloads <code>[]</code> to select a row from the matrix.
     * Selecting an element is handled by the STL vector class
     * This extension enables the use of traditional array notation to
     * get or set individual elements.
     * @bigoh O(1)
     */
  vector<ValueType> &operator[](int rowIndex);

  /**
     * Multiply the two matrices
     * @throw   length_error if columns != mat.rows
     * @returns a new matrix results from multiplication
     * @bigoh O(rows x columns x mat.columns)
     */
  matrix<ValueType> multiply(matrix<ValueType> &mat);

  /**
     * Matrix inverse
     * @throw   length_error if columns != rows
     * @throw   out_of_range if determinant = zero
     * @returns a new matrix results from inverting
     */
  matrix<ValueType> invert();

  /**
     * Matrix transpose
     * @throw   length_error if columns != mat.rows
     * @returns a new matrix results from transposing
     * @bigoh O(rows x columns)
     */
  matrix<ValueType> transpose();

  /**
     * Matrix power
     * @throw   length_error if columns != rows
     * @returns a new matrix results from powering
     * @bigoh O(rows^3 x n)
     */
  matrix<ValueType> power(int n);

  /**
     * @returns the Determinant of the given matrix using 
     *          recursive defintion
     * @throw   length_error if it's not a squre matrix
     */
  ValueType det_recursive();

  /**
     * @returns the Determinant of the given matrix using 
     *          Gaussian elimination algoithm
     * @throw   length_error if it's not a squre matrix
     */
  ValueType det();

  /**
     * function used to perform Back Substitution (Gaussian Elimination) 
     * algorithm to solve system of linear equations 
     * 
     * @param   vec constants vector
     * 
     * @returns vector of the results
     */
  vector<ValueType> back_sub(vector<ValueType> vec);

  /**
     * Replace row(index)
     * @throw   out_of_range if index out of range
     * @returns Reference to the current object
     * @bigoh O(columns)
     */
  matrix<ValueType> &replace_row(vector<ValueType> vec, int index);

  /**
     * Replace column(index)
     * @throw   out_of_range if index out of range
     * @returns Reference to the current object
     * @bigoh O(rows)
     */
  matrix<ValueType> &replace_col(vector<ValueType> vec, int index);

  /**
     * Adds a new row to the end of the matrix
     * @throw   length_error if vector size != number of columns
     * @returns Reference to the current object
     * @bigoh O(columns)
     */
  matrix<ValueType> &push_row(const vector<ValueType> &vec);

  /**
     * Adds a new colum to the end of the matrix
     * @throw   length_error if vector size != number of rows
     * @returns Reference to the current object
     * @bigoh O(rows)
     */
  matrix<ValueType> &push_col(vector<ValueType> vec);

  /**
     * @throw   out_of_range if index out of range
     * @returns row(index)
     * @bigoh O(1)
     */
  vector<ValueType> get_row(int index);

  /**
     * @throw   out_of_range if index out of range
     * @returns column(index)
     * @bigoh O(rows)
     */
  vector<ValueType> get_col(int index);

  /**
     * Erases row(index)
     * @throw   out_of_range if index out of range
     * @returns Reference to the current object
     * @bigoh O(columns)
     */
  matrix<ValueType> &erase_row(int index);

  /**
     * Erases column(index)
     * @throw   out_of_range if index out of range
     * @returns Reference to the current object
     * @bigoh O(rows)
     */
  matrix<ValueType> &erase_col(int index);

  /**
     * sawps row1 with row2
     * stable if row1 equals row2
     * @throw   out_of_range if indexes out of range
     * @returns Reference to the current object
     * @bigoh O(rows)
     */
  matrix<ValueType> &swap_rows(int row1, int row2);

  /**
     * sawps column1 with column2
     * stable if column1 equals column2
     * @throw   out_of_range if indexes out of range
     * @returns Reference to the current object
     * @bigoh O(columns)
     */
  matrix<ValueType> &swap_cols(int col1, int col2);

  /**
     * Prints the matrix in the standard format to the standard output
     *   1 1 1 
     *   1 1 1
     *   1 1 1
     * @returns Reference to the current object
     */
  matrix<ValueType> &print_r();

  /**
     * Prints the matrix in the standard format to a given ostream
     *   1 1 1 
     *   1 1 1
     *   1 1 1
     * @returns Reference to the current object
     */
  matrix<ValueType> &print_r(std::ostream &os);

  /**
     * Prints the matrix in format "[1 1; 1 1]" to the standard output
     * @returns Reference to the current object
     */
  matrix<ValueType> &print_l();

  /**
     * Prints the matrix in format "[1 1; 1 1]" to a given ostream
     * @returns Reference to the current object
     */
  matrix<ValueType> &print_l(std::ostream &os);

  /**
     * Resizes the matrix to an new dimenions row x column
     * Doesn't guarantee the matrix data still valid
     * @returns Reference to the new object
     */
  matrix<ValueType> &resize(int row, int col);

  /**
     * @returns the dimensions in pair <rows, columns>
     * @bigoh O(1)
     */
  std::pair<int, int> get_dim();

  /**
     * @returns the number of rows
     * @bigoh O(1)
     */
  int get_rows();

  /**
     * @returns the number of columns
     * @bigoh O(1)
     */
  int get_cols();

  /**************************************************************************
     *************  Static and friend functions and operators  **************
     ************************************************************************/

  /**
     * @static  function can used to check if a certain vector 
     *          can be valid as a matrix.
     * @returns pair<rows, columns> if the matrix is valid
     *          pair<-1, -1> if the matrix is not valid
     * @bigoh   O(rows x columns)
     */
  static std::pair<int, int> check_dim(const vector<vector<ValueType>> &vec);

  /**
     * Overloads <code>+</code> for addition.
     * Very useful in mathematical operation.
     * The ValueType must have a += operator.
     * @throw   length_error if the dimensions are not the same 
     * @returns a new matrix results from additon
     * @bigoh   O(rows x columns x additon operation)
     */
  template <typename T>
  friend matrix<T> operator+(matrix<T> m1, const matrix<T> &m2);

  /**
     * Overloads <code>-</code> for subtraction.
     * Very useful in mathematical operation.
     * The ValueType must have a -= operator.
     * @throw   length_error if the dimensions are not the same 
     * @returns a new matrix results from subtraction
     * @bigoh   O(rows x columns x subtraction operation)
     */
  template <typename T>
  friend matrix<T> operator-(matrix<T> m1, const matrix<T> &m2);

  /**
     * Overloads <code>*</code> for scaler multiplication.
     * Very useful in mathematical operation.
     * The ValueType must have a *= operator.
     * @throw   length_error if the dimensions are not the same 
     * @returns a new matrix results from multiplication
     * @bigoh   O(rows x columns x multiplication operation)
     */
  template <typename T>
  friend matrix<T> operator*(matrix<T> m1, const matrix<T> &m2);

  /**
     * Overloads <code>/</code> for scaler division.
     * Very useful in mathematical operation.
     * The ValueType must have a /= operator.
     * @throw   length_error if the dimensions are not the same 
     * @returns a new matrix results from division
     * @bigoh   O(rows x columns x division operation)
     */
  template <typename T>
  friend matrix<T> operator/(matrix<T> m1, const matrix<T> &m2);

  /**
     * Add every item in the matrix to val.
     * Very useful in mathematical operation.
     * The ValueType must have a += operator.
     * @returns a new matrix results from additon
     * @bigoh   O(rows x columns x additon operation)
     */
  template <typename T>
  friend matrix<T> operator+(matrix<T> m1, const T val);

  /**
     * Subtract val from every item in the matrix.
     * Very useful in mathematical operation.
     * The ValueType must have a -= operator.
     * @returns a new matrix results from subtraction
     * @bigoh   O(rows x columns x subtraction operation)
     */
  template <typename T>
  friend matrix<T> operator-(matrix<T> m1, const T val);

  /**
     * Multiply every item in the matrix with val.
     * Very useful in mathematical operation.
     * The ValueType must have a *= operator.
     * @returns a new matrix results from multiplication
     * @bigoh   O(rows x columns x multiplication operation)
     */
  template <typename T>
  friend matrix<T> operator*(matrix<T> m1, const T val);

  /**
     * Divide every item in the matrix on val.
     * Very useful in mathematical operation.
     * The ValueType must have a /= operator.
     * @returns a new matrix results from division
     * @bigoh   O(rows x columns x division operation)
     */
  template <typename T>
  friend matrix<T> operator/(matrix<T> m1, const T val);

  /**
     * Overloads << operator to print the matrix in the standard format
     * as a native type.
     */
  template <typename T>
  friend std::ostream &operator<<(std::ostream &os, const matrix<T> &mat);

  /**
     * @returns the Determinant of the given matrix using 
     *          recursive defintion
     * @throw   length_error if it's not a squre matrix
     */
  template <typename T>
  friend T determinant_recursive(matrix<T> mat);

  /**
     * @returns the Determinant of the given matrix using 
     *          Gaussian elimination algoithm
     * @throw   length_error if it's not a squre matrix
     */
  template <typename T>
  friend T determinant(matrix<T> mat);

  /**
     * @helper  function used to get submatrices used in determinant 
     *          calculations.
     * @returns matrix with dimensions <rows-1, columns-1>
     *          the specified row and col are erasrd
     */
  template <typename T>
  friend matrix<T> sub_matrix(matrix<T> mat, int row, int col);

  /**
     * function used to perform Back Substitution (Gaussian Elimination) 
     * algorithm to solve system of linear equations 
     * 
     * @param   mat coefficient matrix
     * @param   vec constants vector
     * 
     * @returns vector of the results
     */
  template <typename T>
  friend vector<T> back_substitution(matrix<T> mat, vector<T> vec);

private:
  int rows;
  int cols;
  vector<vector<ValueType>> elements;
};

#endif
