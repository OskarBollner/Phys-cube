#include "../inc/shape.h"


Shape::Shape(std::vector<float> const& vertexData, Shader const& shader)
: shader{shader}, vertexData{vertexData}, VAO{}, VBO{}
{
    initRenderData();
}

Shape::Shape(std::vector<float> const& vertexData, Shader const& shader, Color color)
: shader{shader}, vertexData{vertexData}, VAO{}, VBO{}
{
    initRenderData();
    shader.use();
    shader.setColor("color", tovec3(color));
}

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
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Shape Shape::Triangle(Color color)
{
    std::vector<float> vertices
    {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f,  // right
            0.0f, 0.5f, 0.0f    // top
    };

    return Shape{vertices, Shader{}, color};
}

Shape Shape::Rectangle(Color color)
{
    std::vector<float> vertices
    {
        -0.5f, -0.5f, 0.0f,  // Center (Bottom-left)
        0.5f, -0.5f, 0.0f,  // Bottom-right
        0.5f, 0.5f, 0.0f,  // Top-right
        -0.5f, 0.5f, 0.0f
    };

    return Shape{vertices, Shader{}, color};
}

Shape Shape::Circle(Color color)
{
    int segments = 36;
    std::vector<float> vertices;
    vertices.push_back(0.f);
    vertices.push_back(0.f);
    vertices.push_back(0.f);

    for (int i = 0; i <= segments; ++i) {
        float angle = (i * 2 * M_PI) / segments;
        vertices.push_back(cos(angle) * 0.5f);
        vertices.push_back(sin(angle) * 0.5f);
        vertices.push_back(0.0f);
    }

    return Shape{vertices, Shader{}, color};
}

Shape Shape::Cube(Color color)
{
    std::vector<float> vertices
    {
         0.0f,  0.0f,  0.5f,  // Center of the front face
        -0.5f, -0.5f,  0.5f,  // Bottom-left
         0.5f, -0.5f,  0.5f,  // Bottom-right
         0.5f,  0.5f,  0.5f,  // Top-right
        -0.5f,  0.5f,  0.5f,  // Top-left
        -0.5f, -0.5f,  0.5f,   // Repeat Bottom-left to close the fanstd::vector<float> backFace = {
         0.0f,  0.0f, -0.5f,  // Center of the back face
        -0.5f, -0.5f, -0.5f,  // Bottom-left
        -0.5f,  0.5f, -0.5f,  // Top-left
         0.5f,  0.5f, -0.5f,  // Top-right
         0.5f, -0.5f, -0.5f,  // Bottom-right
        -0.5f, -0.5f, -0.5f,   // Repeat Bottom-left to close the fan§
         0.0f,  0.5f,  0.0f,  // Center of the top face
        -0.5f,  0.5f,  0.5f,  // Top-left-front
         0.5f,  0.5f,  0.5f,  // Top-right-front
         0.5f,  0.5f, -0.5f,  // Top-right-back
        -0.5f,  0.5f, -0.5f,  // Top-left-back
        -0.5f,  0.5f,  0.5f,   // Repeat Top-left-front
         0.0f, -0.5f,  0.0f,  // Center of the bottom face
        -0.5f, -0.5f, -0.5f,  // Bottom-left-back
         0.5f, -0.5f, -0.5f,  // Bottom-right-back
         0.5f, -0.5f,  0.5f,  // Bottom-right-front
        -0.5f, -0.5f,  0.5f,  // Bottom-left-front
        -0.5f, -0.5f, -0.5f,   // Repeat Bottom-left-back
        -0.5f,  0.0f,  0.0f,  // Center of the left face
        -0.5f, -0.5f, -0.5f,  // Bottom-left-back
        -0.5f,  0.5f, -0.5f,  // Top-left-back
        -0.5f,  0.5f,  0.5f,  // Top-left-front
        -0.5f, -0.5f,  0.5f,  // Bottom-left-front
        -0.5f, -0.5f, -0.5f,   // Repeat Bottom-left-back
         0.5f,  0.0f,  0.0f,  // Center of the right face
         0.5f, -0.5f,  0.5f,  // Bottom-right-front
         0.5f,  0.5f,  0.5f,  // Top-right-front
         0.5f,  0.5f, -0.5f,  // Top-right-back
         0.5f, -0.5f, -0.5f,  // Bottom-right-back
         0.5f, -0.5f,  0.5f
         };

    return Shape{vertices, Shader{}, color};
}
