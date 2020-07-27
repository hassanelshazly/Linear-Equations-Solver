#ifndef _LINEAR_EQUS_IMPL_H_
#define _LINEAR_EQUS_IMPL_H_

#include "linear_equs.h"

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
    if(str == "" ) return str;
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
            if(str.substr(j,i-j) != "") exp.push_back(str.substr(j,i-j));
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
            while(str[index_key] != '+' && str[index_key] != '-' && str[index_key] != '=' && index_key < str.length())
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

    int i = str.find('=');
    string right = str.substr(0, i);
    init_apart(right, m, used, true);
    for(const string& s : used)
        right.erase(right.find(s), s.length());
    m["="] = ValueType();
    if(right != "")
        m["="] -= evaluate(right);
    used.clear();

    string left = str.substr(i+1);
    init_apart(left, m, used, false);
    for(const string& s : used)
        left.erase(left.find(s), s.length());
    if(left != "")
        m["="] += evaluate(left);

    for(const auto& item : m)
        if(item.first != "=")
            vars.insert(item.first);
    sols.push_back(m["="]);
    equs.push_back(m);
    init_flag = false;
    num_of_equs++;
    return m;
}

template <typename ValueType>
linear_equs<ValueType>& linear_equs<ValueType>::init_coffs()
{
    if(!init_flag)
    {
        coffs.resize(num_of_equs, vars.size());
        for(auto& item : equs)
            for(const auto& var : vars)
                if(item.find(var) == item.end())
                    item[var] = ValueType();
        int i = 0, j = 0;
        for(const auto& equ : equs)
        {
            for(const auto& item : equ)
                if(item.first != "=")
                    coffs[i][j++] = item.second;
            j = 0; i++;
        }
        init_flag = true;
    }   
}

template <typename ValueType>
string linear_equs<ValueType>::convert(map<string, ValueType> equ)  
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
    : init_flag(false), num_of_equs(0), coffs(matrix<ValueType>()), sols(vector<ValueType>()) {}

template <typename ValueType>
linear_equs<ValueType>& linear_equs<ValueType>::push_equ(string str) 
{
    init_equ(str);
    return *this;
}

template <typename ValueType>
string linear_equs<ValueType>::get_equ(size_t index) 
{
    init_coffs();
    return convert(equs[index]);
}

template <typename ValueType>
vector<ValueType> linear_equs<ValueType>::get_var_coffs(const string var) 
{
    init_coffs();
    vector<ValueType> vec;
    for(auto& item : equs)
        if(item.find(var) != item.end())
            vec.push_back(item[var]);
        else
            vec.push_back(ValueType());
    return vec;
}

template <typename ValueType>
size_t linear_equs<ValueType>::get_num_of_vars()  
{
    return vars.size();
}

template <typename ValueType>
string linear_equs<ValueType>::add_equs(size_t equ1, size_t equ2) 
{
    init_coffs();
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
    init_coffs();
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
    init_coffs();
    vector<ValueType> v1 = coffs.get_row(equ1);
    vector<ValueType> v2 = coffs.get_row(equ2);
    ValueType coff1 = equs[equ1][var];
    ValueType coff2 = equs[equ2][var];
    ValueType sol1 = sols[equ1] ;
    ValueType sol2 = sols[equ2] ;
    map<string, ValueType> res_map;

    for(int i = 0; i < v1.size(); i++)
        v1[i] += v2[i] * (-coff1 / coff2);
    sol2 += sol1 * (-coff1 / coff2);

    vector<string> var_names ;
    std::copy(vars.begin(), vars.end(), std::back_inserter(var_names));
    for(int i = 0; i < v1.size(); i++)
        res_map.insert(std::make_pair(var_names[i], v1[i]));
    res_map.insert(std::make_pair("=", sol1));
    return convert(res_map);
}

template <typename ValueType>
matrix<ValueType> linear_equs<ValueType>::get_coffs_mat()  
{
    init_coffs();
    return coffs ;
}

template <typename ValueType>
ValueType linear_equs<ValueType>::get_coffs_det()  
{
    init_coffs();
    return determinant(coffs) ;
}

template <typename ValueType>
matrix<ValueType> linear_equs<ValueType>::get_var_mat(string var) 
{
    init_coffs();
    matrix<ValueType> mat = coffs;
    vector<string> var_names ;
    std::copy(vars.begin(), vars.end(), std::back_inserter(var_names));
    int index = std::find(var_names.begin(), var_names.end(), var) - var_names.begin();
    mat.replace_col(sols, index);
    return mat;
}

template <typename ValueType>
ValueType linear_equs<ValueType>::get_var_det(string var) 
{
    init_coffs();
    return determinant(get_var_mat(var));
}

template <typename ValueType>
map<string, ValueType> linear_equs<ValueType>::solve_by_cramer_method()  
{
    init_coffs();
    map<string, ValueType> solution;
    ValueType d_val = get_coffs_det();
    for(const string& var : vars)
    {
        ValueType var_val = get_var_det(var);
        solution.insert(std::make_pair(var, var_val/d_val));
    }
    return solution;
}

template <typename ValueType>
map<string, ValueType> linear_equs<ValueType>::solve_by_backSub() 
{
    init_coffs();
    map<string, ValueType> solution;
    vector<ValueType> sol = back_substitution(coffs, sols);
    int i = 0;
    for(const string& var : vars)
        solution.insert(std::make_pair(var, sol[i++]));
    return solution;
}

#endif // End of the file