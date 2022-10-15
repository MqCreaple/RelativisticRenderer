#include "renderer/Renderer.h"

namespace gmq {

const Int Renderer::DEFAULT_TRACING_DEPTH = 2;
const Int Renderer::DEFAULT_SAMPLE_NUMBER = 400;

Renderer::Renderer(Int width, Int height, Camera *camera)
    : primaryCamera(camera), objects(), tracingDepth(DEFAULT_TRACING_DEPTH), sampleNumber(DEFAULT_SAMPLE_NUMBER) {
    initWindow(width, height);
}

IVec2 Renderer::toImage(const Vec2 &frag) const {
    int x = (frag.x + 1) * surface->w / 2;
    int y = (frag.y + 1) * surface->h / 2;
    return IVec2(x, y);
}

std::pair<Vec2, Vec2> Renderer::toFragment(const IVec2 &image) const {
    Vec2 v1 (
        image.x * 2.0f / surface->w - 1,
        image.y * 2.0f / surface->h - 1
    );
    Vec2 v2 (
        (image.x + 1) * 2.0f / surface->w - 1,
        (image.y + 1) * 2.0f / surface->h - 1
    );
    return std::make_pair(v1, v2);
}

void Renderer::addObject(const std::shared_ptr<VisibleObject> &object) {
    objects.push_back(object);
}

void Renderer::addLight(const std::shared_ptr<PointLight> &light) {
    pointLights.push_back(light);
}

void Renderer::render(Float time) {
    for(int i = 0; i < surface->w; i++) {
        for(int j = 0; j < surface->h; j++) {
            auto pos = toFragment(IVec2(i, j));
            Color pixelColor(0);
            for(int k = 0; k < sampleNumber; k++) {
                Vec2 sample (
                    Random::uniform(pos.first.x, pos.second.x),
                    Random::uniform(pos.first.y, pos.second.y)
                );
                Ray rayLocal = primaryCamera->getRay(sample, time);
                auto rayWorld = primaryCamera->getTransformation().toWorld(rayLocal);
                pixelColor += traceIndirect(rayWorld.first, tracingDepth) / rayWorld.second;
            }
            setPixel(i, j, pixelColor / (sampleNumber * 1.0f));
        }
        update();   //* DEBUG ONLY
    }
    update();
    std::cout << "Render Completed!" << std::endl;

    // wait for the user to quit
    SDL_Event e;
    bool quit = false;
    while(!quit) {
        if(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
}

void Renderer::renderToImage(const string &fileName, Float time) {
    PPMImage image(fileName, surface->w, surface->h);
    for(int i = 0; i < surface->w; i++) {
        for(int j = 0; j < surface->h; j++) {
            auto pos = toFragment(IVec2(i, j));
            Color pixelColor(0);
            for(int k = 0; k < sampleNumber; k++) {
                Vec2 sample (
                    Random::uniform(pos.first.x, pos.second.x),
                    Random::uniform(pos.first.y, pos.second.y)
                );
                Ray rayLocal = primaryCamera->getRay(sample, time);
                auto rayWorld = primaryCamera->getTransformation().toWorld(rayLocal);
                pixelColor += traceIndirect(rayWorld.first, tracingDepth) / rayWorld.second;
            }
            image.nextPixel(pixelColor / (sampleNumber * 1.0f));
        }
    }
    std::cout << "Render completed to image " << fileName << std::endl;
}

std::optional<Renderer::IntersectResult> Renderer::intersect(const Ray &ray, bool isPositive) const {
    std::optional<IntersectResult> ans;
    for(std::shared_ptr<VisibleObject> object : objects) {
        auto rayLocal = object->getTransformation().toLocal(ray);
        std::optional<VisibleObject::IntersectionResult> intersection;
        if(isPositive) {
            intersection = object->intersect(rayLocal.first, -VisibleObject::DEFAULT_T_MAX, -VisibleObject::DEFAULT_T_MIN);
        } else {
            intersection = object->intersect(rayLocal.first);
        }
        if(!intersection.has_value()) {
            continue;
        }
        Transformation transformation = object->getTransformation();
        Float factor = transformation.getGamma() * (1 - dot(transformation.getVelocity(), ray.getDirection()) / lightSpeed);
        Float tWorld = intersection.value().distance / factor;
        if(!ans.has_value() || ((tWorld > ans.value().distance) ^ isPositive)) {
            ans = IntersectResult(object, ray.atDistance(tWorld), rayLocal.first, tWorld, rayLocal.second, intersection.value());
        }
    }
    return ans;
}

Float Renderer::traceIndirect(const Ray &ray, Int depth) const {
    if(depth <= 0) {
        return 0;
    }
    
    std::optional<IntersectResult> mayBeResult = intersect(ray, false);
    if(!mayBeResult.has_value()) {
        return 0;
    }
    IntersectResult result = mayBeResult.value();
    Float direct = traceDirect(result, result.rayLocal.getDirection()) / result.intensityChange;
    auto inDirLocal = result.object->getMaterial()->sample(result.localResult.normal, result.rayLocal.getDirection());
    Ray inRayLocal(result.localResult.intersection, -inDirLocal.first);
    auto inRayGlobal = result.object->getTransformation().toWorld(ray);
    Float indirect = traceIndirect(inRayGlobal.first, depth - 1)
            / inRayGlobal.second                                                    // convert from world ref frame to local
            * inDirLocal.second * dot(result.localResult.normal, inDirLocal.first)  // regular rendering equation
            / result.intensityChange;                                               // convert back from local ref frame to world
    return direct + indirect;
}

Float Renderer::traceDirect(const Renderer::IntersectResult &result, const Vec3 &dirOut) const {
    Float ans = 0;
    // trace point lights
    for(std::shared_ptr<PointLight> light : pointLights) {
        Transformation tr = light->getTransformation();
        Vec3 d = tr.getUnitVelocity();
        Float a = 1 - d.sqLength();
        Float hb = dot(result.intersection - tr.getOrigin(), LVec4(1, d));
        Float c = -(result.intersection - tr.getOrigin()).sqLength();
        Float t = (-hb - sqrt(hb * hb - a * c)) / a;      // distance from origin of reference frame to the origin of ray
        LVec4 origin = tr.getOrigin() + LVec4(1, d) * t;
        Vec3 direction = result.intersection.getXYZ() - origin.getXYZ();
        Ray rayWorld(origin, direction);

        // check if there is object blocking the light
        auto intersection = intersect(Ray(origin, direction), true);
        if(intersection.has_value() && intersection.value().distance < direction.length() + VisibleObject::DEFAULT_T_MAX) {
            continue;
        }

        auto rayOutLocal = tr.toLocal(rayWorld);                                // ray in light source's local reference frames
        auto rayInLocal = result.object->getTransformation().toLocal(rayWorld); // ray in the object's local reference frame

        ans += light->getIntensity() / rayOutLocal.second
                * rayInLocal.second
                * result.object->getMaterial()->f(result.localResult.normal, -rayInLocal.first.getDirection(), dirOut)
                * dot(-rayInLocal.first.getDirection(), result.localResult.normal);
    }
    return ans;
}

void Renderer::initWindow(Int width, Int height) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow (
        "Relativistic Renderer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );
    surface = SDL_GetWindowSurface(window);
}

void Renderer::setPixel(Int x, Int y, const Color& color) {
    Int yp = surface->h - y;
    Uint32* targetPixel = (Uint32*) (surface->pixels + yp * surface->pitch + x * surface->format->BytesPerPixel);
    Color c = Color (
        (color.r > 1)? 1: (color.r < 0)? 0: color.r,
        (color.g > 1)? 1: (color.g < 0)? 0: color.g,
        (color.b > 1)? 1: (color.b < 0)? 0: color.b
    );
    *targetPixel = SDL_MapRGB(surface->format, c.r * 255.9, c.g * 255.9, c.b * 255.9);
}

void Renderer::freeWindow() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::update() {
    SDL_UpdateWindowSurface(window);
}

// class: IntersectionResult //

Renderer::IntersectResult::IntersectResult (
    std::shared_ptr<VisibleObject> object,
    const LVec4 &intersection,
    const Ray &rayLocal,
    Float distance, 
    Float ic,
    const VisibleObject::IntersectionResult &result
): object(object), intersection(intersection), rayLocal(rayLocal), distance(distance), intensityChange(ic), localResult(result) {}

} // namespace gmq