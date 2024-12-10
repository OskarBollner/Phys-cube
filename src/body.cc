#include "../inc/body.h"

Body::Body(glm::vec3 const& pos, Shader const& shader)
: pos{pos}, shader{shader}
{}

Body::~Body()
{}

void Body::render() const
{}
