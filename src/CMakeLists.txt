add_library(libRelativisticRenderer
    utils/Random.cpp
    utils/Transformation.cpp
    utils/Ray.cpp
    utils/Color.cpp
    utils/PPMImage.cpp
    components/Object.cpp
    components/VisibleObject.cpp
    components/SphereObject.cpp
    components/RectangleObject.cpp
    components/Camera.cpp
    components/PerspectiveCamera.cpp
    components/PointLight.cpp
    material/Material.cpp
    material/DiffuseMaterial.cpp
    renderer/Renderer.cpp
)

add_executable(RelativisticRenderer main.cpp)
target_link_libraries(RelativisticRenderer libRelativisticRenderer ${SDL2_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})