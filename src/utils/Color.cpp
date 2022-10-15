#include "utils/Color.h"

namespace gmq {

Color::Color(): r(0), g(0), b(0) {}
Color::Color(Float c): r(c), g(c), b(c) {}
Color::Color(Float r, Float g, Float b): r(r), g(g), b(b) {}

Color &Color::operator +=(const Color &color) {
    r += color.r;
    g += color.g;
    b += color.b;
    return *this;
}

Color &Color::operator +=(Float scalar) {
    r += scalar;
    g += scalar;
    b += scalar;
    return *this;
}

Color operator +(const Color &c1, const Color &c2) {
    return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

Color operator -(const Color &c1, const Color &c2) {
    return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

Color operator *(const Color &c, Float scalar) {
    return Color(c.r * scalar, c.g * scalar, c.b * scalar);
}

Color operator /(const Color &c, Float scalar) {
    return Color(c.r / scalar, c.g / scalar, c.b / scalar);
}

} // namespace gmq