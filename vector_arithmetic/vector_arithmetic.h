#ifndef _VECTOR_ARITHMETIC_
#define _VECTOR_ARITHMETIC_

#include <vector>

using std::vector ;

namespace vector_arithmetic_operations
{
    template <typename ValueType>
    vector<ValueType>& operator+=(vector<ValueType>& vec1, const vector<ValueType>& vec2)
    {
        size_t size = vec1.size();
        if(size != vec2.size())
            throw std::length_error("vector_arithmetic::addition -> vectors must be the same size");
        for(int i = 0; i < size; i++)
            vec1[i] += vec2[i];
        return vec1;
    }

    template <typename ValueType>
    vector<ValueType>& operator-=(vector<ValueType>& vec1, const vector<ValueType>& vec2)
    {
        size_t size = vec1.size();
        if(size != vec2.size())
            throw std::length_error("vector_arithmetic::subtraction -> vectors must be the same size");
        for(int i = 0; i < size; i++)
            vec1[i] -= vec2[i];
        return vec1;
    }

    template <typename ValueType>
    vector<ValueType>& operator*=(vector<ValueType>& vec1, const vector<ValueType>& vec2)
    {
        size_t size = vec1.size();
        if(size != vec2.size())
            throw std::length_error("vector_arithmetic::multiplication -> vectors must be the same size");
        for(int i = 0; i < size; i++)
            vec1[i] *= vec2[i];
        return vec1;
    }

    template <typename ValueType>
    vector<ValueType>& operator/=(vector<ValueType>& vec1, const vector<ValueType>& vec2)
    {
        size_t size = vec1.size();
        if(size != vec2.size())
            throw std::length_error("vector_arithmetic::devision -> vectors must be the same size");
        for(int i = 0; i < size; i++)
            vec1[i] /= vec2[i];
        return vec1;
    }

    template <typename ValueType>
    vector<ValueType> operator+(const vector<ValueType>& vec1, const vector<ValueType>& vec2)
    {
        size_t size = vec1.size();
        if(size != vec2.size())
            throw std::length_error("vector_arithmetic::addition -> vectors must be the same size");
        vector<ValueType> res(size);
        for(int i = 0; i < size; i++)
            res[i] = vec1[i] + vec2[i];
        return res;
    }

    template <typename ValueType>
    vector<ValueType> operator-(const vector<ValueType>& vec1, const vector<ValueType>& vec2)
    {
        size_t size = vec1.size();
        if(size != vec2.size())
            throw std::length_error("vector_arithmetic::subtraction -> vectors must be the same size");
        vector<ValueType> res(size);
        for(int i = 0; i < size; i++)
            res[i] = vec1[i] - vec2[i];
        return res;
    }

    template <typename ValueType>
    vector<ValueType> operator*(const vector<ValueType>& vec1, const vector<ValueType>& vec2)
    {
        size_t size = vec1.size();
        if(size != vec2.size())
            throw std::length_error("vector_arithmetic::multiplication -> vectors must be the same size");
        vector<ValueType> res(size);
        for(int i = 0; i < size; i++)
            res[i] = vec1[i] * vec2[i];
        return res;
    }

    template <typename ValueType>
    vector<ValueType> operator/(const vector<ValueType>& vec1, const vector<ValueType>& vec2)
    {
        size_t size = vec1.size();
        if(size != vec2.size())
            throw std::length_error("vector_arithmetic::devision -> vectors must be the same size");
        vector<ValueType> res(size);
        for(int i = 0; i < size; i++)
            res[i] = vec1[i] / vec2[i];
        return res;
    }

    template <typename ValueType>
    vector<ValueType>& operator+=(vector<ValueType>& vec, const ValueType& val)
    {
        for(auto& element : vec)
            element += val;
        return vec;
    }

    template <typename ValueType>
    vector<ValueType>& operator-=(vector<ValueType>& vec, const ValueType& val)
    {
        for(auto& element : vec)
            element -= val;
        return vec;
    }

    template <typename ValueType>
    vector<ValueType>& operator*=(vector<ValueType>& vec, const ValueType& val)
    {
        for(auto& element : vec)
            element *= val;
        return vec;
    }

    template <typename ValueType>
    vector<ValueType>& operator/=(vector<ValueType>& vec, const ValueType& val)
    {
        for(auto& element : vec)
            element /= val;
        return vec;
    }

    template <typename ValueType>
    vector<ValueType> operator+(const vector<ValueType>& vec, const ValueType& val)
    {
        vector<ValueType> res(vec.size());
        size_t i = 0 ;
        for(auto& element : vec)
            res[i++] = element + val;
        return res;
    }

    template <typename ValueType>
    vector<ValueType> operator-(const vector<ValueType>& vec, const ValueType& val)
    {
        vector<ValueType> res(vec.size());
        size_t i = 0 ;
        for(auto& element : vec)
            res[i++] = element - val;
        return res;
    }

    template <typename ValueType>
    vector<ValueType> operator*(const vector<ValueType>& vec, const ValueType& val)
    {
        vector<ValueType> res(vec.size());
        size_t i = 0 ;
        for(auto& element : vec)
            res[i++] = element * val;
        return res;
    }

    template <typename ValueType>
    vector<ValueType> operator/(const vector<ValueType>& vec, const ValueType& val)
    {
        vector<ValueType> res(vec.size());
        size_t i = 0 ;
        for(auto& element : vec)
            res[i++] = element / val;
        return res;
    }

    template <typename ValueType>
    ValueType sum(const vector<ValueType>& vec)
    {
        ValueType res = ValueType();
        for(const auto& element : vec)
            res += element;
        return res;
    }

    template <typename ValueType>
    ValueType dot_product(const vector<ValueType>& vec1, const vector<ValueType>& vec2)
    {
        size_t size = vec1.size();
        if(size != vec2.size())
            throw std::length_error("vector_arithmetic::dot_product -> vectors must be the same size");
        ValueType res = ValueType();
        for(int i = 0; i < size; i++)
            res += vec1[i] * vec2[i] ;
        return res;
    }

}

#endif