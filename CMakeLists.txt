cmake_minimum_required(VERSION 3.14)
project(ultrasound_opengl CXX)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_library(ultrasound_opengl_lib SHARED
        main.cpp
        main.h)

#add_compile_options(-O3)

add_executable(ultrasound_opengl main.cpp)

target_link_libraries(ultrasound_opengl
        ${GLUT_LIBRARIES}
        ${GLU_LIBRARIES}
        ${OPENGL_LIBRARIES}
        OpenMP::OpenMP_CXX
        ultrasound_opengl_lib)