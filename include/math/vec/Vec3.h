#pragma once

#include "math/vec/Vec.h"

namespace gmq {

template<typename T>
class Vec<T, 3> {
public:
    T x;
    T y;
    T z;

    Vec(): x(0), y(0), z(0) {}
    Vec(T scalar): x(scalar), y(scalar), z(scalar) {}
    Vec(T x, T y, T z): x(x), y(y), z(z) {}

    template<typename X, typename Y, typename Z>
    Vec(X x, Y y, Z z): x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)) {}

    Vec(const Vec &other): x(other.x), y(other.y), z(other.z) {}

    T length() const {
        return sqrt(x * x + y * y + z * z);
    }
    T sqLength() const {
        return x * x + y * y + z * z;
    }
    Vec<T, 3> normalized() const {
        T len = length();
        return Vec<T, 3>(x / len, y / len, z / len);
    }
    T operator [](LengthT index) const {
        switch(index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
            default:
                return z;
        }
    }
    Vec &operator +=(const Vec &vec) {
        this->x += vec.x;
        this->y += vec.y;
        this->z += vec.z;
        return *this;
    }
    Vec &operator -=(const Vec &vec) {
        this->x -= vec.x;
        this->y -= vec.y;
        this->z -= vec.z;
        return *this;
    }
    Vec &operator *=(T scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }
    Vec &operator /=(T scalar) {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        return *this;
    }
private:
};

template<typename T>
bool isZero(const Vec<T, 3> &v) {
    return v.x == 0 && v.y == 0 && v.z == 0;
}

template<typename T>
bool operator ==(const Vec<T, 3> &v, const Vec<T, 3> &w) {
    return (v.x == w.x) && (v.y == w.y) && (v.z == w.z);
}

template<typename T>
bool operator != (const Vec<T, 3> &v, const Vec<T, 3> &w) {
    return (v.x != w.x) || (v.y != w.y) || (v.z != w.z);
}

template<typename T>
Vec<T, 3> operator -(const Vec<T, 3> &v) {
    return Vec<T, 3>(-v.x, -v.y, -v.z);
}

template<typename T>
Vec<T, 3> operator +(const Vec<T, 3> &v, const Vec<T, 3> &w) {
    return Vec<T, 3>(v.x + w.x, v.y + w.y, v.z + w.z);
}

template<typename T>
Vec<T, 3> operator -(const Vec<T, 3> &v, const Vec<T, 3> &w) {
    return Vec<T, 3>(v.x - w.x, v.y - w.y, v.z - w.z);
}

template<typename T>
Vec<T, 3> operator *(const Vec<T, 3> &v, T r) {
    return Vec<T, 3>(v.x * r, v.y * r, v.z * r);
}

template<typename T>
Vec<T, 3> operator *(T r, const Vec<T, 3> &v) {
    return Vec<T, 3>(r * v.x, r * v.y, r * v.z);
}

template<typename T>
Vec<T, 3> operator /(const Vec<T, 3> &v, T r) {
    return Vec<T, 3>(v.x / r, v.y / r, v.z / r);
}

template<typename T>
T dot(const Vec<T, 3> &v, const Vec<T, 3> &w) {
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

template<typename T>
Vec<T, 3> cross(const Vec<T, 3> &v, const Vec<T, 3> &w) {
    return Vec<T, 3> (
        v.y * w.z - v.z * w.y,
        v.z * w.x - v.x * w.z,
        v.x * w.y - v.y * w.x
    );
}

} // namespace gmq