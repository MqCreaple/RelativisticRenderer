#include "components/RectangleObject.h"

namespace gmq {

RectangleObject::RectangleObject (
    const Transformation &transformation,
    const std::shared_ptr<Material> material,
    Float width,
    Float height
): VisibleObject(transformation, material), halfX(width / 2), halfY(height / 2) {}

std::optional<VisibleObject::IntersectionResult> RectangleObject::intersect(const Ray &ray, Float tMin, Float tMax) const {
    Float t = -ray.getOrigin().z / ray.getDirection().z;
    if(t < tMin || t > tMax) {
        return std::nullopt;
    }
    LVec4 intersection = ray.atDistance(t);
    if(std::abs(intersection.x) > halfX || std::abs(intersection.y) > halfY) {
        return std::nullopt;
    }
    return IntersectionResult(t, intersection, Vec3(0, 0, (ray.getOrigin().z > 0)? 1: -1));
}

} // namespace gmq