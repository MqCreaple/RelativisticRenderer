#pragma once

#include "components/Camera.h"

namespace gmq {

class PerspectiveCamera: public Camera {
public:
    PerspectiveCamera(const Vec3 &position, Float focus);
    PerspectiveCamera(const LVec4 &origin, const Vec3 &velocity, Float focus);

    Ray getRay(const Vec2 &vec, Float t) const override;
    Float getFocus() const;
private:
    Float focus;
};

} // namespace gmq
