#include "components/PerspectiveCamera.h"

namespace gmq {

PerspectiveCamera::PerspectiveCamera(const Vec3 &center, Float focus): Camera(center), focus(focus) {}
PerspectiveCamera::PerspectiveCamera(const LVec4 &origin, const Vec3 &velocity, Float focus): Camera(origin, velocity), focus(focus) {}

Ray PerspectiveCamera::getRay(const Vec2 &vec, Float t) const {
    return Ray(LVec4(t, 0, 0, focus), Vec3(-vec.x, -vec.y, focus));
}

Float PerspectiveCamera::getFocus() const {
    return focus;
}

} // namespace gmq