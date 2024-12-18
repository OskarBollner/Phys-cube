#include "../inc/shape.h"

#include <iostream>

Shape::Shape(std::vector<float> const& vertexData, Shader const& shader)
: shader{shader}, vertices{vertexData}, VAO{}, VBO{}
{
    initRenderData();
}

Shape::Shape(std::vector<float> const& vertexData, Shader const& shader, Color color)
: shader{shader}, vertices{vertexData}, VAO{}, VBO{}
{
    if (glfwInit() == GLFW_TRUE){};
    initRenderData();
    shader.use();
    shader.setColor("color", tovec3(color));
}

Shape::Shape(Shape const& other)
: shader{other.shader}, vertices{other.vertices}, VAO{other.VAO}, VBO{other.VBO}
{}

Shape::~Shape()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Shape::initRenderData()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    if (VBO == 0 || VAO == 0) {
            std::cerr << "Error: Failed to generate OpenGL buffers." << std::endl;
            return;
    }

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const Shape& Shape::getTriangle(Color color) {
    static Shape* triangle { new Shape {
            {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
            },
            Shader{},
            color
        }
    };

    std::cout << "ShaderID: " << triangle->shader.ID << std::endl;
    std::cout << "VAO: " << triangle->VAO << std::endl;
    std::cout << "VBO: " << triangle->VBO << std::endl;
    return *triangle;
}

const Shape& Shape::getRectangle(Color color) {
    static Shape* rectangle { new Shape {
        {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
        },
        Shader{},
        color
        }
    };
    return *rectangle;
}

const Shape& Shape::getCircle(Color color) {
    static std::vector<float> vertices = []() {
        int segments = 36;
        std::vector<float> vtx;
        vtx.push_back(0.0f); // Center vertex
        vtx.push_back(0.0f);
        vtx.push_back(0.0f);

        for (int i = 0; i <= segments; ++i) {
            float angle = (i * 2 * M_PI) / segments;
            vtx.push_back(std::cos(angle) * 0.5f);
            vtx.push_back(std::sin(angle) * 0.5f);
            vtx.push_back(0.0f);
        }
        return vtx;
    }();

    static Shape* circle {new Shape {vertices, Shader{}, color} };
    return *circle;
}

//const Shape Shape::Cube {std::vector<float>{}};

namespace Drawing {

    void drawHelper(Shader const& shader, Shape const& shape, glm::vec3 pos)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(shape.getVAO());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, shape.getVertexData().size()/3);
        glBindVertexArray(0);
    }
};
