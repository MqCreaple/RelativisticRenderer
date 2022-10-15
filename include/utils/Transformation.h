#pragma once

#include "math/math.h"
#include "utils/constants.h"
#include "utils/Ray.h"
#include <utility>

namespace gmq {

/**
 * @brief A transformation in Minkowski space.
 */
class Transformation {
public:
    static const Transformation WORLD;

    static Mat4x4 getLorentzMatrix(const Vec3 &vFrame);
    /**
     * @brief Transform an event in world reference frame 
     * @param vFrame velocity of reference frame relative to the world
     * @param eWorld event in world reference frame
     * @return LVec4 event in the other reference frame
     */
    static LVec4 transform(const Vec3 &vFrame, const LVec4 &eWorld);
    static Vec3 transformVelocity(const Vec3 &vFrame, const Vec3 &vWorld);

    Transformation(const LVec4 &origin, const Vec3 &velocity);
    Transformation(const Vec3 &velocity);

    LVec4 getOrigin() const;
    Vec3 getVelocity() const;
    /**
     * @brief Get the unit velocity (velocity divided by light speed).
     * @return Vec3 Unit velocity
     */
    Vec3 getUnitVelocity() const;

    Float getGamma() const;

    /**
     * @brief Transform an event in world reference frame to local reference frame
     * @param world event represented in world coordinate
     * @return Vec4 same event in local coordinate
     */
    LVec4 toLocal(const LVec4 &world) const;
    /**
     * @brief Transform an event in local reference frame to world reference frame
     * @param local event represented in local coordinate
     * @return Vec4 same event in world coordinate
     */
    LVec4 toWorld(const LVec4 &local) const;

#if RENDERER_TRANSFORM_INTENSITY
    /**
     * @brief Transform a ray in world reference frame to local reference frame
     * @param ray Ray in world reference frame
     * @return std::pair<Ray, Float> first: ray in local reference frame. second: factor of intensity change.
     * Radiance of ray in local reference frame is the radiance in world reference frame multiplied by the factor.
     */
    std::pair<Ray, Float> toLocal(const Ray &ray) const;
    /**
     * @brief Transform a ray in local reference frame to world reference frame
     * @param ray Ray in local reference frame
     * @return std::pair<Ray, Float> first: ray in world reference frame. second: factor of intensity change.
     * Radiance of ray in world reference frame is the radiance in local reference frame multiplied by the factor.
     */
    std::pair<Ray, Float> toWorld(const Ray &ray) const;
#else // RENDERER_TRANSFORM_INTENSITY
    Ray toLocal(const Ray &ray) const;
    Ray toWorld(const Ray &ray) const;
#endif // RENDERER_TRANSFORM_INTENSITY

private:
    LVec4 origin;          // world coordinate of point (0, 0, 0, 0) in local reference frame
    Vec3 velocity;         // reference frame's velocity relative to the world
};

} // namespace gmq