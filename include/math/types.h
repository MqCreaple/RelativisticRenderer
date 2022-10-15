#pragma once

#include "macro.h"
#include "math/vec/Vec.h"
#include "math/vec/Vec2.h"
#include "math/vec/Vec3.h"
#include "math/vec/Vec4.h"
#include "math/vec/LVec.h"
#include "math/mat/Mat.h"
#include "math/mat/Mat4x4.h"

namespace gmq {

using Vec2 = Vec<Float, 2>;
using Vec3 = Vec<Float, 3>;
using Vec4 = Vec<Float, 4>;
using LVec4 = LVec<Float>;

using IVec2 = Vec<Int, 2>;
using IVec3 = Vec<Int, 3>;
using IVec4 = Vec<Int, 4>;

using Mat4x4 = Mat<Float, 4, 4>;

} // namespace gmq