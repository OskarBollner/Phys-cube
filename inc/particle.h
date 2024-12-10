#pragma once

#include "body.h"
#include "shader.h"

static float const PI {3.141592};

class Particle : public Body
{
public:
    Particle(glm::vec3 const&, Shader const&, size_t const);
    ~Particle() = default;
    
    void render() const override;

private:
    size_t radius;
};
