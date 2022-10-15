#include "components/Camera.h"

namespace gmq {

Camera::Camera(const Vec3 &center): Object(LVec4(0, center), Vec3()) {}

Camera::Camera(const LVec4 &origin, const Vec3 &velocity): Object(origin, velocity) {}

} // namespace gmq