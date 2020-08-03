#ifndef _LINEAR_EQUATIONS_IMPL_H_
#define _LINEAR_EQUATIONS_IMPL_H_

template <typename value_t>
linear_equations<value_t>::linear_equations()
    : vars(), equations(), updated(false),
      const_coffs(), const_matrix()
{
    // do nothing
}

template <typename value_t>
linear_equations<value_t>::linear_equations(const linear_equations &lin_equ)
    : vars(lin_equ.vars), equations(lin_equ.equations),
      updated(lin_equ.updated), const_coffs(lin_equ.const_coffs),
      const_matrix(lin_equ.const_matrix)
{
    // do nothing
}

template <typename value_t>
linear_equations<value_t>::linear_equations(linear_equations &&lin_equ)
    : vars(move(lin_equ.vars)), equations(move(lin_equ.equations)),
      updated(move(lin_equ.updated)), const_coffs(move(lin_equ.const_coffs)),
      const_matrix(move(lin_equ.const_matrix))
{
    // do nothing
}

template <typename value_t>
linear_equations<value_t> &linear_equations<value_t>::__init__()
{
    if (updated)
        return *this;
    const_matrix.resize(equations.size(), vars.size());
    const_coffs.resize(equations.size());
    uint32_t i = 0, j;
    for (const auto &equation : equations)
    {
        j = 0;
        for (const auto &var : vars)
            const_matrix[i][j++] = equation.get(var);
        const_coffs[i] = equation.get_const();
        i++;
    }
    updated = true;
    return *this;
}

template <typename value_t>
uint32_t linear_equations<value_t>::size()
{
    return equations.size();
}

template <typename value_t>
uint32_t linear_equations<value_t>::num_of_vars()
{
    return vars.size();
}

template <typename value_t>
equation<value_t> linear_equations<value_t>::get_by_index(uint32_t index)
{
    return equations[index];
}

template <typename value_t>
matrix<value_t> linear_equations<value_t>::get_const_matrix()
{
    __init__();
    return const_matrix;
}

template <typename value_t>
matrix<value_t> linear_equations<value_t>::get_term_matrix(const string &term_str)
{
    __init__();
    matrix<value_t> mat = const_matrix;
    mat.replace_col(const_coffs, get_term_poision(term_str));
    return mat;
}

template <typename value_t>
vector<value_t> linear_equations<value_t>::get_const_coffs()
{
    __init__();
    return const_coffs;
}

template <typename value_t>
uint32_t linear_equations<value_t>::get_term_poision(const string &term_str)
{
    uint32_t i = 0;
    for (const auto &var : vars)
    {
        if (var == term_str)
            return i;
        i++;
    }
    throw out_of_range("linear_equations::term_poision -> non existing term");
}

template <typename value_t>
vector<value_t> linear_equations<value_t>::get_term_coffs(const string &term_str)
{
    __init__();
    return const_matrix.get_col(get_term_poision(term_str));
}

template <typename value_t>
value_t linear_equations<value_t>::const_det()
{
    __init__();
    return const_matrix.det();
}

template <typename value_t>
value_t linear_equations<value_t>::term_det(const string &term_str)
{
    return get_term_matrix(term_str).det();
}

template <typename value_t>
linear_equations<value_t> &linear_equations<value_t>::insert(const string &equ_str)
{
    updated = false;
    equations.push_back(equation<value_t>(equ_str));
    set<string> new_vars = equations.back().get_vars();
    vars.insert(new_vars.begin(), new_vars.end());
    return *this;
}

template <typename value_t>
linear_equations<value_t> &linear_equations<value_t>::reomve(uint32_t index)
{
    if (index > size())
        throw out_of_range("linear_equations::reomve -> check index");
    equations.erase(equations.begin() + index);
    return *this;
}

template <typename value_t>
map<string, value_t> linear_equations<value_t>::solve_cramer()
{
    __init__();
    map<string, value_t> solution;
    value_t det = const_det();
    for (const auto &var : vars)
        solution.insert({var, term_det(var) / det});
    return solution;
}

template <typename value_t>
map<string, value_t> linear_equations<value_t>::solve_back_sub()
{
    __init__();
    map<string, value_t> solution;
    vector<value_t> sol = const_matrix.back_sub(const_coffs);
    int i = 0;
    for (const auto &var : vars)
        solution.insert({var, sol[i++]});
    return solution;
}

#endif // End of the file