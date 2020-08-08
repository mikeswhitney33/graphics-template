CMAKE_MINIMUM_REQUIRED(VERSION 3.0)



PROJECT(graphics-template)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_SUBDIRECTORY(assimp)
ADD_SUBDIRECTORY(glad)
ADD_SUBDIRECTORY(glfw)
ADD_SUBDIRECTORY(glm)
INCLUDE_DIRECTORIES(stb)

LINK_LIBRARIES(assimp glad glfw glm)

ADD_SUBDIRECTORY(pipeline)
LINK_LIBRARIES(pipeline)

#### vvvv Add subdirectory of project here vvvv ####


ADD_SUBDIRECTORY(fluid)

#### ^^^^ Add subdirectory of project here ^^^^ ####

ENABLE_TESTING()
ADD_SUBDIRECTORY(test)
