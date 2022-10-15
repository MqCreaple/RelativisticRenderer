#pragma once

#include "macro.h"
#include "math/vec/Vec.h"

namespace gmq {

template<typename T, LengthT width, LengthT height>
class Mat {
public:
private:
};

template<typename T, LengthT a, LengthT b>
Mat<T, a, b> operator +(const Mat<T, a, b>&, const Mat<T, a, b>&);

template<typename T, LengthT a, LengthT b>
Mat<T, a, b> operator -(const Mat<T, a, b>&, const Mat<T, a, b>&);

template<typename T, LengthT a, LengthT b, LengthT c>
Mat<T, a, c> operator *(const Mat<T, a, b>&, const Mat<T, b, c>&);

template<typename T, LengthT a, LengthT b>
Vec<T, a> operator *(const Mat<T, a, b>&, const Vec<T, b>&);

} // namespace gmq