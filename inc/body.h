#pragma once

class Body
{
public:
    void update(std::vector const&);
    void render();

private:
    Shape shape;
    unsigned elasticity;
}
