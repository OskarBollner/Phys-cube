#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

class Body
{
public:
    Body(glm::vec3 const&, Shader const&);
    virtual ~Body();

    //void handleCollision(const Body*);
    //void update(std::vector<glm::vec3> const&);
    virtual void render() const;

protected:
    glm::vec3 pos;
    Shader shader;
};
