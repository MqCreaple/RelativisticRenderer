#include "RelativisticRenderer.h"
#include <sstream>
#include <iomanip>
using namespace gmq;

int main() {
    auto sphere = std::make_shared<SphereObject>(LVec4(0, 0, 0, 1), Vec3(0.5, 0, 0), Material::DEFAULT, 1);
    auto rectangle = std::make_shared<RectangleObject>(Transformation::WORLD, Material::DEFAULT, 6, 6);
    auto light = std::make_shared<PointLight>(Vec3(1, 2, 1.5), 1.0);
    auto camera = new PerspectiveCamera(LVec4(0, 0, 0, 4), Vec3(), 1.0);
    Renderer renderer(700, 700, camera);
    renderer.addObject(sphere);
    renderer.addObject(rectangle);
    renderer.addLight(light);
    for(Float time = 0; time < 5; time += 0.25) {
        std::stringstream fileNameStream;
        fileNameStream << "sc_" << std::fixed << std::setprecision(2) << time;
        std::string fileName = fileNameStream.str();
        renderer.renderToImage(fileName, time);
    }
    // renderer.render(3.50);
}