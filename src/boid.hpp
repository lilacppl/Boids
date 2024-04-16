#pragma once

#include <cstdlib>
// #include <winuser.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include "doctest/doctest.h"
#include "glm/fwd.hpp"
#include "iprogram.hpp"
#include "mesh.hpp"

class Boid {
private:
    float m_radius;

public:
    glm::vec3 m_speed;
    glm::vec3 m_position;
    glm::vec3 m_direction;
    Boid();
    glm::vec3 get_position() const;
    glm::vec3 get_speed() const;
    void      move(float square_radius, float maxspeed, float minspeed);
    void      draw(p6::Context& ctx, Mesh& mesh, glm::mat4 viewMatrix, Program& program);
};
