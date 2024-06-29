cmake_minimum_required(VERSION 3.13)
project(drocket_rone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH /usr/local/lib/cmake)
set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw3)

add_subdirectory(glad)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})

set(SOURCE_FILES src/cpp/main.cpp)
add_executable(drocket_rone src/cpp/main.cpp src/cpp/Shader.cpp include/Shader.h include/stb_image.h src/cpp/Texture.cpp include/Texture.h src/cpp/Camera.cpp include/Camera.h src/cpp/Mesh.cpp include/Mesh.h src/cpp/Model.cpp include/Model.h)
target_link_libraries (drocket_rone
        ${OPENGL_LIBRARIES}
        ${GLFW3_LIBRARY}
        glfw
        assimp glad)