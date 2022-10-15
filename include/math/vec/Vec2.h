#pragma once

#include "math/vec/Vec.h"

namespace gmq {

template<typename T>
class Vec<T, 2> {
public:
    T x;
    T y;

    Vec(): x(0), y(0) {}
    Vec(T scalar): x(scalar), y(scalar) {}
    Vec(T x, T y): x(x), y(y) {}

    template<typename X, typename Y>
    Vec(X x, Y y): x(static_cast<T>(x)), y(static_cast<T>(y)) {}

    Vec(const Vec &other): x(other.x), y(other.y) {}

    T length() const {
        return hypot(x, y);
    }
    T sqLength() const {
        return x * x + y * y;
    }
    Vec<T, 2> normalized() const {
        T len = length();
        return Vec<T, 2>(x / len, y / len);
    }
    T operator [](LengthT index) const {
        return (index == 0)? x: y;
    }
    Vec &operator +=(const Vec &vec) {
        this->x += vec.x;
        this->y += vec.y;
        return *this;
    }
    Vec &operator -=(const Vec &vec) {
        this->x -= vec.x;
        this->y -= vec.y;
        return *this;
    }
    Vec &operator *=(T scalar) {
        this->x -= scalar;
        this->y -= scalar;
        return *this;
    }
    Vec &operator /=(T scalar) {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }
private:
};

template<typename T>
bool isZero(const Vec<T, 2> &v) {
    return v.x == 0 && v.y == 0;
}

template<typename T>
bool operator ==(const Vec<T, 2> &v, const Vec<T, 2> &w) {
    return (v.x == w.x) && (v.y == w.y);
}

template<typename T>
bool operator != (const Vec<T, 2> &v, const Vec<T, 2> &w) {
    return (v.x != w.x) || (v.y != w.y);
}

template<typename T>
Vec<T, 2> operator +(const Vec<T, 2> &v, const Vec<T, 2> &w) {
    return Vec<T, 2>(v.x + w.x, v.y + w.y);
}

template<typename T>
Vec<T, 2> operator -(const Vec<T, 2> &v, const Vec<T, 2> &w) {
    return Vec<T, 2>(v.x - w.x, v.y - w.y);
}

template<typename T>
Vec<T, 2> operator *(const Vec<T, 2> &v, T r) {
    return Vec<T, 2>(v.x * r, v.y * r);
}

template<typename T>
Vec<T, 2> operator *(T r, const Vec<T, 2> &v) {
    return Vec<T, 2>(r * v.x, r * v.y);
}

template<typename T>
Vec<T, 2> operator /(const Vec<T, 2> &v, T r) {
    return Vec<T, 2>(v.x / r, v.y / r);
}

} // namespace gmq