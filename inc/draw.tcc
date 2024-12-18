
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <concepts>

namespace Drawing {
    void drawHelper(Shader const& shader, Shape const& shape, glm::vec3 pos);
}

template <typename T>
concept Drawable = requires(T shape) {
    { shape.getVAO() } -> std::convertible_to<unsigned int>;
    { shape.getShader() } -> std::convertible_to<Shader>;
    { shape.getVertexData() } -> std::convertible_to<std::vector<float>>;
};

template <typename T>
concept is_object = requires(T object) {
    { object.getShape() } -> std::convertible_to<Shape>;
    { object.getPos() } -> std::convertible_to<glm::vec3>;
};

template <typename T>
requires Drawable<T>
void Draw(T const& shape, glm::vec3 pos, Color color)
{
    Shader const& shader = shape.getShader();
    shader.use();
    shader.setColor("color", tovec3(color));
    
    Drawing::drawHelper(shader, shape, pos);
}

template <typename T>
requires Drawable<T>
void Draw(T const& shape, glm::vec3 pos)
{
    Shader const& shader = shape.getShader();
    shader.use();

    Drawing::drawHelper(shader, shape, pos);
}

template <typename T>
requires is_object<T>
void Draw(T const& object)
{
    Shader const& shader = object.getShape().getShader();

    shader.use();

    Drawing::drawHelper(shader, object.getShape(), object.getPos());
}

