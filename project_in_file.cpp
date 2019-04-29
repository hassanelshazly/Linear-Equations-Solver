/* start matrix.h file*/

#ifndef _MAREIX_H_
#define _MAREIX_H_

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <sstream>

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


    matrix<ValueType>& print_r();
    matrix<ValueType>& print_r(std::ostream& os);
    matrix<ValueType>& print_l(); // matlab format
    matrix<ValueType>& print_l(std::ostream& os);

    matrix<ValueType>& resize(int row, int col); // This doesn't guarantee the matrix data still valid
    std::pair<int, int> getDim();
    int getR();
    int getC();
    static std::pair<int, int> check_dim(const vector<vector<ValueType>>& vec);

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
    std::pair<int, int> p = check_dim(vec);
    if(p.first < 0)
        throw std::length_error("Dimentions error");
    rows = p.first;
    cols = p.second;
    elements = vec ;
}

template <typename ValueType>
matrix<ValueType>::matrix(vector<vector<ValueType>>&& vec)
{
    std::pair<int, int> p = check_dim(vec);
    if(p.first < 0)
        throw std::length_error("Dimentions error");
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
    std::pair<int, int> p = check_dim(vec);
    if(p.first < 0)
        throw std::length_error("Dimentions error");
    rows = p.first;
    cols = p.second;
    elements = vec ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator=(vector<vector<ValueType>>&& vec)
{
    std::pair<int, int> p = check_dim(vec);
    if(p.first < 0)
        throw std::length_error("Dimentions error");
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
inline std::pair<int, int> matrix<ValueType>::getDim()
{
    return std::make_pair(rows, cols);
}

template <typename ValueType>
inline int matrix<ValueType>::getR()
{
    return rows;
}

template <typename ValueType>
inline int matrix<ValueType>::getC()
{
    return cols;
}



template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator+=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("Error: Matrices dimentions must be the same") ;
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
        throw std::length_error("Error: Matrices dimentions must be the same") ;
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
        throw std::length_error("Error: Matrices dimentions must be the same") ;
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
        throw std::length_error("Error: Matrices dimentions must be the same") ;
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
        throw std::length_error("Error: check matrices dimentions");
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
        throw std::length_error("Error: check matrix dimentions");
    matrix<ValueType> res = *this;
    for(int i = 0; i < n-1; i++)
        res = res.multiply(*this);
    return res;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::invert()
{
    if(rows != cols)
        throw std::length_error("Error: check matrix dimentions");
    matrix<ValueType> adj (rows, cols);
    ValueType signRow = 1 ;
    ValueType signCol = signRow ;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            adj[i][j] = determinant(subMatrix(*this, i, j)) * signCol;
            signCol = -signCol;
        }
        signRow = -signRow;
        signCol = signRow;
    }
    ValueType det = determinant(*this);
    if(det == static_cast<ValueType>(0))
        throw std::out_of_range("Error: Determinant equal zero");
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
std::pair<int, int> matrix<ValueType>::check_dim(const vector<vector<ValueType>>& vec)
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
        throw std::out_of_range("out of range");
    elements[index] = vec;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::replace_col(vector<ValueType> vec, int index)
{
    if(index < 0 || index >= cols)
        throw std::out_of_range("out of range");
    int i = 0;
    for(auto& row : elements)
        row[index] = vec[i++];
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::push_row(vector<ValueType> vec)
{
    if(vec.size() != cols)
        throw std::length_error("Dimentions must be the same");
    elements.push_back(vec);
    rows++;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::push_col(vector<ValueType> vec)
{
    if(vec.size() != rows)
        throw std::length_error("Dimentions must be the same");
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
        throw std::out_of_range("out of range");
    return elements[index];
}

template <typename ValueType>
vector<ValueType> matrix<ValueType>::get_col(int index)
{
    if(index < 0 || index >= cols)
        throw std::out_of_range("out of range");
    vector<ValueType> vec(rows);
    for(const auto& row : elements)
        vec.push_back(row[index]);
    return vec;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::erase_row(int index)
{
    if(index < 0 || index >= rows)
        throw std::out_of_range("out of range");
    elements.erase(elements.begin()+index);
    rows--;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::erase_col(int index)
{
    if(index < 0 || index >= cols)
        throw std::out_of_range("out of range");
    for(auto& row : elements)
        row.erase(row.begin()+index);
    cols--;
    return *this;
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
matrix<ValueType> subMatrix(matrix<ValueType> m, int row, int col)
{
    for(int i = 0; i<m.getR(); i++)
        m[i].erase(m[i].begin() + col);
    m.elements.erase(m.elements.begin() + row);
    return matrix<ValueType>(m.elements);
}

template <typename ValueType>
ValueType determinant(matrix<ValueType> m)
{
    if(m.getR() != m.getC())
        throw std::length_error("Error: check matrix dimentions");
    if(m.getR() == 1) return m[0][0] ;
    ValueType det = ValueType();
    ValueType sign = 1 ;
    for(int i = 0; i<m.getC(); i++)
    {
        det += m[0][i] * determinant(subMatrix(m, 0, i)) * sign;
        sign = -sign ;
    }
    return det;
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
/* end matrix.h file */

/* start linear_equs.h file */

/**
 * Now, the input can be in any format and the variables can be in any format with some restrictions
 * no parentesis are allowed
 * no spaces are allowed
 * no special characters are allowed including * / ^ % except '_' undersore
 * variables can't start with a number & can't contain any special characters
 * to solve the system or to get any carmer coff, the number of variables must be euaql to the number of equs
 * ex. for vaild equtions
 *      "2x1+3x2+4x4=16"             -> "2x1+3x2+4x4=16"
 *      "4+x4-3+x1+x2-5x4-3x4=7+7-7" -> "1x1+1x2-7x4=6"
 *      "_x3-_7y+-4=_7y+5"           -> "-2_7y+1_x3=9"
 *      "5x+4y-9=7x-4y"              -> "-2x+8y=9"
 * ex. for non vaild equtions
 *      "2x1+3x2+4x4"
 *      "_x3-_7y+-4="
 *      "5x + 4y- 9= 7x-4y"
 *      "x@y3-7/y+-4=7"
 *      "(xy3)-7y+-4=7*3"
 */

#ifndef _LINEAR_EQUS_H_
#define _LINEAR_EQUS_H_

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <map>
//#include "matrix.h"

using std::vector;
using std::string;
using std::map;

template <typename ValueType>
class linear_equs
{
public:
    linear_equs();

    linear_equs<ValueType>& push_equ(string str) noexcept;
    string get_equ(size_t index) const;

    vector<ValueType> get_var_coffs(const string var) noexcept;
    size_t get_num_of_vars() const noexcept;

    string add_equs(size_t equ1, size_t equ2) ;
    string subtract_equs(size_t equ1, size_t equ2) ;
    string substitute_equs(string var, size_t equ1, size_t equ2) ;
    matrix<ValueType> get_coffs_mat() const noexcept;

    ValueType get_coffs_det() const noexcept;
    matrix<ValueType> get_var_mat(string var) const;
    ValueType get_var_det(string var) const;
    map<string, ValueType> solve() const;

private:
    size_t num_of_vars;
    size_t num_of_equs;
    std::set<string> vars;

    vector<ValueType> sols;
    matrix<ValueType> coffs;
    vector<map<string, ValueType>> equs;

    ValueType cast_val(string str);
    ValueType evaluate(string str);
    string factor(string str);
    linear_equs<ValueType>& init_coffs();
    map<string, ValueType> init_equ(string str);
    linear_equs<ValueType>& make_equ(map<string, ValueType> equ);
    string convert(map<string, ValueType> equ) const noexcept;

    map<string, ValueType> init_apart(string& str, map<string, ValueType>& m, vector<string>& used, bool right);
};

template <typename ValueType>
ValueType linear_equs<ValueType>::cast_val(string str)
{
    std::istringstream is (str);
    ValueType val;
    is >> val;
    return val;
}

template <typename ValueType>
string linear_equs<ValueType>::factor(string str)
{
    vector<string> exp;
    if(str == "" || str == "+" || str == "-") return str;
    int j = 0;
    for(int i=0; i < str.length(); i++)
        if(str[i] == '+' or str[i] == '-')
        {
            if(str.substr(j,i-j) != "") exp.push_back(str.substr(j,i-j));
            j=i;
        }
    if(str.substr(j,str.length()-j) != "") exp.push_back(str.substr(j,str.length()-j));
    return exp[exp.size()-1];
}

template <typename ValueType>
ValueType linear_equs<ValueType>::evaluate(string str)
{
    vector<string> exp;
    int j = 0;
    for(int i=0; i < str.length(); i++)
        if(str[i] == '+' or str[i] == '-')
        {
            exp.push_back(str.substr(j,i-j));
            j=i;
        }
    exp.push_back(str.substr(j,str.length()-j));
    ValueType result = ValueType();
    for(auto& val : exp)
        result += cast_val(val);
    return result;
}

template <typename ValueType>
map<string, ValueType> linear_equs<ValueType>::init_apart(string& str, map<string, ValueType>& m, vector<string>& used, bool right)
{
    int index = 0;
    for(int i = 0; i < str.length(); i++)
    {
        if(isalpha(str[i]) || str[i] == '_')
        {
            string val = str.substr(index, i-index);
            int index_key = i+1;
            while(str[index_key] != '+' && str[index_key] != '-' && index_key < str.length())
                index_key++;
            string key = str.substr(i,index_key-i);
            index = index_key;
            val = factor(val);
            ValueType tmp = cast_val(val);
            if(val == "" or val == "+") tmp = static_cast<ValueType>(1);
            if(val == "-") tmp = static_cast<ValueType>(-1);
            if(m.find(key) != m.end())
                if(right) m[key] += tmp;
                else m[key] -= tmp;
            else
                if(right) m[key] = tmp;
                else m[key] = -tmp;
            used.push_back(val+key);
            i += key.length()-1;
        }
        if(str[i] == '=')
            throw std::out_of_range("parse error: mutipule \"=\"");
    }
    return m;
}

template <typename ValueType>
map<string, ValueType> linear_equs<ValueType>::init_equ(string str)
{
    map<string, ValueType> m;
    vector<string> used;
    for(int i = 0; i < str.length(); i++)
        if(str[i] == '=')
        {
        string right = str.substr(0, i);
        init_apart(right, m, used, true);
        for(const string& s : used)
            right.erase(right.find(s), s.length());
        if(right != "")
        m["="] = -evaluate(right);
        used.clear();
        string left = str.substr(i+1);
        init_apart(left, m, used, false);
        for(const string& s : used)
            left.erase(left.find(s), s.length());
        if(left != "")
            m["="] += evaluate(left);
        }
    for(const auto& item : m)
        if(item.first != "=")
            vars.insert(item.first);
    equs.push_back(m);
    return m;
}

template <typename ValueType>
linear_equs<ValueType>& linear_equs<ValueType>::init_coffs()
{
    coffs.resize(num_of_equs, num_of_vars);
    int i = 0, j = 0;
    for(const auto& equ : equs)
    {
        for(const auto& item : equ)
            if(item.first != "=")
                coffs[i][j++] = item.second;
        j = 0; i++;
    }
}

template <typename ValueType>
linear_equs<ValueType>& linear_equs<ValueType>::make_equ(map<string, ValueType> equ)
{
    /* vaild for any variables names
     * must call init_coffs() before any operation on coffs */
    sols.push_back(equ["="]);
    num_of_vars = vars.size();
    num_of_equs++;
    for(auto& item : equs)
        for(const auto& var : vars)
            if(item.find(var) == item.end())
                item[var] = ValueType();
    init_coffs();
    return *this;
    /* vaild for x{number} only */

    // sols.push_back(equ["="]);
    // auto it = equ.begin();
    // std::advance(it, equ.size()-1);
    // int vars = atoi(it->first.substr(1).c_str());
    // if(vars > num_of_vars)
    // {
    //     num_of_vars = vars;
    //     coffs.resize(coffs.getR(), num_of_vars);
    // }
    // vector<ValueType> vec(num_of_vars);
    // for(int i=0; i<vec.size(); i++)
    // {
    //     std::ostringstream os;
    //     os << "x" << i+1 ;
    //     string var_name = os.str();
    //     if(equ.find(var_name) != equ.end())
    //         vec[i] = equ[var_name];
    //     else
    //         vec[i] = ValueType();
    // }
    // coffs.push_row(vec);
    // num_of_equs++;
    // return vec;
}

template <typename ValueType>
string linear_equs<ValueType>::convert(map<string, ValueType> equ) const noexcept
{
    std::ostringstream os ;
    for(const auto& item : equ)
        if(item.first == "=" || item.second == 0)
            continue;
        else
            if(item.second > 0)
                os << "+" << item.second << item.first ;
            else if(item.second < 0)
                os << item.second << item.first ;
    os << "=" << equ["="];
    string s = os.str();
    if(s[0] == '+') s.erase(0,1);
    return s;
}

template <typename ValueType>
linear_equs<ValueType>::linear_equs()
    : num_of_vars(0), num_of_equs(0), coffs(matrix<ValueType>()), sols(vector<ValueType>()) {}

template <typename ValueType>
linear_equs<ValueType>& linear_equs<ValueType>::push_equ(string str) noexcept
{
    make_equ(init_equ(str));
    return *this;
}

template <typename ValueType>
string linear_equs<ValueType>::get_equ(size_t index) const
{
    return convert(equs[index]);
}

template <typename ValueType>
vector<ValueType> linear_equs<ValueType>::get_var_coffs(const string var) noexcept
{
    vector<ValueType> vec;
    for(auto& item : equs)
        if(item.find(var) != item.end())
            vec.push_back(item[var]);
        else
            vec.push_back(ValueType());
    return vec;
}

template <typename ValueType>
size_t linear_equs<ValueType>::get_num_of_vars() const noexcept
{
    return num_of_vars;
}

template <typename ValueType>
string linear_equs<ValueType>::add_equs(size_t equ1, size_t equ2)
{
    vector<ValueType> v1 = coffs.get_row(equ1);
    vector<ValueType> v2 = coffs.get_row(equ2);
    vector<ValueType> res(v1.size());
    vector<string> var_names ;
    std::copy(vars.begin(), vars.end(), std::back_inserter(var_names));
    map<string, ValueType> res_map;
    for(int i = 0; i < v1.size(); i++)
        res[i] = v1[i] + v2[i];
    for(int i = 0; i < res.size(); i++)
        res_map.insert(std::make_pair(var_names[i], res[i]));
    res_map.insert(std::make_pair("=", sols[equ1] + sols[equ2]));
    return convert(res_map);
}

template <typename ValueType>
string linear_equs<ValueType>::subtract_equs(size_t equ1, size_t equ2)
{
    vector<ValueType> v1 = coffs.get_row(equ1);
    vector<ValueType> v2 = coffs.get_row(equ2);
    vector<ValueType> res(v1.size());
    vector<string> var_names ;
    std::copy(vars.begin(), vars.end(), std::back_inserter(var_names));
    map<string, ValueType> res_map;
    for(int i = 0; i < v1.size(); i++)
        res[i] = v1[i] - v2[i];
    for(int i = 0; i < res.size(); i++)
        res_map.insert(std::make_pair(var_names[i], res[i]));
    res_map.insert(std::make_pair("=", sols[equ1] - sols[equ2]));
    return convert(res_map);
}

template <typename ValueType>
string linear_equs<ValueType>::substitute_equs(string var, size_t equ1, size_t equ2)
{
    vector<ValueType> v1 = coffs.get_row(equ1);
    vector<ValueType> v2 = coffs.get_row(equ2);
    ValueType coff1 = equs[equ1][var];
    ValueType coff2 = equs[equ2][var];
    ValueType sol1 = sols[equ1] ;
    ValueType sol2 = sols[equ2] ;
    map<string, ValueType> res_map;

    for(auto& item : v2)
        item *= (coff1 / coff2 );
    sol2 *= (coff1 / coff2 );
    if((coff1 > 0 && coff2 > 0) || (coff1 < 0 && coff2 < 0))
    {
        for(int i = 0; i < v1.size(); i++)
            v1[i] -= v2[i];
        sol1 -= sol2;
    }
    else
    {
        for(int i = 0; i < v1.size(); i++)
            v1[i] += v2[i];
        sol1 += sol2;
    }
    vector<string> var_names ;
    std::copy(vars.begin(), vars.end(), std::back_inserter(var_names));
    for(int i = 0; i < v1.size(); i++)
        res_map.insert(std::make_pair(var_names[i], v1[i]));
    res_map.insert(std::make_pair("=", sol1));
    return convert(res_map);
}

template <typename ValueType>
matrix<ValueType> linear_equs<ValueType>::get_coffs_mat() const noexcept
{
    return coffs ;
}

template <typename ValueType>
ValueType linear_equs<ValueType>::get_coffs_det() const noexcept
{
    return determinant(coffs) ;
}

template <typename ValueType>
matrix<ValueType> linear_equs<ValueType>::get_var_mat(string var) const
{
    matrix<ValueType> mat = coffs;
    vector<string> var_names ;
    std::copy(vars.begin(), vars.end(), std::back_inserter(var_names));
    int index = std::find(var_names.begin(), var_names.end(), var) - var_names.begin();
    mat.replace_col(sols, index);
    return mat;
}

template <typename ValueType>
ValueType linear_equs<ValueType>::get_var_det(string var) const
{
    return determinant(get_var_mat(var));
}

template <typename ValueType>
map<string, ValueType> linear_equs<ValueType>::solve() const
{
    map<string, ValueType> solution;
    ValueType d_val = get_coffs_det();
    for(const string& var : vars)
    {
        ValueType var_val = get_var_det(var);
        solution.insert(std::make_pair(var, var_val/d_val));
    }
    return solution;
}

#endif
/* end linear_equs.h file */

/* start main.cpp file */

#include <iostream>
#include <string>
// #include <time.h>
// #include "../linear equations/linear_equs.h"
// #include "../Matrix/matrix.h"

using namespace std;

string remove_spaces(string str)
{
    for(int i = 0; i < str.length(); i++)
        if(str[i] == ' ')
            str.erase(i,1);
    return str;
}

int main()
{
    try
    {
        linear_equs<float> ln;
        int n; cin >> n;
        cin.ignore(1000,'\n');
        string str;
        for(int i = 0; i < n; i++)
        {
            getline(cin, str);
            ln.push_equ(remove_spaces(str));
        }
        cin >> str ;
        if(str == "num_vars")
        {
            cout << ln.get_num_of_vars();
        }
        else if(str == "equation")
        {
            cin >> n;
            cout << ln.get_equ(n-1);
        }
        else if(str == "column")
        {
            cin >> str;
            vector<float> vec = ln.get_var_coffs(str);
            for(const auto& item : vec)
                cout << item << endl;
        }
        else if(str == "add")
        {
            int i, j; cin >> i >> j;
            cout << ln.add_equs(i-1, j-1);
        }
        else if(str == "subtract")
        {
            int i, j; cin >> i >> j;
            cout << ln.subtract_equs(i-1, j-1);
        }
        else if(str == "substitute")
        {
            int i, j; cin >> str >> i >> j;
            cout << ln.substitute_equs(str, i-1, j-1);
        }
        else if(str == "D")
        {
            cin.unget();
            getline(cin, str);
            if(str == "D")
                cout << ln.get_coffs_mat();
            else
                cout << ln.get_var_mat(str.substr(2));
        }
        else if(str == "D_value")
        {
            cout << ln.get_coffs_det();
        }
        else if(str == "solve")
        {
            map<string, float> m = ln.solve();
            for(const auto& item : m)
                cout << item.first << "=" << item.second << endl;
        }
    }
    catch(const std::exception& e)
    {
        cout << e.what() << '\n';
    }
    catch(...)
    {
        cout << "Exception ocuured\n";
    }
}
/* end main.cpp file */
