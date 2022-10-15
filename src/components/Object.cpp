#include "components/Object.h"

namespace gmq {

Object::Object(): transformation(Transformation::WORLD) {}

Object::Object(const Transformation &tr): transformation(tr) {}

Object::Object(const LVec4 &origin, const Vec3 &velocity): transformation(origin, velocity) {}

Transformation Object::getTransformation() const {
    return transformation;
}

} // namespace gmq