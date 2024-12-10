#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>
#include <string>

class InitWindow
{
public:
    InitWindow(size_t, size_t, const char* name);

    void run();
private:
    void processInput();

    GLFWwindow* window;
};
