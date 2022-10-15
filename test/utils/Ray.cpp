#include "TestInclude.h"
#include "RelativisticRenderer.h"
using namespace gmq;

int main() {
    Ray ray(LVec4(1, -1, 2, -3), Vec3(3, 4, 0));
    CHECK_EPSILON_EQU(ray.getDirection().length(), 1, 1e-7);
    CHECK_EPSILON_EQU(ray.getVelocity().length(), lightSpeed, 1e-7);
    CHECK_EPSILON_EQU(ray.atDistance(5), LVec4(6, 2, 6, -3), 1e-7);
}