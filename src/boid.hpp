#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include "doctest/doctest.h"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid {
private:
    float m_radius;

public:
    glm::vec4 m_speed;
    glm::vec4 m_position;
    Boid();
    glm::vec4 get_position() const;
    glm::vec4 get_speed() const;
    void      move(float square_radius, float maxspeed, float minspeed);
    void      draw(p6::Context& ctx);
};
