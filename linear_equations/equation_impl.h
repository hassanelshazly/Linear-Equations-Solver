#ifndef _EQUATION_IMPL_H_
#define _EQUATION_IMPL_H_

#include <regex>

using std::find;
using std::regex;
using std::regex_search;
using std::smatch;

/**
 * This file needs -fpermissive flag.
 * although we update the values in the set directly the order doesn't 
 * change as it depends on the variable name so the update is save
 */
template <typename value_t>
equation<value_t>::equation()
    : terms(), constant(value_t())
{
    // do nothing
}

template <typename value_t>
equation<value_t>::equation(const equation<value_t> &equ)
    : terms(equ.terms), constant(equ.constant)
{
    // do nothing
}

template <typename value_t>
equation<value_t>::equation(const string &equ_str)
    : equation(convert(equ_str))
{
    // do nothing
}

template <typename value_t>
inline uint32_t equation<value_t>::size()
{
    return terms.size();
}

template <typename value_t>
value_t equation<value_t>::get(const string &var)
{
    auto found = terms.find(term<value_t>(var));
    if (found != terms.end())
        return found->get_coff();
    return value_t();
}

template <typename value_t>
set<string> equation<value_t>::get_vars()
{
    set<string> vars;
    for (const auto &term : terms)
        vars.insert(term.get_var());
    return vars;
}

template <typename value_t>
set<term<value_t>> equation<value_t>::get_terms()
{
    return terms;
}

template <typename value_t>
inline value_t equation<value_t>::get_const()
{
    return constant;
}

template <typename value_t>
equation<value_t> &equation<value_t>::add_term(term<value_t> tm)
{
    auto found = terms.find(tm);
    if (found != terms.end())
        (*found) += tm;
    else
        terms.insert(tm);
    return *this;
}

template <typename value_t>
equation<value_t> &equation<value_t>::subtract_term(term<value_t> tm)
{
    auto found = terms.find(tm);
    if (found != terms.end())
        (*found) -= tm;
    else
        terms.insert(-tm);
    return *this;
}

template <typename value_t>
inline equation<value_t> &equation<value_t>::add_term(const string &var, value_t val)
{
    return add_term(term<value_t>(var, val));
}

template <typename value_t>
equation<value_t> &equation<value_t>::set_term(const string &var, value_t val)
{
    term<value_t> tm(var, val);
    auto found = terms.find(tm);
    if (found != terms.end())
        (*found).set_coff(val);
    else
        terms.insert(tm);
    return *this;
}

template <typename value_t>
inline equation<value_t> &equation<value_t>::set_const(value_t val)
{
    constant = val;
}

template <typename value_t>
inline equation<value_t> &equation<value_t>::add_const(value_t val)
{
    constant += val;
}

template <typename value_t>
inline equation<value_t> &equation<value_t>::subtract_const(value_t val)
{
    constant -= val;
}

template <typename value_t>
equation<value_t> &equation<value_t>::remove_term(const string &var)
{
    terms.erase(term<value_t>(var));
    return *this;
}

template <typename value_t>
equation<value_t> &equation<value_t>::sub_term(const string &var, value_t val)
{
    constant -= get(var) * val;
    remove_term(var);
    return *this;
}

template <typename value_t>
equation<value_t> &equation<value_t>::add(const equation<value_t> &equ)
{
    for (const auto &term : equ.terms)
        add_term(term);
    constant += equ.constant;
    return *this;
}

template <typename value_t>
equation<value_t> &equation<value_t>::subtract(const equation<value_t> &equ)
{
    for (const auto &term : equ.terms)
        subtract_term(term);
    constant -= equ.constant;
    return *this;
}

template <typename value_t>
equation<value_t> &equation<value_t>::multiply(value_t val)
{
    for (auto &term : terms)
        term *= val;
    constant *= val;
    return *this;
}

template <typename value_t>
equation<value_t> &equation<value_t>::divide(value_t val)
{
    for (auto &term : terms)
        term /= val;
    constant /= val;
    return *this;
}

template <typename value_t>
inline equation<value_t> &equation<value_t>::operator+=(const equation<value_t> &equ)
{
    return add(equ);
}

template <typename value_t>
inline equation<value_t> &equation<value_t>::operator-=(const equation<value_t> &equ)
{
    return subtract(equ);
}

template <typename value_t>
inline equation<value_t> &equation<value_t>::operator*=(value_t val)
{
    return multiply(val);
}

template <typename value_t>
inline equation<value_t> &equation<value_t>::operator/=(value_t val)
{
    return divide(val);
}

template <typename value_t>
inline equation<value_t> &operator+(equation<value_t> equ1, const equation<value_t> &equ2)
{
    return equ1.add(equ2);
}

template <typename value_t>
inline equation<value_t> &operator-(equation<value_t> equ1, const equation<value_t> &equ2)
{
    return equ1.subtract(equ2);
}

template <typename value_t>
inline equation<value_t> &operator*(equation<value_t> equ, value_t val)
{
    return equ.multiply(val);
}

template <typename value_t>
inline equation<value_t> &operator/(equation<value_t> equ, value_t val)
{
    return equ.divide(val);
}

template <typename value_t>
std::ostream &operator<<(std::ostream &os, const equation<value_t> &equ)
{
    bool flag_term = false;
    for (const auto &term : equ.terms)
    {
        if (term == value_t())
            continue;

        else if (term == static_cast<value_t>(1))
            if (flag_term)
                os << "+" << term.get_var();
            else
                os << term.get_var();

        else if (term == static_cast<value_t>(-1))
            os << "-" << term.get_var();

        else if (term > 0)
            if (flag_term)
                os << "+" << term;
            else
                os << term;
        else
            os << term;

        flag_term = true;
    }
    if (equ.terms.size() != 0)
        os << "=";
    os << equ.constant;
    os << "\n";
    return os;
}

template <typename value_t>
equation<value_t> equation<value_t>::convert(const string &equ_str)
{
    vector<string> matched;
    matched = get_tokens(equ_str, "=");
    if (matched.size() != 1)
        throw out_of_range("equation::convert -> more or less than = sign");
    uint32_t index = equ_str.find("=");
    equation<value_t> equ1 = evaluate(equ_str.substr(0, index), -1);
    equation<value_t> equ2 = evaluate(equ_str.substr(index + 1, equ_str.length()), 1);
    return equ1.add(equ2);
}

template <typename value_t>
equation<value_t> equation<value_t>::evaluate(const string &equ_str, int sign)
{
    string num_re = "[+\\-0-9.]+";
    string var_re = "[a-zA-Z_][a-zA-Z0-9_]{0,}";
    string term_re = "[+-]{0,1}[.a-zA-Z0-9_]+";

    vector<string> matched;
    vector<string> matched_temp;
    equation<value_t> result;
    matched = get_tokens(equ_str, term_re);
    for (const auto &match : matched)
    {
        matched_temp = get_tokens(match, var_re);
        string var;
        value_t coff;
        if (matched_temp.size() == 0)
        {
            if (match == "+")
                coff = static_cast<value_t>(1);
            else if (match == "-")
                coff = static_cast<value_t>(-1);
            else
                coff = static_cast<value_t>(atof(match.c_str()));
            result.constant += (coff * sign);
        }
        else
        {
            var = matched_temp[0];
            matched_temp = get_tokens(match, num_re);
            // std::cout << "/  " << matched_temp[0] << "  " << equ_str.find(matched_temp[0]) << " /\n";
            if (matched_temp.size() == 0 || match.find(matched_temp[0]) != 0)
                coff = static_cast<value_t>(1);
            else if (matched_temp[0] == "+")
                coff = static_cast<value_t>(1);
            else if (matched_temp[0] == "-")
                coff = static_cast<value_t>(-1);
            else
                coff = static_cast<value_t>(atof(matched_temp[0].c_str()));
            result.add_term(var, coff * (-sign));
        }
    }
    return result;
}

template <typename value_t>
vector<string> equation<value_t>::get_tokens(string to_match, const string &pattern)
{
    smatch result;
    regex rg(pattern);
    vector<string> matched;
    while (regex_search(to_match, result, rg))
    {
        matched.push_back(result[0]);
        to_match = result.suffix();
    }
    return matched;
}

#endif // End of the file