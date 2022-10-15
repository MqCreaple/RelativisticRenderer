#include "material/DiffuseMaterial.h"

namespace gmq {

DiffuseMaterial::DiffuseMaterial(Float color): color(color) {}

Float DiffuseMaterial::f(const Vec3 &normal, const Vec3 &dirIn, const Vec3 &dirOut) const {
    return dot(normal, dirIn) >= 0 && dot(normal, dirOut) >= 0;
}

std::pair<Vec3, Float> DiffuseMaterial::sample(const Vec3 &normal, const Vec3 &outDir) const {
    return std::make_pair(Random::vecOnHemisphere(normal), color);
}

} // namespace gmq