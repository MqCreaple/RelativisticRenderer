#include "components/SphereObject.h"

namespace gmq {

SphereObject::SphereObject(const LVec4 &initial, const Vec3 &velocity, const std::shared_ptr<Material> &material, Float radius)
    : VisibleObject(initial, velocity, material), radius(radius) {}

SphereObject::SphereObject(const Transformation &transformation, const std::shared_ptr<Material> &material, Float radius)
    : VisibleObject(transformation, material), radius(radius) {}

Float SphereObject::getRadius() const {
    return radius;
}

std::optional<VisibleObject::IntersectionResult> SphereObject::intersect(const Ray &ray, Float tMin, Float tMax) const {
    Vec3 r0 = ray.getOrigin().getXYZ();
    Float hb = dot(r0, ray.getDirection());            // half of b
    Float c = r0.sqLength() - radius * radius;
    Float qDelta = hb * hb - c;                        // 1/4 of Delta (b^2 - 4ac)
    if(qDelta < 0) {
        return std::nullopt;
    }
    Float t = -hb + sqrt(qDelta);
    if(t > DEFAULT_T_MAX) {
        t = -hb - sqrt(qDelta);
    }
    if(t < tMin || t > tMax) {
        return std::nullopt;
    }
    return IntersectionResult(t, ray.atDistance(t), ray.atDistance(t).getXYZ().normalized());
}

} // namespace gmq