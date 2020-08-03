#ifndef _TERM_H_
#define _TERM_H_

#include <string>

using std::string;

template <typename value_t>
class term
{
public:
    /**
     * Default constructor
     */
    term();

    /**
     * Copy constructor
     */
    term(const term &tm);

    /**
     * Move constructor
     */
    term(const term &&tm);

    /**
     * Construct term with the default coff value
     */
    term(const string &var);

    /**
     * Construct term with a given name and coff value
     */
    term(const string &var, value_t coff);

    /**
     * Assignment operator
     * @return reference to the object
     */
    term &operator=(const term &tm);

    /**
     * Assignment coff only
     * @return reference to the object
     */
    term &operator=(value_t val);

    /**
     * @return variable name
     */
    string get_var() const;

    /**
     * @return coff value
     */
    value_t get_coff() const;

    /**
     * Change the value of the coff 
     * @return reference to the object
     */
    term &set_coff(value_t val);

    /**
     * Change the value of variable name 
     * @return reference to the object
     */
    term &set_var(string var_name);

    /**
     * Add val to the coff
     * @return reference to the object
     */
    term &operator+=(value_t val);

    /**
     * Subract val to the coff
     * @return reference to the object
     */
    term &operator-=(value_t val);

    /**
     * Multiply val with the coff
     * @return reference to the object
     */
    term &operator*=(value_t val);

    /**
     * Divide coff on val
     * @return reference to the object
     */
    term &operator/=(value_t val);

    /**
     * Add one to the coff prefix++
     * @return reference to the object
     */
    term &operator++();

    /**
     * Subtract one from the coff ptrfix--
     * @return reference to the object
     */
    term &operator--();

    /**
     * Add one to the coff postfix++
     * @return reference to the object
     */
    term &operator++(int);

    /**
     * Subtract one from the coff postfix--
     * @return reference to the object
     */
    term &operator--(int);

    /**
     * unary plus
     * @return reference to the object
     */
    term &operator+();

    /**
     * unary minus
     * @return reference to the object
     */
    term &operator-();

    /**
     * @return true if the coffs are equal
     */
    bool operator==(value_t val) const;

    /**
     * @return true if the coffs are not equal
     */
    bool operator!=(value_t val) const;

    /**
     * Add the two terms
     * @throw  out_of_range() if the terms are not the same
     * @return reference to the calling object
     */
    term &operator+=(const term &tm);

    /**
     * Subtract the two terms
     * @throw  out_of_range() if the terms are not the same
     * @return reference to the calling object
     */
    term &operator-=(const term &tm);

    /**
     * Multiply the two terms
     * @throw  out_of_range() if the terms are not the same
     * @return reference to the calling object
     */
    term &operator*=(const term &tm);

    /**
     * Divide the two terms
     * @throw  out_of_range() if the terms are not the same
     * @return reference to the calling object
     */
    term &operator/=(const term &tm);

    /**
      * @return true if the two terms are equal
      */
    bool operator==(const term &tm) const;

    /**  
      * @return true if the two terms are not equal
      */
    bool operator!=(const term &tm) const;

    /**
     * @return true if var > tm.var
     */
    bool operator>(const term &tm) const;

    /**
     * @return true if var < tm.var
     */
    bool operator<(const term &tm) const;

    /**
     * @return true if var >= tm.var
     */
    bool operator>=(const term &tm) const;

    /**
      * @return true if var <= tm.var
      */
    bool operator<=(const term &tm) const;

    /**
     * @return true if coff > val
     */
    bool operator>(value_t val) const;

    /**
     * @return true if coff < val
     */
    bool operator<(value_t val) const;

    /**
     * @return true if coff >= val
     */
    bool operator>=(value_t val) const;

    /**
     * @return true if coff <= val
     */
    bool operator<=(value_t val) const;

    /**************************************************************************
     *************  Static and friend functions and operators  ****************
     **************************************************************************/

    /**
     * @return a new object results from addition
     */
    template <typename T>
    friend term<T> operator+(term<T> tm, T val);

    /**
     * @return a new object results from subtraction
     */
    template <typename T>
    friend term<T> operator-(term<T> tm, T val);

    /**
     * @return a new object results from multipliction
     */
    template <typename T>
    friend term<T> operator*(term<T> tm, T val);

    /**
     * @return a new object results from Division
     */
    template <typename T>
    friend term<T> operator/(term<T> tm, T val);

    /**
     * Add the two terms
     * @throw  out_of_range() if the terms are not the same
     * @return a new object results from addition
     */
    template <typename T>
    friend term<T> operator+(term<T> tm1, term<T> tm2);

    /**
     * Subtract the two terms
     * @throw  out_of_range() if the terms are not the same
     * @return a new object results from subtraction
     */
    template <typename T>
    friend term<T> operator-(term<T> tm1, term<T> tm2);

    /**
     * Multiply the two terms
     * @throw  out_of_range() if the terms are not the same
     * @return a new object results from multipliction
     */
    template <typename T>
    friend term<T> operator*(term<T> tm1, term<T> tm2);

    /**
     * Divide the two terms
     * @throw  out_of_range() if the terms are not the same
     * @return a new object results from Division
     */
    template <typename T>
    friend term<T> operator/(term<T> tm1, term<T> tm2);

    /**
     * Overloads << operator to print term as a native type.
     */
    template <typename T>
    friend std::ostream &operator<<(std::ostream &os, const term<T> &tm);

private:
    string var;
    value_t coff;
};

// include implemention
#include "term_impl.h"

#endif // End of the file
