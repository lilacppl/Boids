#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include "doctest/doctest.h"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid {
private:
    glm::vec3 m_position;
    glm::vec3 m_speed;
    float     m_radius;

public:
    Boid();
    glm::vec3 get_position() const;
    glm::vec3 get_speed() const;
    void      move();
    void      draw(p6::Context& ctx);
};
