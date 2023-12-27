#include "RelativisticRenderer.h"
#include <sstream>
#include <iomanip>
#include <thread>
using namespace gmq;
using namespace std;

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[]) {
    auto sphere = std::make_shared<SphereObject>(LVec4(0, 0, 0, 1), Vec3(0.5, 0, 0), Material::DEFAULT, 1);
    auto cubeFace1 = std::make_shared<RectangleObject>(Transformation(LVec4(0, 0, 0, 1), Vec3(0.5, 0, 0)), Material::DEFAULT, 2, 2);
    // auto rectangle = std::make_shared<RectangleObject>(Transformation::WORLD, Material::DEFAULT, 8, 8);
    auto light = std::make_shared<PointLight>(Vec3(1, 2, 1.6), 1.0);
    auto camera = new PerspectiveCamera(LVec4(0, 0, 0, 4), Vec3(), 1.0);
    Renderer renderer(700, 700, camera);
    renderer.addObject(cubeFace1);
    // renderer.addObject(rectangle);
    renderer.addLight(light);

    cout << thread::hardware_concurrency() << " threads available" << endl;
    ThreadPool threadpool(thread::hardware_concurrency());

    int counter = 0;
    for(Float time = 0; time < 9; time += 1.0 / 12) {
        std::stringstream fileNameStream;
        fileNameStream << counter;
        std::string fileName = fileNameStream.str();
        threadpool.addTask([=, &renderer]() {
            renderer.renderToImage(fileName, time);
        });
        counter++;
    }
    threadpool.join();
}