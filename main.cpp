#include <iostream>
#include <string>
#include "linear_equs.h"
#include "../Matrix/matrix.h"

using namespace std;

string remove_spaces(string str)
{
    for(int i = 0; i < str.length(); i++)
        if(str[i] == ' ')
            str.erase(i,1);
    return str;
}

int main()
{
    linear_equs<float> ln;
    int n; cin >> n;
    cin.ignore(1000,'\n');
    string str; 
    for(int i = 0; i < n; i++)
    {
        getline(cin, str);
        ln.push_equ(remove_spaces(str));
    }
    cin >> str ;
    if(str == "num_vars")
    {
        cout << ln.get_num_of_vars();
    }
    else if(str == "equation")
    {
        cin >> n;
        cout << ln.get_equ(n-1);
    }
    else if(str == "column")
    {
        cin >> str;
        vector<float> vec = ln.get_var_coffs(str);
        for(const auto& item : vec)
            cout << item << endl;
    }
    else if(str == "add")
    {
        int i, j; cin >> i >> j;
        cout << ln.add_equs(i-1, j-1);
    }
    else if(str == "subtract")
    {
        int i, j; cin >> i >> j;
        cout << ln.subtract_equs(i-1, j-1);
    }
    else if(str == "substitute")
    {
        int i, j; cin >> str >> i >> j;
        cout << ln.substitute_equs(str, i-1, j-1);
    }
    else if(str == "D")
    {
        cin.unget();
        getline(cin, str);
        if(str == "D")
            cout << ln.get_coffs_mat();
        else
            cout << ln.get_var_mat(str.substr(2));
    }
    else if(str == "D_value")
    {
        cout << ln.get_coffs_det();
    }
    else if(str == "solve")
    {
        map<string, float> m = ln.solve();
        for(const auto& item : m)
            cout << item.first << "=" << item.second << endl;
    } 
}