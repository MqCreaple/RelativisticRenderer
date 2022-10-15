#pragma once

#include "utils/Ray.h"
#include "utils/Color.h"
#include "utils/Random.h"
#include "utils/PPMImage.h"
#include "components/Camera.h"
#include "components/VisibleObject.h"
#include "components/PointLight.h"
#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <SDL2/SDL.h>

namespace gmq {

class Renderer {
public:
    static const Int DEFAULT_TRACING_DEPTH;
    static const Int DEFAULT_SAMPLE_NUMBER;

    Renderer(Int width, Int height, Camera *camera);

    /**
     * @brief Convert position in fragment coordinate to image coordinate (integer coordinate of pixel).
     * @param fragment Fragment coordinate. -1 <= x, y <= 1.
     * @return IVec2 Image coordinate. 0 <= x < windowWidth, 0 <= y < windowHeight.
     */
    IVec2 toImage(const Vec2 &fragment) const;
    std::pair<Vec2, Vec2> toFragment(const IVec2 &image) const;

    void addObject(const std::shared_ptr<VisibleObject> &object);
    void addLight(const std::shared_ptr<PointLight> &light);

    struct IntersectResult {
        std::shared_ptr<VisibleObject> object;
        LVec4 intersection;
        Ray rayLocal;
        Float distance;
#if RENDERER_TRANSFORM_INTENSITY
        /**
         * Factor of ray's intensity change.
         * The intensity of same ray in object's local reference frame is the ray's intensity in world frame multiplied by this factor.
         */
        Float intensityChange;
#endif
        VisibleObject::IntersectionResult localResult;
        IntersectResult (
            std::shared_ptr<VisibleObject> object,
            const LVec4 &intersection,
            const Ray &rayLocal,
            Float distance,
            Float ic,
            const VisibleObject::IntersectionResult &result
        );
    }; // struct IntersectResult

    /**
     * @brief Find intersection of a ray and the list of objects.
     * @param ray Ray (in world reference frame)
     * @param isPositive If this flag is set, the function only searches for intersection after the ray's origin.
     * Otherwise, the function only searches for intersection before ray's origin. 
     * @return std::optional<IntersectResult> result of intersection
     */
    std::optional<IntersectResult> intersect(const Ray &ray, bool isPositive) const;

    void render(Float time);

    void renderToImage(const string &fileName, Float time);
private:
    // scene
    std::unique_ptr<Camera> primaryCamera;
    std::vector<std::shared_ptr<VisibleObject>> objects;
    std::vector<std::shared_ptr<PointLight>> pointLights;

    // ray tracing
    Int tracingDepth;
    Int sampleNumber;
    /**
     * @brief Trace the intensity of a ray.
     * @param ray A ray (in world reference frame).
     * @param depth Current tracing depth.
     * @return Float Intensity of the ray (in world reference frame).
     */
    Float traceIndirect(const Ray &ray, Int depth) const;

    /**
     * @brief Trace the direct light intensity on a point with given output direction.
     * @param result A result of ray-object intersection.
     * @param dirOut Outward direction (in local reference frame).
     * @return Float Total intensity from all known light source to the output direction (in object's local reference frame).
     */
    Float traceDirect(const IntersectResult &result, const Vec3 &dirOut) const;

    // graphics
    SDL_Window *window;
    SDL_Surface *surface;
    void initWindow(Int width, Int height);
    void setPixel(Int x, Int y, const Color &c);
    void freeWindow();
    void update();
};

} // namespace gmq