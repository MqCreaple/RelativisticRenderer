#include "components/PointLight.h"

namespace gmq {

PointLight::PointLight(Float intensity): Object(), intensity(intensity) {}
PointLight::PointLight(const Vec3 &world, Float intensity): Object(LVec4(0, world), Vec3()), intensity(intensity) {}
PointLight::PointLight(const Transformation &transformation, Float intensity)
    : Object(transformation), intensity(intensity) {}

Float PointLight::getIntensity() const {
    return intensity;
}

} // namespace gmq