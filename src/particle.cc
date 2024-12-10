#include "../inc/particle.h"

#include <iostream>

Particle::Particle(glm::vec3 const& pos, Shader const& shader, size_t const radius)
: Body{pos, shader}, radius{radius}
{}

void Particle::render() const
{
    float vertices [32] {0};
    size_t indices [31*3] {};

    for (size_t i {1}; i < 32; i++)
    {
        vertices[i] = radius * (sin(i * PI/16) + cos(i * PI/16));
         std::cout << vertices[i] << std::endl;
    }

    for (size_t i {}; i < 31*3;i+=3)
    {
        indices[i] = 0;
        indices[i+1] = i;
        indices[i+2] = i+1;
         std::cout << indices[i+1] << std::endl;
    }

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
