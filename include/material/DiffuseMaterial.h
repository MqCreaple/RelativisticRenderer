#pragma once

#include "material/Material.h"
#include "utils/Random.h"

namespace gmq {

class DiffuseMaterial: public Material {
public:
    DiffuseMaterial(Float color = 1.0);
    Float f(const Vec3 &normal, const Vec3 &dirIn, const Vec3 &dirOut) const override;
    std::pair<Vec3, Float> sample(const Vec3 &normal, const Vec3 &dirOut) const override;
private:
    Float color;
};

} //namespace gmq