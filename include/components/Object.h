#pragma once

#include "math/math.h"
#include "utils/Transformation.h"

namespace gmq {

class Object {
public:
    Object();
    Object(const Transformation &tr);
    Object(const LVec4 &origin, const Vec3 &velocity);

    Transformation getTransformation() const;
private:
    Transformation transformation;
};

} // namespace gmq