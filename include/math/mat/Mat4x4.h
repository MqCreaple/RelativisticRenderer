#pragma once

#include "macro.h"
#include "math/mat/Mat.h"
#include "math/vec/Vec.h"
#include "math/vec/Vec4.h"
#include "math/vec/LVec.h"

namespace gmq {

template<typename T>
class Mat<T, 4, 4> {
public:
    Mat() = default;
    Mat(Vec<T, 4> value[4]): value(value) {}
    Mat(const Vec<T, 4> &v1, const Vec<T, 4> &v2, const Vec<T, 4> &v3, const Vec<T, 4> &v4)
        : value({v1, v2, v3, v4}) {}
    Mat(T m11, T m12, T m13, T m14,
        T m21, T m22, T m23, T m24,
        T m31, T m32, T m33, T m34,
        T m41, T m42, T m43, T m44)
        : value({
            Vec<T, 4>(m11, m21, m31, m41),
            Vec<T, 4>(m12, m22, m32, m42),
            Vec<T, 4>(m13, m23, m33, m43),
            Vec<T, 4>(m14, m24, m34, m44)
        }) {}

    Vec<T, 4> operator [](LengthT index) const {
        return value[index];
        // TODO (add bound check)
    }
private:
    Vec<T, 4> value[4];         // stores 4 column vectors resembling the matrix
};

template<typename T>
Vec<T, 4> operator *(const Mat<T, 4, 4> &m, const Vec<T, 4> &v) {
    return Vec<T, 4> (
        m[0].w * v.w + m[1].w * v.x + m[2].w * v.y + m[3].w * v.z,
        m[0].x * v.w + m[1].x * v.x + m[2].x * v.y + m[3].x * v.z,
        m[0].y * v.w + m[1].y * v.x + m[2].y * v.y + m[3].y * v.z,
        m[0].z * v.w + m[1].z * v.x + m[2].z * v.y + m[3].z * v.z
    );
}

template<typename T>
LVec<T> operator *(const Mat<T, 4, 4> &m, const LVec<T> &v) {
    return LVec<T> (
        m[0].w * v.w + m[1].w * v.x + m[2].w * v.y + m[3].w * v.z,
        m[0].x * v.w + m[1].x * v.x + m[2].x * v.y + m[3].x * v.z,
        m[0].y * v.w + m[1].y * v.x + m[2].y * v.y + m[3].y * v.z,
        m[0].z * v.w + m[1].z * v.x + m[2].z * v.y + m[3].z * v.z
    );
}

template<typename T>
Mat<T, 4, 4> operator *(const Mat<T, 4, 4> &m, const Mat<T, 4, 4> &n) {
    return Mat<T, 4, 4>(m * n[0], m * n[1], m * n[2], m * n[3]);
}

template<typename T>
Mat<T, 4, 4> operator +(const Mat<T, 4, 4> &m, const Mat<T, 4, 4> &n) {
    return Mat<T, 4, 4>(m[0] + n[0], m[1] + n[1], m[2] + n[2], m[3] + n[3]);
}

template<typename T>
Mat<T, 4, 4> operator -(const Mat<T, 4, 4> &m, const Mat<T, 4, 4> &n) {
    return Mat<T, 4, 4>(m[0] - n[0], m[1] - n[1], m[2] - n[2], m[3] - n[3]);
}

} // namespace gmq