#pragma once

#include "components/Object.h"
#include "material/Material.h"
#include <optional>
#include <memory>

namespace gmq {

class VisibleObject: public Object {
public:
    static const Float DEFAULT_T_MIN;
    static const Float DEFAULT_T_MAX;

    VisibleObject(const Transformation &transformation, const std::shared_ptr<Material> &material);
    VisibleObject(const LVec4 &origin, const Vec3 &velocity, const std::shared_ptr<Material> &material);

    std::shared_ptr<const Material> getMaterial() const;

    /**
     * @brief Information about intersection between a ray and the object in the local reference frame.
     */
    struct IntersectionResult {
        Float distance;      // spacial distance from ray's origin to the intersection (should be a negative number).
        LVec4 intersection;  // position of the intersection
        Vec3 normal;         // normal vector on the intersection. If the object is closed, normal vector should point outward.
        IntersectionResult(Float distance, const LVec4 &intersection, const Vec3 &normal);
    };
    /**
     * @brief Find the intersection of ray and the object.
     * @param ray a ray pointing away from the object (in local reference frame)
     * @return std::optional<LocalIntersectResult> result of intersection.
     */
    virtual std::optional<IntersectionResult> intersect(const Ray &ray, Float tMin=DEFAULT_T_MIN, Float tMax=DEFAULT_T_MAX) const = 0;
protected:
    std::shared_ptr<const Material> material;
};

} // namespace gmq