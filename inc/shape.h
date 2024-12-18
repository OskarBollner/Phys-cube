#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "shader.h"

enum class Color
{
    RED,
    GREEN,
    BLUE,
    CYAN,
    PURPLE,
    YELLOW
};

static glm::vec3 tovec3(Color color) {
    switch (color) {
    case Color::RED:
        return {1.0f, 0.0f, 0.0f};
    case Color::GREEN:
        return {0.0f, 1.0f, 0.0f};
    case Color::BLUE:
        return {0.0f, 0.0f, 1.0f};
    case Color::CYAN:
        return {0.0f, 1.0f, 1.0f};
    case Color::PURPLE:
        return {1.0f, 0.0f, 1.0f};
    case Color::YELLOW:
        return {1.0f, 1.0f, 0.0f};
    default:
        return {0.0f, 0.0f, 0.0f}; // Default color if none matches
    }
}

class Shape
{
public:
    Shape(std::vector<float> const&, Shader const&);
    Shape(std::vector<float> const&, Shader const&, Color);
    Shape(Shape const&);
    ~Shape();

    static const Shape& getTriangle(Color);
    static const Shape& getRectangle(Color);
    static const Shape& getCircle(Color);
    static const Shape& getCube(Color);

    inline unsigned int getVAO() const { return VAO; }
    inline Shader const& getShader() const { return shader; }
    inline std::vector<float> const& getVertexData() const { return vertices; }

private:
    Shader const shader;
    std::vector<float> const vertices;
    unsigned int VAO;
    unsigned int VBO;

    void initRenderData();
};

#include "draw.tcc"

#endif //SHAPE_H
