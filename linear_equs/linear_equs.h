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

#include "matrix.h"

using std::vector;
using std::string;
using std::map;

template <typename ValueType>
class linear_equs
{
public:
    linear_equs();

    linear_equs<ValueType>& push_equ(string str) ;
    string get_equ(size_t index) ;

    vector<ValueType> get_var_coffs(const string var) ;
    size_t get_num_of_vars()  ;

    string add_equs(size_t equ1, size_t equ2) ;
    string subtract_equs(size_t equ1, size_t equ2) ;
    string substitute_equs(string var, size_t equ1, size_t equ2) ;
    matrix<ValueType> get_coffs_mat()  ;

    ValueType get_coffs_det()  ;
    matrix<ValueType> get_var_mat(string var) ;
    ValueType get_var_det(string var) ;
    map<string, ValueType> solve_by_cramer_method() ;
    map<string, ValueType> solve_by_backSub() ;

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
    linear_equs<ValueType>& init_coffs();
    map<string, ValueType> init_equ(string str);
    string convert(map<string, ValueType> equ) ;
    map<string, ValueType> init_apart(string& str, 
                        map<string, ValueType>& m, vector<string>& used, bool right);
};



// include implemention
#include "linear_equs_impl.h"

#endif // End of the file
