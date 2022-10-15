#pragma once

#include "math/vec/Vec.h"
#include "math/vec/Vec3.h"
#include "math/vec/Vec4.h"
#include "math/vec/LVec.h"
#include <iostream>

namespace gmq {

template<typename T>
std::ostream &operator <<(std::ostream &os, const Vec<T, 3> &v) {
    os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
    return os;
}

template<typename T>
std::ostream &operator <<(std::ostream &os, const Vec<T, 4> &v) {
    os << "[" << v.w << ", " << v.x << ", " << v.y << ", " << v.z << "]";
    return os;
}

} // namespace gmq