#pragma once

#include "components/Object.h"
#include "utils/Ray.h"

namespace gmq {

/**
 * @brief General camera class
 */
class Camera: public Object {
public:
    Camera(const Vec3 &center);
    Camera(const LVec4 &origin, const Vec3 &velocity);

    /**
     * @brief Get an inward ray on fragment coordinate (x, y).
     * It is guaranteed that x and y are in range [-1, 1].
     * @param vec fragment coordinate of the pixel
     * @param t time (in local reference frame)
     * @return Ray an inward ray (in local reference frame)
     */
    virtual Ray getRay(const Vec2 &vec, Float t) const = 0;
private:
};

} // namespace gmq