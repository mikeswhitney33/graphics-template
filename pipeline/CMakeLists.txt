add_library(
    pipeline
    src/graphics-pipeline.cpp
    src/input.cpp
    src/shader.cpp
    src/exceptions.cpp
    src/camera.cpp
)
target_include_directories(pipeline PUBLIC include)

add_executable(pipeline-test src/pipeline-test.cpp)
target_link_libraries(pipeline-test pipeline)

add_executable(basic3d src/basic3D-pipeline.cpp)
target_link_libraries(basic3d pipeline)
target_include_directories(basic3d PUBLIC include)
