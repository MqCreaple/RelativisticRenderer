#pragma once

#include "math/math.h"
#include "utils/constants.h"

namespace gmq {

class Ray {
public:
    Ray();
    Ray(const LVec4 &origin, const Vec3 &velocity);

    /**
     * @brief Get the position of ray after time @c t.
     * The ray always moves forward in time.
     * @param t time
     * @return LVec4 position of ray at time @c t.
     */
    LVec4 atTime(Float t) const;
    /**
     * @brief Get the position of ray at spacial distance @c dist away from the origin.
     * @param dist spacial distance
     * @return LVec4 position of ray
     */
    LVec4 atDistance(Float dist) const;

    LVec4 getOrigin() const;
    Vec3 getDirection() const;
    /**
     * @brief Get the ray's velocity vector.
     * Equivalent to @c direction multiplied by light speed.
     * @return Vec3 velocity vector
     */
    Vec3 getVelocity() const;
private:
    LVec4 origin;   // Ray's origin point. A 4-vector in Minkowski space.
    Vec3 direction; // Ray's direction. Always have magnitude of 1.
                    // The ray's velocity equals direction vector multiplied by light speed.
};

} // namespace gmq