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


#ifndef _LINEAR_EQUATIONS_H_
#define _LINEAR_EQUATIONS_H_

#include <iostream>
#include <vector>
#include <set>

#include "matrix.h"
#include "equation.h"

using std::map;
using std::vector;

template <typename value_t>
class linear_equations
{
public:

    /**
     * Default constructor
     */
    linear_equations();

    /**
     * Copy constructor
     */
    linear_equations(const linear_equations &lin_equ);

     /**
     * Move constructor
     */
    linear_equations(linear_equations &&lin_equ);

    /**
     * @return number of equations
     */
    uint32_t size();

    /**
     * @return total number of variables 
     */
    uint32_t num_of_vars();

    /**
     * insert new equation to the system
     * @return reference to the calling object
     */
    linear_equations &insert(const string &equ_str);

    /**
     * remove equation by index
     * @return reference to the calling object
     */
    linear_equations &reomve(uint32_t index);

    /**
     * solve the system using cramer method
     * @return map of every variable with it's value
     */
    map<string, value_t> solve_cramer();

    /**
     * solve the system using Gaussian elimination method
     * @return map of every variable with it's value
     */
    map<string, value_t> solve_back_sub();

    /**
     * @return the position of the variable relative to 
     *         all the varibles in the system
     */ 
    uint32_t get_term_position(const string &term_str);

    /**
     * @return the equation in specific index
     */
    equation<value_t> get_by_index(uint32_t index);

    /**
     * @return matrix of all coffs of variables
     */
    matrix<value_t> get_const_matrix();
    
    /**
     * @return matrix of all coffs of variables except term_str
     *         substituted with consts column
     */
    matrix<value_t> get_term_matrix(const string &term_str);

    /**
     * @return vector with the consts of all equations
     */
    vector<value_t> get_const_coffs();

    /**
     * @return vector with the coffs of term_str
     */
    vector<value_t> get_term_coffs(const string &term_str);

    /**
     * @return the determinant of the coffs matrix
     */
    value_t const_det();

    /**
     * @return the determinant of the term_str matrix
     */
    value_t term_det(const string &term_str);

private:
    set<string> vars;
    vector<equation<value_t>> equations;

    /**
     * for efficency with reapted tasks
     */
    bool updated; // holds the state of the object
    vector<value_t> const_coffs;
    matrix<value_t> const_matrix;

    linear_equations &__init__();
};

// include implemention
#include "linear_equations_impl.h"

#endif // End of the file
