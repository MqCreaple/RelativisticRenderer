#include "utils/Transformation.h"

namespace gmq {

const Transformation Transformation::WORLD = Transformation(LVec4(), Vec3());

Mat4x4 Transformation::getLorentzMatrix(const Vec3 &vFrame) {
    Vec3 normal = vFrame.normalized();       // normalized velocity vector
    Vec3 reduced = vFrame / lightSpeed;      // v / c
    Float beta = reduced.length();           // ||v|| / c
    Float gamma = 1 / sqrt(1 - beta * beta); // 1 / sqrt(1 - v^2 / c^2)
    Float gamma1 = gamma - 1;
    return Mat4x4 (
        gamma, -gamma * reduced.x, -gamma * reduced.y, -gamma * reduced.z,
        -gamma * reduced.x, 1 + gamma1 * normal.x * normal.x, gamma1 * normal.x * normal.y, gamma1 * normal.x * normal.z,
        -gamma * reduced.y, gamma1 * normal.x * normal.y, 1 + gamma1 * normal.y * normal.y, gamma1 * normal.y * normal.z,
        -gamma * reduced.z, gamma1 * normal.x * normal.z, gamma1 * normal.y * normal.z, 1 + gamma1 * normal.z * normal.z
    );
}

LVec4 Transformation::transform(const Vec3 &vFrame, const LVec4 &eWorld) {
    if(isZero(vFrame)) {
        return eWorld;
    }
    Vec3 r = eWorld.getXYZ();                // space component of the vector
    Vec3 normal = vFrame.normalized();       // normalized velocity vector
    Vec3 reduced = vFrame / lightSpeed;      // v / c
    Float beta = reduced.length();           // ||v|| / c
    Float gamma = 1 / sqrt(1 - beta * beta); // 1 / sqrt(1 - v^2 / c^2)
    return LVec4 (
        gamma * eWorld.t - gamma * dot(reduced, r),
        -gamma * eWorld.t * reduced + r + (gamma - 1) * dot(r, normal) * normal
    );
}

Vec3 Transformation::transformVelocity(const Vec3 &vFrame, const Vec3 &vWorld) {
    Float factor = 1 / (1 - dot(vFrame, vWorld) / (lightSpeed * lightSpeed));
    Float gamma = 1 / sqrt(1 - (vFrame.length() * vFrame.length()) / (lightSpeed * lightSpeed));
    return factor * (vWorld / gamma - vFrame + (gamma / (lightSpeed * lightSpeed * (gamma + 1))) * dot(vFrame, vWorld) * vFrame);
}

Transformation::Transformation(const LVec4 &origin, const Vec3 &velocity): origin(origin), velocity(velocity) {}
Transformation::Transformation(const Vec3 &velocity): origin(), velocity(velocity) {}

LVec4 Transformation::getOrigin() const {
    return origin;
}

Vec3 Transformation::getVelocity() const {
   return velocity;
}

Vec3 Transformation::getUnitVelocity() const {
    return velocity / lightSpeed;
}

Float Transformation::getGamma() const {
    Float beta = velocity.length() / lightSpeed;
    return 1 / sqrt(1 - beta * beta);
}

LVec4 Transformation::toLocal(const LVec4 &world) const {
    return transform(velocity, world - origin);
}

LVec4 Transformation::toWorld(const LVec4 &local) const {
    return transform(-velocity, local) + origin;
}

#if RENDERER_TRANSFORM_INTENSITY
std::pair<Ray, Float> Transformation::toLocal(const Ray &ray) const {
    if(isZero(velocity)) {
        return std::make_pair(Ray(ray.getOrigin() - origin, ray.getDirection()), 1.0);
    }
    Ray ans(toLocal(ray.getOrigin()), transformVelocity(velocity, ray.getVelocity()) / lightSpeed);
    Float cosTheta = dot(ray.getDirection(), velocity.normalized());
    Float beta = velocity.length() / lightSpeed;
    Float gamma = 1 / sqrt(1 - beta * beta);
    Float factor = gamma * (1 - beta * cosTheta);
    return std::make_pair(ans, factor);
}
std::pair<Ray, Float> Transformation::toWorld(const Ray &ray) const {
    if(isZero(velocity)) {
        return std::make_pair(Ray(ray.getOrigin() + origin, ray.getDirection()), 1.0);
    }
    Ray ans(toWorld(ray.getOrigin()), transformVelocity(-velocity, ray.getVelocity()) / lightSpeed);
    Float cosTheta = dot(ray.getDirection(), -velocity.normalized());
    Float beta = velocity.length() / lightSpeed;
    Float gamma = 1 / sqrt(1 - beta * beta);
    Float factor = gamma * (1 - beta * cosTheta);
    return std::make_pair(ans, factor);
}
#else // RENDERER_TRANSFORM_INTENSITY
Ray Transformation::toLocal(const Ray &ray) const {
    return Ray(toLocal(ray.getOrigin()), transformVelocity(velocity, ray.getVelocity()));
}

Ray Transformation::toWorld(const Ray &ray) const {
    return Ray(toWorld(ray.getOrigin()), transformVelocity(-velocity, ray.getVelocity()));
}
#endif // RENDERER_TRANSFORM_INTENSITY

} // namespace gmq