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
    linear_equations();
    linear_equations(const linear_equations &lin_equ);
    linear_equations(linear_equations &&lin_equ);

    uint32_t size();
    uint32_t num_of_vars();
    uint32_t get_term_poision(const string &term_str);
    equation<value_t> get_by_index(uint32_t index);

    matrix<value_t> get_const_matrix();
    matrix<value_t> get_term_matrix(const string &term_str);

    vector<value_t> get_const_coffs();
    vector<value_t> get_term_coffs(const string &term_str);

    value_t const_det();
    value_t term_det(const string &term_str);

    linear_equations &insert(const string &equ_str);
    linear_equations &reomve(uint32_t index);
    map<string, value_t> solve_cramer();
    map<string, value_t> solve_back_sub();

private:
    set<string> vars;
    vector<equation<value_t>> equations;

    /**
     * for efficency with reapted tasks
     */
    bool updated;
    vector<value_t> const_coffs;
    matrix<value_t> const_matrix;

    linear_equations &__init__();
};

// include implemention
#include "linear_equations_impl.h"

#endif // End of the file
