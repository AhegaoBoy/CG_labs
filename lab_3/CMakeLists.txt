cmake_minimum_required(VERSION 3.23)
project(lab_3)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)
add_executable(lab_3 main.cpp)

target_link_libraries(lab_3 PRIVATE OpenGL::GL GLEW::GLEW glm::glm glfw)