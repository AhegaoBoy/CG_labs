#ifndef LAB_6_ENGINE_H
#define LAB_6_ENGINE_H
#include<SFML/Graphics.hpp>
#include<GLFW/glfw3.h>
#include<memory>


#include "PhysicsSystem.h"
#include "SceneLoader.h"
class Engine
{
public:
    bool is_running = false;
    double last_frame_time = 0;

    std::unique_ptr<physics_system> physicsSystem;
    std::shared_ptr<scene_manager> sceneManager;

    GLFWwindow* window = nullptr;

public:
    bool init();
    void run();

private:
    bool init_graphics();
    void update(double selta_time);
    void render();
    void shutdown();

};

#endif //LAB_6_ENGINE_H
