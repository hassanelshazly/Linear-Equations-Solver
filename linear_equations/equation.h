#ifndef _EQUATION_H_
#define _EQUATION_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "term.h"

using std::set;
using std::string;
using std::vector;

template <typename value_t>
class equation
{
public:
    equation();
    equation(const equation &equ);
    equation(const string &equ_str);

    uint32_t size();

    value_t get(const string &var);
    value_t get_const();
    set<string> get_vars();
    set<term<value_t>> get_terms();

    equation &set_term(const string &var, value_t val);
    equation &set_const(value_t val);
    equation &add_const(value_t val);
    equation &subtract_const(value_t val);
    equation &add_term(term<value_t> tm);
    equation &subtract_term(term<value_t> tm);
    equation &subtract_term(const string &var, value_t val);
    equation &add_term(const string &var, value_t val);

    equation &remove_term(const string &var);

    equation &sub_term(const string &var, value_t val);

    equation &add(const equation &equ);
    equation &subtract(const equation &equ);
    equation &multiply(value_t val);
    equation &divide(value_t val);

    equation &operator+=(const equation &equ);
    equation &operator-=(const equation &equ);
    equation &operator*=(value_t val);
    equation &operator/=(value_t val);

    template <typename T>
    friend equation<T> &operator+(const equation<T> &equ1, const equation<T> &equ2);

    template <typename T>
    friend equation<T> &operator-(const equation<T> &equ1, const equation<T> &equ2);

    template <typename T>
    friend equation<T> &operator*(const equation<T> &equ, value_t val);

    template <typename T>
    friend equation<T> &operator/(const equation<T> &equ, value_t val);

    /**
     * Overloads << operator to print equation as a native type.
     */
    template <typename T>
    friend std::ostream &operator<<(std::ostream &os, const equation<T> &equ);

private:
    set<term<value_t>> terms;
    value_t constant;

    equation convert(const string &equ_str);
    equation evaluate(const string &equ_str, int sign);
    vector<string> get_tokens(string to_match, const string &pattern);
};

// include implemention
#include "equation_impl.h"

#endif // End of the file
