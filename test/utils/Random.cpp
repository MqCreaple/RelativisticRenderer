#include "TestInclude.h"
#include "RelativisticRenderer.h"
using namespace gmq;

int main() {
    const int testNumber = 1000;
    for(int i = 0; i < testNumber; i++) {
        CHECK_EPSILON_EQU(Random::unitVec().length(), 1, 1e-7);
    }
    for(int i = 0; i < testNumber; i++) {
        Vec3 vec = Random::vecOnHemisphere();
        CHECK_EPSILON_EQU(vec.length(), 1, 1e-7);
        CHECK(vec.z >= 0);
    }
    Vec3 v1(0, 1, 0);
    for(int i = 0; i < testNumber; i++) {
        Vec3 rnd = Random::vecOnHemisphere(v1);
        CHECK_EPSILON_EQU(rnd.length(), v1.length(), 1e-7);
        CHECK(rnd.y >= 0);
    }
    Vec3 v2(0, 0, 2);
    for(int i = 0; i < testNumber; i++) {
        Vec3 rnd = Random::vecOnHemisphere(v2);
        CHECK_EPSILON_EQU(rnd.length(), v2.length(), 1e-7);
        CHECK(rnd.z > 0);
    }
}