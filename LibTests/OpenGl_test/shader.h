#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int const ID;

    Shader(const char*, const char*);

    void use();

    void setBool(std::string const&, bool) const;
    void setInt(std::string const&, int) const;
    void setFloat(std::string const&, float) const;

};

#endif //SHADER_H
