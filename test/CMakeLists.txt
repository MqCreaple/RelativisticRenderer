project(RendererTest)

function(createTest DIRECTORY NAME)
    set(TEST_NAME test_${NAME})
    add_executable(${TEST_NAME} ${DIRECTORY}/${NAME}.cpp)
    target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${TEST_NAME} libRelativisticRenderer ${SDL2_LIBRARIES})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction() # createTest

createTest(math Vec3)
createTest(math Vec4)
createTest(math LVec4)
createTest(math Mat4)
createTest(utils Ray)
createTest(utils Random)
createTest(utils Transformation)
createTest(components SphereObject)