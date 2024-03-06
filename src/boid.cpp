#pragma once

#include "boid.hpp"
// #include <bits/stdc++.h>
#include <cstdlib>
#include <random>
#include <vector>
#include "glm/fwd.hpp"

std::default_random_engine             gen;
std::uniform_real_distribution<double> distrib_pos(-0.09, 0.09);
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

void Boid::move(float square_radius)
{
    // if (m_position[0] - m_radius < -square_radius)
    //     m_position[0] = square_radius * 2 + m_position[0];
    // if (m_position[0] + m_radius > square_radius)
    //     m_position[0] = -m_position[0];

    // if (m_position[1] - m_radius < -square_radius)
    //     m_position[1] = square_radius * 2 + m_position[1];
    // if (m_position[1] + m_radius > square_radius)
    //     m_position[1] = -m_position[1];

    float margin     = 0.97;
    float turnfactor = 0.002;
    float maxspeed   = 0.006;
    float minspeed   = 0.002;
    if (m_position[0] < -square_radius * margin)
    {
        m_speed[0] += turnfactor;
    }
    if (m_position[0] > square_radius * margin)
    {
        m_speed[0] -= turnfactor;
    }
    if (m_position[1] < -square_radius * margin)
    {
        m_speed[1] += turnfactor;
    }
    if (m_position[1] > square_radius * margin)
    {
        m_speed[1] -= turnfactor;
    }
    float speed = sqrt(m_speed[0] * m_speed[0] + m_speed[1] * m_speed[1]);
    if (speed > maxspeed)
    {
        m_speed[0] = (m_speed[0] / speed) * maxspeed;
        m_speed[1] = (m_speed[1] / speed) * maxspeed;
    }

    if (speed < minspeed)
    {
        m_speed[0] = (m_speed[0] / speed) * minspeed;
        m_speed[1] = (m_speed[1] / speed) * minspeed;
    }

    glm::vec3 new_pos = m_speed + m_position;
    m_position        = new_pos;
}
