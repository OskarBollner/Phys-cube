
#include "../inc/InitWindow.h"
#include <stdexcept>

#include "../inc/shape.h"

InitWindow::InitWindow(size_t xRes, size_t yRes, const char* name)
: objects{}, window{}
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
    glEnable(GL_DEPTH_TEST);

}

InitWindow::~InitWindow()
{
    for (Particle* shape : objects)
    {
        delete shape;
    }
    glfwTerminate();
}

void InitWindow::run()
{

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput();
        
        update(0.01f);

        render();

        glfwPollEvents();
    }
}

void InitWindow::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        shapes.push_back(new Shape{Shape::Rectangle(Color::BLUE)});
    }
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        shapes.push_back(new Shape{Shape::Circle(Color::RED)});
    }
    else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        shapes.push_back(new Shape{Shape::Triangle(Color::GREEN)});
    }
    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        objects.push_back(new Particle{glm::vec3{0,0,-10}, Shape::Cube(Color::GREEN)});
    }
}

void InitWindow::update(float dt)
{
    // Do something.
}

void InitWindow::render()
{
    for(auto& object : objects)
    {
        Draw(object->getShape(), object->getPos());
    }
    //for(auto& object : shapes)
    //{
    //    Draw(*object, glm::vec3{0,0,-10});
    //}

    glfwSwapBuffers(window);
}

