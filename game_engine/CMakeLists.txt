cmake_minimum_required(VERSION 3.23)

# Настраиваем название проекта
project(game_engine)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(IMGUI_FILES
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui_impl_qt.cpp
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
        ${CMAKE_SOURCE_DIR}/src
        include/Camera.h
        include/ImGuiController.h
        imgui/imgui_impl_qt.h
        imgui/imgui_impl_qt.cpp
        include/MainWindow.h
        include/Shader.h
        include/Texture.h
        include/SceneWindow.h
        src/SceneWindow.cpp
)

add_executable(game_engine
        main.cpp
        ${SOURCES}
        ${IMGUI_FILES}
)



target_include_directories(game_engine PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        imgui
)


# Линкуем библиотеки для проекта
target_link_libraries(game_engine PRIVATE
        OpenGL::GL
        GLEW::GLEW
        glm::glm
        glfw
        sfml-system sfml-window sfml-graphics
        Qt6::Widgets
        Qt6::OpenGLWidgets
)