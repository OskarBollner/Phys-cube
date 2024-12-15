
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    Shader shader = shape.getShader();
    shader.use();
    shader.setColor("color", tovec3(color));

    glBindVertexArray(shape.getVAO());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, shape.getVertexData().size()/3);
    glBindVertexArray(0);
}

template <typename T>
requires Drawable<T>
void Draw(T const& shape, glm::vec3 pos)
{
    Shader shader = shape.getShader();
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

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

template <typename T>
requires is_object<T>
void Draw(T const& object)
{
    Shape shape = object.getShape();
    Shader shader = shape.getShader();

    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, object.getPos());
    //model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

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
