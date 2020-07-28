#ifndef _TERM_IMPL_H_
#define _TERM_IMPL_H_

#include <exception>

using std::out_of_range;

template <typename value_t>
term<value_t>::term()
    : var(""), coff(value_t())
{
    // do nothing
}

template <typename value_t>
term<value_t>::term(const term<value_t> &tm)
    : var(tm.var), coff(tm.coff)
{
    // do nothing
}

template <typename value_t>
term<value_t>::term(const string &var)
    : var(var), coff(value_t())
{
    // do nothing
}

template <typename value_t>
term<value_t>::term(const string &var, value_t coff)
    : var(var), coff(coff)
{
    // do nothing
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator=(const term<value_t> &tm)
{
    var = tm.var;
    coff = tm.coff;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator=(value_t val)
{
    coff = val;
    return *this;
}

template <typename value_t>
inline string term<value_t>::get_var()
{
    return var;
}

template <typename value_t>
inline value_t term<value_t>::get_coff()
{
    return coff;
}

template <typename value_t>
inline term<value_t> &term<value_t>::set_coff(value_t val)
{
    coff = val;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::set_var(string var_name)
{
    var = var_name;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator+=(value_t val)
{
    coff += val;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator-=(value_t val)
{
    coff -= val;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator*=(value_t val)
{
    coff *= val;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator/=(value_t val)
{
    coff /= val;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator++()
{
    ++coff;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator--()
{
    --coff;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator++(int)
{
    coff++;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator--(int)
{
    coff--;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator+()
{
    coff = +coff;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator-()
{
    coff = -coff;
    return *this;
}

template <typename value_t>
inline bool term<value_t>::operator==(value_t val)
{
    return coff == val;
}

template <typename value_t>
inline bool term<value_t>::operator!=(value_t val)
{
    return coff != val;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator+=(const term<value_t> &tm)
{
    if (var != tm.var)
        throw out_of_range("term::addition -> variables aren't the same");
    coff += tm.coff;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator-=(const term<value_t> &tm)
{
    if (var != tm.var)
        throw out_of_range("term::subtraction -> variables aren't the same");
    coff -= tm.coff;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator*=(const term<value_t> &tm)
{
    if (var != tm.var)
        throw out_of_range("term::multiplication -> variables aren't the same");
    coff *= tm.coff;
    return *this;
}

template <typename value_t>
inline term<value_t> &term<value_t>::operator/=(const term<value_t> &tm)
{
    if (var != tm.var)
        throw out_of_range("term::Devision -> variables aren't the same");
    coff /= tm.coff;
    return *this;
}

template <typename value_t>
inline bool term<value_t>::operator==(const term<value_t> &tm)
{
    return var == tm.var && coff == tm.coff;
}

template <typename value_t>
inline bool term<value_t>::operator!=(const term<value_t> &tm)
{
    return !(*this == tm);
}

template <typename value_t>
inline term<value_t> operator+(term<value_t> tm, value_t val)
{
    return tm += val;
}

template <typename value_t>
inline term<value_t> operator-(term<value_t> tm, value_t val)
{
    return tm -= val;
}

template <typename value_t>
inline term<value_t> operator*(term<value_t> tm, value_t val)
{
    return tm *= val;
}

template <typename value_t>
inline term<value_t> operator/(term<value_t> tm, value_t val)
{
    return tm /= val;
}

template <typename value_t>
inline term<value_t> operator+(term<value_t> tm1, term<value_t> tm2)
{
    return tm1 += tm2;
}

template <typename value_t>
inline term<value_t> operator-(term<value_t> tm1, term<value_t> tm2)
{
    return tm1 -= tm2;
}

template <typename value_t>
inline term<value_t> operator*(term<value_t> tm1, term<value_t> tm2)
{
    return tm1 *= tm2;
}

template <typename value_t>
inline term<value_t> operator/(term<value_t> tm1, term<value_t> tm2)
{
    return tm1 /= tm2;
}

template <typename value_t>
inline std::ostream &operator<<(std::ostream &os, const term<value_t> &tm)
{
    os << tm.coff << tm.var;
    return os;
}

#endif // End of the file