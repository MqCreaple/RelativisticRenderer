#include "utils/Ray.h"

namespace gmq {

Ray::Ray(): origin(), direction(1, 0, 0) {}
Ray::Ray(const LVec4 &origin, const Vec3 &velocity): origin(origin), direction(velocity.normalized()) {}

LVec4 Ray::atTime(Float t) const {
    return LVec4(origin.t + lightSpeed * t, origin.getXYZ() + direction * lightSpeed * t);
}

LVec4 Ray::atDistance(Float dist) const {
    return LVec4(origin.t + dist, origin.getXYZ() + direction * dist);
}

LVec4 Ray::getOrigin() const {
    return origin;
}
Vec3 Ray::getDirection() const {
    return direction;
}
Vec3 Ray::getVelocity() const {
    return lightSpeed * direction;
}

} // namespace gmq