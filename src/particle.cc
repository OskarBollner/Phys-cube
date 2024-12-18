#include "../inc/particle.h"

#include <iostream>


Particle::Particle(glm::vec3 const& pos, Shape const& shape)
: pos{pos}, velocity{glm::vec3{0.1,0,0}}, shape{shape}
{}

void Particle::update(float dt)
{
    velocity += glm::vec3{0,sin(glfwGetTime()),0} * dt;
    pos += velocity;
}
