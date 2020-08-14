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

#ifdef _TEST_TERM_

#include <iostream>
#include <cassert>

#include "term.h"

using namespace std;

int main(int argc, char **agrv)
{
    term<int> x{"x", 4};
    term<int> y{"y", 3};
    term<int> t;

    assert(x == 4);
    assert(y == 3);
    assert(x != y);

    try
    {
        t = x + y;
        assert(false);
    }
    catch (...)
    {
        assert(t == 0);
    }

    t = x * 2;
    assert(t == 8);
    t /= 4;
    assert(t == 2);
    t = y;
    assert(t == y);
    t = -x;
    assert(t == -4 && t.get_var() == "x");

    t++;
    assert(t == -3);
    t--;
    assert(t == -4);
    // cout << t;
    cout << "Testing term completed sucessfully" << endl;
}

#endif
