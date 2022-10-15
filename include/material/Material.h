#pragma once

#include "macro.h"
#include "math/math.h"
#include <utility>
#include <memory>

namespace gmq {

class Material {
public:
    static const std::shared_ptr<Material> DEFAULT;

    virtual Float f(const Vec3 &normal, const Vec3 &dirIn, const Vec3 &dirOut) const = 0;

    /**
     * @brief For a given ray's outward direction, returns a random inward ray and its attenuation factor.
     * The outward ray and inward ray are both in object's local reference frame.
     * Always assume vector [0, 0, 1] is the normal vector.
     * @param normal Normal vector of the surface.
     * @param dirOut Outward direction (in local reference frame)
     * @return std::pair<Float, Vec3> First: inward direction. Second: attenuation factor.
     */
    virtual std::pair<Vec3, Float> sample(const Vec3 &normal, const Vec3 &dirOut) const = 0;
private:
};

} // namespace gmq