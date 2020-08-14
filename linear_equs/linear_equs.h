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

#ifndef _LINEAR_EQUS_H_
#define _LINEAR_EQUS_H_

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <map>

#include "matrix.h"

using std::map;
using std::string;
using std::vector;

template <typename ValueType>
class linear_equs
{
public:
    /**
     * Default constructor
     */
    linear_equs();

    /**
     * insert new equation to the system
     * @return reference to the calling object
     */
    linear_equs<ValueType> &push_equ(string str);

    /**
     * @return the equation in specific index
     */
    string get_equ(size_t index);

    /**
     * @return vector with the coffs of var
     */
    vector<ValueType> get_var_coffs(const string var);

    /**
     * @return total number of variables 
     */
    size_t get_num_of_vars();

    /**
     * add equations of indexes equ1 & equ2
     * @return the resulting equation on string format 
     */
    string add_equs(size_t equ1, size_t equ2);

    /**
     * subtract equation[equ1] from equation[equ2]
     * @return the resulting equation on string format
     */
    string subtract_equs(size_t equ1, size_t equ2);

    /**
     * Substitutes the variable var in equ1 by its equation in equ2
     * @return the resulting equation on string format
     */
    string substitute_equs(string var, size_t equ1, size_t equ2);

    /**
     * @return matrix of all coffs of variables
     */
    matrix<ValueType> get_coffs_mat();

    /**
     * @return the determinant of the coffs matrix
     */
    ValueType get_coffs_det();

    /**
     * @return matrix of all coffs of variables except term_str
     *         substituted with consts column
     */
    matrix<ValueType> get_var_mat(string var);

    /**
     * @return the determinant of the term_str matrix
     */
    ValueType get_var_det(string var);

    /**
     * solve the system using cramer method
     * @return map of every variable with it's value
     */
    map<string, ValueType> solve_by_cramer_method();

    /**
     * solve the system using Gaussian elimination method
     * @return map of every variable with it's value
     */
    map<string, ValueType> solve_by_backSub();

private:
    bool init_flag;
    size_t num_of_equs;
    std::set<string> vars;

    vector<ValueType> sols;
    matrix<ValueType> coffs;
    vector<map<string, ValueType>> equs;

    ValueType cast_val(string str);
    ValueType evaluate(string str);
    string factor(string str);
    linear_equs<ValueType> &init_coffs();
    map<string, ValueType> init_equ(string str);
    string convert(map<string, ValueType> equ);
    map<string, ValueType> init_apart(string &str,
                                      map<string, ValueType> &m, vector<string> &used, bool right);
};

// include implemention
#include "linear_equs_impl.h"

#endif // End of the file
       // 11300
       // 610800