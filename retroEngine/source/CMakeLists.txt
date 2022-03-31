cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(RetroEngine C CXX)

# Getting the parent directory twice
cmake_path(GET CMAKE_SOURCE_DIR PARENT_PATH CURRENT_DIR)
cmake_path(GET CURRENT_DIR PARENT_PATH ROOT_DIR)

add_executable(RetroE
    "main.cpp"
    "shader.h"
)
set_property(TARGET RetroE PROPERTY CXX_STANDARD 20)
target_link_libraries(RetroE PRIVATE
    "${ROOT_DIR}/libs/glad/build/Release/glad.lib"
    "${ROOT_DIR}/libs/glfw/build/src/Release/glfw3.lib"
)
target_include_directories(RetroE PRIVATE
    "${ROOT_DIR}/libs/glad/source/include"
    "${ROOT_DIR}/libs/glfw/source/include"
    "${ROOT_DIR}/libs/glm/source/"
)