#include "TestInclude.h"
#include "RelativisticRenderer.h"
using namespace gmq;

int main(int argc, char *argv[]) {
    Vec4 v(1, 2, 3, 4), w(5, Vec3(6, 7, 8));
    CHECK_EPSILON_EQU(v.length(), sqrt(30), 1e-7);
    CHECK_EPSILON_EQU(v.normalized(), Vec4(1 / sqrt(30), 2 / sqrt(30), 3 / sqrt(30), 4 / sqrt(30)), 1e-7);
    CHECK_EPSILON_EQU(-v, Vec4(-1, -2, -3, -4), 1e-7);
    CHECK_EPSILON_EQU(v + w, Vec4(6, 8, 10, 12), 1e-7);
    CHECK_EPSILON_EQU(v - w, Vec4(-4), 1e-7);
    CHECK_EPSILON_EQU(-1.5 * v, Vec4(-1.5, -3, -4.5, -6), 1e-7);
    CHECK_EPSILON_EQU(dot(v, w), 70, 1e-7);
    CHECK_EPSILON_EQU(v.getXYZ(), Vec3(2, 3, 4), 1e-7);
}