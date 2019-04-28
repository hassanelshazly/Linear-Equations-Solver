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
#include "../Matrix/matrix.h"

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
    if(str == "") return "";
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
            while(str[index_key] != '+' && str[index_key] != '-' && str[index_key] != '=')
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
            i+= key.length()-1;
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
