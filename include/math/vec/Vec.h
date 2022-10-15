#pragma once

#include <cmath>
#include "macro.h"

namespace gmq {

template<typename T, LengthT len>
class Vec {
public:
    virtual T length() const;

    // length squared
    virtual T sqLength() const;

    virtual Vec<T, len> normalized() const;

    // get the ith index of vector. index starts from 0.
    virtual T operator [](LengthT index) const;
private:
};

/**
 * @brief Checks if an vector is zero vector (all of its components are zero).
 * @tparam T type of vector elements
 * @tparam len dimension of vector
 * @param vec vector being tested
 * @return bool if the vector is zero vector.
 */
template<typename T, LengthT len>
bool isZero(const Vec<T, len>& vec);

template<typename T, LengthT len>
bool operator ==(const Vec<T, len>&, const Vec<T, len>&);

template<typename T, LengthT len>
bool operator != (const Vec<T, len>&, const Vec<T, len>&);

template<typename T, LengthT len>
Vec<T, len> operator -(const Vec<T, len>&);

template<typename T, LengthT len>
Vec<T, len> operator +(const Vec<T, len>&, const Vec<T, len>&);

template<typename T, LengthT len>
Vec<T, len> operator -(const Vec<T, len>&, const Vec<T, len>&);

template<typename T, LengthT len>
Vec<T, len> operator *(const Vec<T, len>&, T);

template<typename T, LengthT len>
Vec<T, len> operator *(T, const Vec<T, len>&);

template<typename T, LengthT len>
Vec<T, len> operator /(const Vec<T, len>&, T);

template<typename T, LengthT len>
T dot(const Vec<T, len>&, const Vec<T, len>&);

} // namespace gmq