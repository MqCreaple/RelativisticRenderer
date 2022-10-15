#pragma once

#include "components/VisibleObject.h"

namespace gmq {

class SphereObject: public VisibleObject {
public:
    SphereObject(const Transformation &transformation, const std::shared_ptr<Material> &material, Float radius);
    SphereObject(const LVec4 &initial, const Vec3 &velocity, const std::shared_ptr<Material> &material, Float radius);

    Float getRadius() const;

    std::optional<IntersectionResult> intersect(const Ray &ray, Float tMin=DEFAULT_T_MIN, Float tMax=DEFAULT_T_MAX) const override;
private:
    Float radius;
};

} // namespace gmq