#pragma once

#include "components/Object.h"

namespace gmq {

class PointLight: public Object {
public:
    PointLight(Float intensity);
    /**
     * @brief Construct a point light that is stationary in world reference frame.
     * @param world position in world reference frame.
     * @param intensity intensity of the light
     */
    PointLight(const Vec3 &world, Float intensity);
    PointLight(const Transformation &transformation, Float intensity);

    Float getIntensity() const;
private:
    Float intensity;
};

} // namespace gmq