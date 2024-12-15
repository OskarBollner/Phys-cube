#include "../inc/shader.h"

Shader::Shader()
: ID {glCreateProgram()}
{
    const char* vShaderCode {
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"

    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"

    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "}\0"
    };

    const char* fShaderCode {
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec3 color;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(color, 1.0f);\n"
    "}\n\0"
    };
    initShader(vShaderCode, fShaderCode);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
: ID {glCreateProgram()}
{
    std::string vertexCode {};
    std::string fragmentCode {};

    std::ifstream vShaderFile {};
    std::ifstream fShaderFile {};

    std::ostringstream vecStream {};
    std::ostringstream fragStream {};

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        vecStream << vShaderFile.rdbuf();
        fragStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vecStream.str();
        fragmentCode = fragStream.str();
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const char* vShaderCode {vertexCode.c_str()};
    const char* fShaderCode {fragmentCode.c_str()};
    initShader(vShaderCode, fShaderCode);
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::setBool(std::string const& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(std::string const& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(std::string const& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setColor(std::string const& name, glm::vec3 const& color) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), color.x, color.y, color.z);
}

void Shader::initShader(const char* vShaderCode, const char* fShaderCode)
{
    unsigned int vertex {};
    unsigned int fragment {};
    int success {};
    char infolog[512];

    // vertexShader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infolog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog
            << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infolog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog
            << std::endl;
    }

    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infolog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog
            << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
