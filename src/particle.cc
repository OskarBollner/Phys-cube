#include "../inc/particle.h"

#include <iostream>


Particle::Particle(glm::vec3 const& pos, Shape const& shape)
: pos{pos}, shape{shape}
{}
