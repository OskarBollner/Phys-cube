#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>
#include <string>
#include <vector>

#include "particle.h"

class InitWindow
{
public:
    InitWindow(size_t, size_t, const char* name);
    ~InitWindow();

    void run();
private:
    void processInput();
    void update(double);
    void render();

    std::vector<Particle*> objects;
    std::vector<Shape*> shapes;

    GLFWwindow* window;
};
