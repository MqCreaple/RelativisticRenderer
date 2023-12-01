#include "TestInclude.h"
#include "RelativisticRenderer.h"
using namespace gmq;

int main(int argc, char *argv[]) {
    // Test 1: a high speed (0.6c) inertial frame, and Lorentz transformation
    Transformation t(Vec3(0.6 * lightSpeed, 0, 0));
    Mat4x4 l = Transformation::getLorentzMatrix(t.getVelocity());
    CHECK_EPSILON_EQU(l[0], Vec4(1.25, -0.75, 0, 0), 1e-7);
    CHECK_EPSILON_EQU(l[1], Vec4(-0.75, 1.25, 0, 0), 1e-7);
    CHECK_EPSILON_EQU(l[2], Vec4(0, 0, 1, 0), 1e-7f);
    CHECK_EPSILON_EQU(l[3], Vec4(0, 0, 0, 1), 1e-7f);
    LVec4 event(1, 1, 1, 1);
    LVec4 local = t.toLocal(event);
    CHECK_EPSILON_EQU(local, Vec4(0.5, 0.5, 1, 1), 1e-7f);
    LVec4 world = t.toWorld(local);
    CHECK_EPSILON_EQU(world, event, 1e-7f);
    Ray ray(LVec4(), Vec3(0, 1, 0));
    CHECK_EPSILON_EQU(t.toLocal(ray).first.getOrigin(), LVec4(0, 0, 0, 0), 1e-7);
    CHECK_EPSILON_EQU(t.toLocal(ray).first.getDirection(), Vec3(-0.6, 0.8, 0), 1e-7);
    CHECK_EPSILON_EQU(t.toWorld(t.toLocal(ray).first).first.getDirection(), ray.getDirection(), 1e-7);

    // Test 2: a low speed (0.005c) inertial frame, and approximation with Galileo transformation
    Transformation t2(Vec3(0.005 * lightSpeed, 0, 0));
    event = LVec4(2, 3, 4, 5);
    CHECK_EPSILON_EQU(t2.toLocal(event), Vec4(2, 2.99, 4, 5), 0.02);
    CHECK_EPSILON_EQU(t2.toWorld(t2.toLocal(event)), event, 1e-7f);
    Vec3 velocity = Vec3(0.6, 0.8, 0);
    CHECK_EPSILON_EQU(Transformation::transformVelocity(t2.getVelocity(), velocity), Vec3(0.6005, 0.8, 0), 0.02);

    // Test 3: translation and Lorentz transformation
    Transformation t3(LVec4(1, 2, 3, 4), Vec3(0.2, 0.2, 0));
    event = LVec4(1, 2, 3, 4);
    CHECK_EPSILON_EQU(t3.toLocal(event), LVec4(0, 0, 0, 0), 1e-7f);

    // Test 4: WORLD transformation
    event = LVec4(1, 4, 2, 5);
    CHECK_EPSILON_EQU(Transformation::WORLD.toLocal(event), event, 1e-7);
    velocity = Vec3(0.2, 0.3, -0.4);
    CHECK_EPSILON_EQU(Transformation::transformVelocity(Transformation::WORLD.getVelocity(), velocity), velocity, 1e-7);

#if RENDERER_TRANSFORM_INTENSITY
    // Test 5: factor of intensity change
    ray = Ray(LVec4(0, 0, 0, 0), Vec3(0.1, -0.2, 0.3));
    auto p = t3.toLocal(ray);
    auto q = t3.toWorld(p.first);
    CHECK_EPSILON_EQU(q.first.getOrigin(), ray.getOrigin(), 1e-7);
    CHECK_EPSILON_EQU(q.first.getDirection(), ray.getDirection(), 1e-7);
    CHECK(p.second > 1);
    CHECK_EPSILON_EQU(p.second * q.second, 1, 1e-7);
    ray = Ray(LVec4(0, 0, 0, 0), Vec3(0.2, 0.2, 0));           // a ray with same direction as relative speed between reference frames
    p = t3.toLocal(ray);
    q = t3.toWorld(p.first);
    CHECK_EPSILON_EQU(q.first.getOrigin(), ray.getOrigin(), 1e-7);
    CHECK_EPSILON_EQU(q.first.getDirection(), ray.getDirection(), 1e-7);
    CHECK(p.second < 1);
    CHECK_EPSILON_EQU(p.second * q.second, 1, 1e-7);
#endif
}