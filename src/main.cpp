#include "RelativisticRenderer.h"
#include <sstream>
#include <iomanip>
#include <thread>
using namespace gmq;

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[]) {
    auto sphere = std::make_shared<SphereObject>(LVec4(0, 0, 0, 1), Vec3(0.5, 0, 0), Material::DEFAULT, 1);
    auto rectangle = std::make_shared<RectangleObject>(Transformation::WORLD, Material::DEFAULT, 8, 8);
    auto light = std::make_shared<PointLight>(Vec3(1, 2, 1.6), 1.0);
    auto camera = new PerspectiveCamera(LVec4(0, 0, 0, 4), Vec3(), 1.0);
    Renderer renderer(700, 700, camera);
    renderer.addObject(sphere);
    renderer.addObject(rectangle);
    renderer.addLight(light);

    // std::vector<std::thread> threads;
    // for(Float time = 0; time < 6; time += 0.25) {
    //     std::stringstream fileNameStream;
    //     fileNameStream << "sc_" << std::fixed << std::setprecision(2) << time;
    //     std::string fileName = fileNameStream.str();
    //     threads.push_back(std::thread(&Renderer::renderToImage, std::ref(renderer), fileName, time));
    // }
    // for(std::thread &thread : threads) {
    //     thread.join();
    // }
    renderer.renderToImage("image-t-4.0", 4.0);
}