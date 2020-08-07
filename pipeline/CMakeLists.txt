add_library(
    pipeline
    src/graphics-pipeline.cpp
    src/input.cpp
    src/shader.cpp
    src/exceptions.cpp
)
target_include_directories(pipeline PUBLIC include)

add_executable(pipeline-test src/pipeline-test.cpp)
target_link_libraries(pipeline-test pipeline)
