#include "components/VisibleObject.h"

namespace gmq {

const Float VisibleObject::DEFAULT_T_MIN = -1e6;
const Float VisibleObject::DEFAULT_T_MAX = -1e-6;

VisibleObject::VisibleObject(const Transformation &transformation, const std::shared_ptr<Material> &material): Object(transformation), material(material) {}
VisibleObject::VisibleObject(const LVec4 &origin, const Vec3 &velocity, const std::shared_ptr<Material> &material): Object(origin, velocity), material(material) {}

std::shared_ptr<const Material> VisibleObject::getMaterial() const {
    return material;
}

VisibleObject::IntersectionResult::IntersectionResult(Float distance, const LVec4 &intersection, const Vec3 &normal)
    : distance(distance), intersection(intersection), normal(normal) {}

} // namespace gmq