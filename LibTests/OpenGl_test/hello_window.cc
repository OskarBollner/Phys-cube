#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    GLFWwindow* window {glfwCreateWindow(800,600,"YEAAAAAAH", NULL, NULL)};
    if (window == NULL)
    {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader( reinterpret_cast<GLADloadproc>(glfwGetProcAddress) ))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    //

    float vertices [] {
        -0.5, 0.5, 0.5, 1.0, 0, 0,
        -0.5, -0.5, 0, 0, 1.0, 0,
        0.5,  -0.5, 0, 0, 0, 1.0,
        0.5, 0.5, 0, 1.0, 1.0, 1.0,
    };

    unsigned int indices [] {
        0, 1, 2,
        0, 3, 2
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // 

    Shader shader {"shader.vs", "shader.fs"};

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        processInput(window);

        shader.use();
        float timeValue {static_cast<float>(glfwGetTime())};
        double alpha {sin(timeValue)/2.0 + 0.5};
        shader.setFloat("alpha", alpha);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void checkCompileSuccess(unsigned int shader)
{
    int success {};
    char infoLog[512] {};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" 
            << infoLog << std::endl;
    }
}

void checkLinkSuccess(unsigned int program)
{
    int success {};
    char infoLog[512] {};
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" 
            << infoLog << std::endl;
    }
}
