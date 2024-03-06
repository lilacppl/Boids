#pragma once

#include "boid.hpp"
// #include <bits/stdc++.h>
#include <cstdlib>
#include <random>
#include <vector>
#include "glm/fwd.hpp"

std::default_random_engine             gen;
std::uniform_real_distribution<double> distrib_pos(-0.3, 0.3);
std::uniform_real_distribution<double> distrib_speed(-0.005, 0.005);
std::vector<int>                       rand_speed{-1, 1};

Boid::Boid()
    : m_position(glm::vec3{distrib_pos(gen), distrib_pos(gen), distrib_pos(gen)}), m_speed(glm::vec3{distrib_speed(gen), distrib_speed(gen), 0}), m_radius(0.01) {}

glm::vec3 Boid::get_position() const
{
    return m_position;
}
glm::vec3 Boid::get_speed() const
{
    return m_speed;
}

void Boid::draw(p6::Context& ctx)
{
    ctx.fill = {1, 1, 1, 0.5};
    ctx.square(p6::Center{get_position()}, p6::Radius{0.01f});
}

void Boid::move()
{
    if (m_position[0] - m_radius < -0.9)
        m_position[0] = 0.9f * 2 + m_position[0];
    if (m_position[0] + m_radius > 0.9)
        m_position[0] = -m_position[0];

    if (m_position[1] - m_radius < -0.9)
        m_position[1] = 0.9f * 2 + m_position[1];
    if (m_position[1] + m_radius > 0.9)
        m_position[1] = -m_position[1];

    glm::vec3 new_pos = m_speed + m_position;
    m_position        = new_pos;
}
