CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED 11)

PROJECT(graphics-template)

ADD_SUBDIRECTORY(assimp)
ADD_SUBDIRECTORY(glad)
ADD_SUBDIRECTORY(glfw)
ADD_SUBDIRECTORY(glm)
INCLUDE_DIRECTORIES(stb)

LINK_LIBRARIES(assimp glad glfw glm)

ADD_SUBDIRECTORY(pipeline)
LINK_LIBRARIES(pipeline)

#### vvvv Add subdirectory of project here vvvv ####




#### ^^^^ Add subdirectory of project here ^^^^ ####

ENABLE_TESTING()
ADD_SUBDIRECTORY(test)
