#include "TestInclude.h"
#include "RelativisticRenderer.h"
using namespace gmq;

int main(int argc, char *argv[]) {
    // Test 1: stationary sphere
    SphereObject object(Transformation::WORLD, Material::DEFAULT, 1.5);
    CHECK_EPSILON_EQU(object.getRadius(), 1.5, 1e-7);
    Ray ray(LVec4(1, 2, 2, 0), Vec3(1, 1, 0));
    auto intersection = object.intersect(ray);
    CHECK(intersection.has_value());
    CHECK_EPSILON_EQU(ray.atDistance(intersection.value().distance).getXYZ().length(), object.getRadius(), 1e-7);
    ray = Ray(LVec4(1, 2, 2, 0), Vec3(1, -1, 0));
    intersection = object.intersect(ray);
    CHECK(!intersection.has_value());

    // Test 2: moving sphere
    object = SphereObject(LVec4(), Vec3(0.5, 0, 0), Material::DEFAULT, 1.5);
    ray = Ray(LVec4(sqrt(3), 1, 1, 1), Vec3(1, 1, 1));
    Ray rayLocal = object.getTransformation().toLocal(ray).first;
    intersection = object.intersect(rayLocal);
    CHECK(intersection.has_value());
    Float iWorld = intersection.value().distance / (object.getTransformation().getGamma() * (1 - dot(object.getTransformation().getVelocity(), ray.getDirection()) / lightSpeed));
    LVec4 e1Local = rayLocal.getOrigin();
    LVec4 e2Local = rayLocal.atDistance(intersection.value().distance);
    LVec4 e1World = ray.getOrigin();
    LVec4 e2World = ray.atDistance(iWorld);
    CHECK_EPSILON_EQU(object.getTransformation().toWorld(e1Local), e1World, 1e-7);
    CHECK_EPSILON_EQU(object.getTransformation().toWorld(e2Local), e2World, 1e-7);
}