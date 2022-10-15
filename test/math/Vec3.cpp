#include "TestInclude.h"
#include "RelativisticRenderer.h"
using namespace gmq;

int main() {
    Vec3 v(1, 2, 3), w(4, 5, 6);
    CHECK_EPSILON_EQU(v.length(), sqrt(14), 1e-7);
    CHECK_EPSILON_EQU(-v, Vec3(-1, -2, -3), 1e-7);
    CHECK_EPSILON_EQU(v.normalized(), Vec3(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)), 1e-7);
    CHECK_EPSILON_EQU(v + w, Vec3(5, 7, 9), 1e-7);
    CHECK_EPSILON_EQU(v - w, Vec3(-3), 1e-7);
    CHECK_EPSILON_EQU(dot(v, w), 32, 1e-7);
    CHECK_EPSILON_EQU(cross(v, w), Vec3(-3, 6, -3), 1e-7);
    v += Vec3(2, 1, -1);
    CHECK_EPSILON_EQU(v, Vec3(3, 3, 2), 1e-7);
}