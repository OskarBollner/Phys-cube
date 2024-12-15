#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    unsigned int const ID;

    Shader();
    Shader(const char*, const char*);

    void use() const;

    void setBool(std::string const&, bool) const;
    void setInt(std::string const&, int) const;
    void setFloat(std::string const&, float) const;
    void setColor(std::string const&, glm::vec3 const&) const;

private:
    void initShader(const char*, const char*);
};

#endif //SHADER_H
