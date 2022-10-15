#pragma once

#include "macro.h"

namespace gmq {

struct Color {
    Float r;
    Float g;
    Float b;
    Color();
    Color(Float c);
    Color(Float r, Float g, Float b);

    Color &operator +=(const Color &color);
    Color &operator +=(Float scalar);
};

Color operator +(const Color &c1, const Color &c2);
Color operator -(const Color &c1, const Color &c2);
Color operator *(const Color &c, Float scalar);
Color operator /(const Color &c, Float scalar);

} // namespace gmq