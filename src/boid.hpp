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
    float     m_radius;
    glm::vec3 m_direction;

public:
    glm::vec3 m_speed;    // utilisée dans boids.cpp
    glm::vec3 m_position; // utilisée dans boids.cpp
    Boid();
    glm::vec3 getPosition() const;
    glm::vec3 getSpeed() const;
    void      move(float square_radius, float maxspeed, float minspeed, float height);
    void      draw(const p6::Context& ctx, const Mesh& mesh, const glm::mat4 viewMatrix, const Program& program) const;
};

glm::vec3 calculateRotation(const glm::vec3 speed);
