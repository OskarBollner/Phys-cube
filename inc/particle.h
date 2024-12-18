#pragma once

#include "shape.h"

class Particle
{
public:
    Particle(glm::vec3 const&, Shape const&);
    ~Particle() = default;

    inline Shape const& getShape() const { return shape; }
    inline glm::vec3 const& getPos() const { return pos; }

    void update(float);

private:
    glm::vec3 pos;
    glm::vec3 velocity;
    Shape shape;
    unsigned mass;
};
