#pragma once

#include "math/vec/Vec.h"
#include "math/vec/Vec3.h"

namespace gmq {

template<typename T>
class Vec<T, 4> {
public:
    union {
        T w, t;
    };
    T x;
    T y;
    T z;

    Vec(): w(0), x(0), y(0), z(0) {}
    Vec(T scalar): w(scalar), x(scalar), y(scalar), z(scalar) {}
    Vec(T w, T x, T y, T z): w(w), x(x), y(y), z(z) {}
    Vec(T w, const Vec<T, 3> &v): w(w), x(v.x), y(v.y), z(v.z) {}
    
    template<typename W, typename X, typename Y, typename Z>
    Vec(W w, X x, Y y, Z z): w(static_cast<T>(w)), x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)) {}

    Vec(const Vec &other): w(other.w), x(other.x), y(other.y), z(other.z) {}

    Vec<T, 3> getXYZ() const {
        return Vec<T, 3>(x, y, z);
    }

    virtual T length() const {
        return sqrt(w * w + x * x + y * y + z * z);
    }
    virtual T sqLength() const {
        return w * w + x * x + y * y + z * z;
    }
    virtual Vec<T, 4> normalized() const {
        T len = length();
        return Vec<T, 4>(w / len, x / len, y / len, z / len);
    }
    T operator [](LengthT index) const {
        switch(index) {
            case 0:
                return w;
            case 1:
                return x;
            case 2:
                return y;
            case 3:
            default:
                return z;
        }
    }
    Vec &operator +=(const Vec &vec) {
        this->w += vec.w;
        this->x += vec.x;
        this->y += vec.y;
        this->z += vec.z;
        return *this;
    }
    Vec &operator -=(const Vec &vec) {
        this->w -= vec.w;
        this->x -= vec.x;
        this->y -= vec.y;
        this->z -= vec.z;
        return *this;
    }
    Vec &operator *=(T scalar) {
        this->w *= scalar;
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }
    Vec &operator /=(T scalar) {
        this->w /= scalar;
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        return *this;
    }
private:
};

template<typename T>
bool isZero(const Vec<T, 4> &v) {
    return v.w == 0 && v.x == 0 && v.y == 0 && v.z == 0;
}

template<typename T>
bool operator ==(const Vec<T, 4> &v, const Vec<T, 4> &w) {
    return (v.w == w.w) && (v.x == w.x) && (v.y == w.y) && (v.z == w.z);
}

template<typename T>
bool operator != (const Vec<T, 4> &v, const Vec<T, 4> &w) {
    return (v.w != w.w) || (v.x != w.x) || (v.y != w.y) || (v.z != w.z);
}

template<typename T>
Vec<T, 4> operator -(const Vec<T, 4> &v) {
    return Vec<T, 4>(-v.w, -v.x, -v.y, -v.z);
}

template<typename T>
Vec<T, 4> operator +(const Vec<T, 4> &v, const Vec<T, 4> &w) {
    return Vec<T, 4>(v.w + w.w, v.x + w.x, v.y + w.y, v.z + w.z);
}

template<typename T>
Vec<T, 4> operator -(const Vec<T, 4> &v, const Vec<T, 4> &w) {
    return Vec<T, 4>(v.w - w.w, v.x - w.x, v.y - w.y, v.z - w.z);
}

template<typename T>
Vec<T, 4> operator *(const Vec<T, 4> &v, T r) {
    return Vec<T, 4>(v.w * r, v.x * r, v.y * r, v.z * r);
}

template<typename T>
Vec<T, 4> operator *(T r, const Vec<T, 4> &v) {
    return Vec<T, 4>(r * v.w, r * v.x, r * v.y, r * v.z);
}

template<typename T>
Vec<T, 4> operator /(const Vec<T, 4> &v, T r) {
    return Vec<T, 4>(v.w / r, v.x / r, v.y / r, v.z / r);
}

template<typename T>
T dot(const Vec<T, 4> &v, const Vec<T, 4> &w) {
    return v.w * w.w + v.x * w.x + v.y * w.y + v.z * w.z;
}

} // namespace gmq