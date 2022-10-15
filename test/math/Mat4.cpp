#include "TestInclude.h"
#include "RelativisticRenderer.h"
using namespace gmq;

int main() {
    Mat4x4 m1(1,  2,  3,  4,
               5,  6,  7,  8,
               9,  10, 11, 12,
               13, 14, 15, 16);
    Vec4 v(1, 2, 3, 4);
    CHECK_EPSILON_EQU(m1 * v, Vec4(30, 70, 110, 150), 1e-7f);
    Mat4x4 m2(1, 4, 6, 5,
              2, 8, 3, 7,
              3, 9, 6, 3,
              1, 5, 4, 2);
    CHECK_EPSILON_EQU((m1 * m2)[0], Vec4(18, 46, 74, 102), 1e-7f);
    CHECK_EPSILON_EQU((m1 * m2)[1], Vec4(67, 171, 275, 379), 1e-7f);
    CHECK_EPSILON_EQU((m1 * m2)[2], Vec4(46, 122, 198, 274), 1e-7f);
    CHECK_EPSILON_EQU((m1 * m2)[3], Vec4(36, 104, 172, 240), 1e-7f);

    CHECK_EPSILON_EQU((m1 + m2)[0], Vec4(2, 7, 12, 14), 1e-7f);
    CHECK_EPSILON_EQU((m1 + m2)[1], Vec4(6, 14, 19, 19), 1e-7f);
    CHECK_EPSILON_EQU((m1 + m2)[2], Vec4(9, 10, 17, 19), 1e-7f);
    CHECK_EPSILON_EQU((m1 + m2)[3], Vec4(9, 15, 15, 18), 1e-7f);
}