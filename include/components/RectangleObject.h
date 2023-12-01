#pragma once

#include "components/VisibleObject.h"
#include <cmath>

namespace gmq {
/**
 * @brief Rectangle surface object.
 * The default surface is on the xOy plane with center at the origin. Its normal vector is [0, 0, 1].
 */
class RectangleObject: public VisibleObject {
public:
    RectangleObject (
        const Transformation &transformation,
        const std::shared_ptr<Material> material,
        Float width,
        Float height
    );

    std::optional<IntersectionResult> intersect(const Ray& ray, Float tMin=DEFAULT_T_MIN, Float tMax=DEFAULT_T_MAX) const override;
private:
    float halfX;
    float halfY;
};

} // namespace gmq