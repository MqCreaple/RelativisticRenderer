#include "TestInclude.h"
#include "RelativisticRenderer.h"
#include <sstream>
using namespace gmq;

int main() {
    LVec4 lv(1, 2, 3, 4), lw(5, Vec3(6, 7, 8));
    CHECK_EPSILON_EQU(lv.length(), sqrt(28), 1e-7);
    CHECK_EPSILON_EQU(dot(lv, lw), 60, 1e-7);
    std::stringstream str;
    str << lv;
    CHECK_EQU(str.str(), "[1, 2, 3, 4]");
}