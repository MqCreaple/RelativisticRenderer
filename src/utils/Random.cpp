#include "utils/Random.h"

namespace gmq {

Int Random::randInt(Int iMin, Int iMax) {
    return rand() % (iMax - iMin) + iMin;
}

Float Random::uniform() {
    return rand() / (RAND_MAX * 1.0f);
}

Float Random::uniform(Float fmin, Float fmax) {
    return uniform() * (fmax - fmin) + fmin;
}

Vec3 Random::unitVec() {
    Float z = uniform(-1, 1);
    Float phi = 2 * M_PI * uniform();
    Float t = sqrt(1 - z * z);
    return Vec3(t * cos(phi), t * sin(phi), z);
}

Vec3 Random::vecOnHemisphere() {
    Float z = uniform();
    Float phi = 2 * M_PI * uniform();
    Float t = sqrt(1 - z * z);
    return Vec3(t * cos(phi), t * sin(phi), z);
}

Vec3 Random::vecOnHemisphere(const Vec3 &v) {
    Float z = uniform();
    Float phi = 2 * M_PI * uniform();
    Float t = sqrt(1 - z * z);
    Vec3 xUnit(v.x, -v.z, v.y);
    Vec3 yUnit = cross(v.normalized(), xUnit);
    return xUnit * t * cos(phi) + yUnit * t * sin(phi) + v * z;
}

} // namespace gmq