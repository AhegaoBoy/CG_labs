cmake_minimum_required(VERSION 3.23)

# Настраиваем название проекта
project(lab_6)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
include_directories(imgui)
include_directories(imgui/backends)
file(GLOB IMGUI_SOURCES
        imgui/*.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(SFML REQUIRED COMPONENTS system window graphics)
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

# Подключаем библиотеку glm через FetchContent
include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
)
FetchContent_MakeAvailable(glm)

# Указываем исходные файлы
set(SOURCES
        ${CMAKE_SOURCE_DIR}/objects/src/character.cpp
        ${CMAKE_SOURCE_DIR}/Engine/src/Engine.cpp
        Engine/include/PhysicsSystem.h
        Engine/include/Light.h
        Engine/include/Camera.h
        objects/include/SimpleObject.h
        Engine/include/SceneWidget.h
        Engine/src/SceneWidget.cpp
        Engine/include/MainWindow.h
        Engine/src/MainWindow.cpp
        Engine/src/Camera.cpp
)

add_executable(lab_6
        main.cpp
        ${SOURCES}
)

target_include_directories(lab_6 PRIVATE
        ${CMAKE_SOURCE_DIR}/objects/include
        ${CMAKE_SOURCE_DIR}/Engine/include
)

# Создаем исполняемый файл


# Линкуем библиотеки для проекта
target_link_libraries(lab_6 PRIVATE
        OpenGL::GL
        GLEW::GLEW
        glm::glm
        glfw
        sfml-system sfml-window sfml-graphics
        Qt6::Widgets
        Qt6::OpenGLWidgets
)