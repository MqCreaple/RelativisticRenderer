#pragma once

#include "math/vec/Vec.h"
#include "math/vec/Vec4.h"

namespace gmq {

/**
 * @brief 4-dimensional vector in Minkowski space
 * Unlike Euclidean vector, vectors in Minkowski space have a metric of $s=-t^2+x^2+y^2+z^2$.
 * @tparam T type of vector element
 */
template<typename T>
class LVec: public Vec<T, 4> {
public:
    LVec(): Vec<T, 4>() {}
    LVec(T t, T x, T y, T z): Vec<T, 4>(t, x, y, z) {}
    LVec(T t, const Vec<T, 3> &r): Vec<T, 4>(t, r) {}

    T length() const override {
        return sqrt(-this->t * this->t + this->x * this->x + this->y * this->y + this->z * this->z);
    }
    T sqLength() const override {
        return -this->t * this->t + this->x * this->x + this->y * this->y + this->z * this->z;
    }
};

template<typename T>
LVec<T> operator +(const LVec<T> &v, const LVec<T> &w) {
    return LVec<T>(v.t + w.t, v.x + w.x, v.y + w.y, v.z + w.z);
}

template<typename T>
LVec<T> operator -(const LVec<T> &v, const LVec<T> &w) {
    return LVec<T>(v.t - w.t, v.x - w.x, v.y - w.y, v.z - w.z);
}

template<typename T>
LVec<T> operator *(const LVec<T> &v, T r) {
    return LVec<T>(v.t * r, v.x * r, v.y * r, v.z * r);
}

template<typename T>
LVec<T> operator *(T r, const LVec<T> &v) {
    return LVec<T>(r * v.t, r * v.x, r * v.y, r * v.z);
}

template<typename T>
LVec<T> operator /(const LVec<T> &v, T r) {
    return LVec<T>(v.t / r, v.x / r, v.y / r, v.z / r);
}

template<typename T>
T dot(const LVec<T> &v, const LVec<T> &w) {
    return -v.t * w.t + v.x * w.x + v.y * w.y + v.z * w.z;
}

} // namespace gmq