CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

ADD_SUBDIRECTORY(assimp)
ADD_SUBDIRECTORY(glad)
ADD_SUBDIRECTORY(glfw)
ADD_SUBDIRECTORY(glm)
INCLUDE_DIRECTORIES(stb)

LINK_LIBRARIES(assimp glad glfw glm)

ENABLE_TESTING()
ADD_SUBDIRECTORY(test)

#### vvvv Add subdirectory of project here vvvv ####



#### ^^^^ Add subdirectory of project here ^^^^ ####
