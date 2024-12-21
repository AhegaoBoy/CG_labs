cmake_minimum_required(VERSION 3.23)
project(lab_2)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

find_package(GLUT REQUIRED)

find_package(GLEW REQUIRED)

add_executable(lab_2 main.cpp)
target_link_libraries(lab_2 OpenGL::GL GLEW::GLEW GLUT::GLUT)

