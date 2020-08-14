/******************************************************************************
 * Copyright (C) 2020 by Hassan El-shazly
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright.
 *
 *****************************************************************************/
/**
 *
 * @author Hassan El-shazly
 * @date Last Edit Aug-2020
 *
 */

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
    /**
     * Default constructor
     */
    equation();

    /**
     * Copy constructor
     */
    equation(const equation &equ);

    /**
     * Move constructor
     */
    equation(const equation &&equ);

    /**
     * Construct equation from string
     */
    equation(const string &equ_str);

    /**
     * @return number of terms
     */
    uint32_t size();

    /**
     * @return the coff of specifec variable
     */
    value_t get(const string &var);

    /**
     * @return the constant term
     */
    value_t get_const();
    
    /**
     * @return set with varible names
     */
    set<string> get_vars();
    
    /**
     * @return terms of the equation
     */
    set<term<value_t>> get_terms();

    /**
     * change the value of specifec term
     * @return reference to the calling object
     */
    equation &set_term(const string &var, value_t val);

    /**
     * change the value of the constant
     * @return reference to the calling object
     */
    equation &set_const(value_t val);
    
    /**
     * add value to the const term
     * @return reference to the calling object
     */
    equation &add_const(value_t val);
    
    /**
     * subtract value from the const term
     * @return reference to the calling object
     */
    equation &subtract_const(value_t val);
    
    /**
     * add term to the equation
     * @return reference to the calling object
     */
    equation &add_term(term<value_t> tm);

    /**
     * add term to the equation
     * @return reference to the calling object
     */
    equation &add_term(const string &var, value_t val);
    
    /**
     * subtract term from the equation
     * @return reference to the calling object
     */
    equation &subtract_term(term<value_t> tm);

    /**
     * subtract term from the equation
     * @return reference to the calling object
     */
    equation &subtract_term(const string &var, value_t val);
    
    /**
     * remove term from the equation
     * @return reference to the calling object
     */
    equation &remove_term(const string &var);

    /**
     * subsutuite varible with specfic value
     * @return reference to the calling object
     */
    equation &sub_term(const string &var, value_t val);

    /**
     * add two equations
     * @return reference to the calling object
     */
    equation &add(const equation &equ);

     /**
     * subtract two equations
     * @return reference to the calling object
     */
    equation &subtract(const equation &equ);

     /**
     * multiply all the terms of the equation with val
     * @return reference to the calling object
     */
    equation &multiply(value_t val);

    /**
     * divide all the terms of the equation on val
     * @return reference to the calling object
     */
    equation &divide(value_t val);

    /**
     * add two equations
     * @return reference to the calling object
     */
    equation &operator+=(const equation &equ);

    /**
     * subtract two equations
     * @return reference to the calling object
     */
    equation &operator-=(const equation &equ);

    /**
     * multiply all the terms of the equation with val
     * @return reference to the calling object
     */
    equation &operator*=(value_t val);

    /**
     * divide all the terms of the equation on val
     * @return reference to the calling object
     */
    equation &operator/=(value_t val);

    /**
     * add two equations
     * @return new equation object
     */    
    template <typename T>
    friend equation<T> &operator+(const equation<T> &equ1, const equation<T> &equ2);

    /**
     * subtract two equations
     * @return new equation object
     */
    template <typename T>
    friend equation<T> &operator-(const equation<T> &equ1, const equation<T> &equ2);

    /**
     * multiply all the terms of the equation with val
     * @return new equation object
     */
    template <typename T>
    friend equation<T> &operator*(const equation<T> &equ, value_t val);

     /**
     * divide all the terms of the equation on val
     * @return new equation object
     */
    template <typename T>
    friend equation<T> &operator/(const equation<T> &equ, value_t val);

    /**
     * Overloads << operator to print equation as a native type.
     */
    template <typename T>
    friend std::ostream &operator<<(std::ostream &os, const equation<T> &equ);

private:
    /**
     * convert string to an equation
     */
    equation convert(const string &equ_str);
    
    /**
     * convert string to an equation
     */
    equation evaluate(const string &equ_str, int sign);
    
    /**
     * @return vector of matched strings with regex
     */
    vector<string> get_tokens(string to_match, const string &pattern);

    set<term<value_t>> terms;
    value_t constant;
};

// include implemention
#include "equation_impl.h"

#endif // End of the file
