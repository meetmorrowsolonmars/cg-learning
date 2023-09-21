cmake_minimum_required(VERSION 3.0.0)

project(cg-learning VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(GLAD STATIC external/glad/include/glad/glad.h external/glad/src/glad.c)
target_include_directories(GLAD PUBLIC external/glad/include/)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

add_executable(cg-learning main.cpp)

target_link_libraries(cg-learning PRIVATE SDL3::SDL3 GLAD)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
