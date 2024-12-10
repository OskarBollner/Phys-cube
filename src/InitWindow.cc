
#include "../inc/InitWindow.h"
#include <stdexcept>

#include "../inc/shader.h"

InitWindow::InitWindow(size_t xRes, size_t yRes, const char* name)
: window{}
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(xRes, yRes, name, NULL, NULL);

    if (window == NULL)
    {
        glfwTerminate();
        throw std::logic_error("Failed to create window!");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader( reinterpret_cast<GLADloadproc>(glfwGetProcAddress) ))
    {
        throw std::logic_error("Failed to init GLAD");
    }

    glViewport(0, 0, xRes, yRes);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height)
                                   {glViewport(0, 0, width, height);});
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

}

void InitWindow::run()
{
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        processInput();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void InitWindow::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        glClearColor(0.5f, 0.1f, 0.5f, 1.0f);
    }
}
