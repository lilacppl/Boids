#pragma once

#include "boid.hpp"
// #include <bits/stdc++.h>
#include <random>
#include "glm/fwd.hpp"

static constexpr float                 maxSpeed = 5;
static constexpr float                 maxForce = 10;
std::default_random_engine             gen;
std::uniform_real_distribution<double> distrib_pos(0.0, 0.8);
std::uniform_real_distribution<double> distrib_speed(-0.01, 0.01);

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
        m_position[0] = -m_position[0];
    if (m_position[0] + m_radius > 0.9)
        m_position[0] = -m_position[0];
    if (m_position[1] - m_radius < -0.9)
        m_position[1] = -m_position[1];
    if (m_position[1] + m_radius > 0.9)
        m_position[1] = -m_position[1];
    glm::vec3 new_pos = m_speed + m_position;
    m_position        = new_pos;
}

glm::vec3 Boid::alignement(std::vector<Boid>& all)
{
    float neighbordist = 50; // Field of vision

    glm::vec3 sum(0, 0, 0);
    int       count = 0;
    for (int i = 0; i < all.size(); i++)
    {
        float d = abs(get_position()[0] - all[i].get_position()[0]);
        if ((d > 0) && (d < neighbordist))
        { // 0 < d < 50
            sum += all[i].get_speed();
            count++;
        }
    }
    // If there are boids close enough for alignment...
    if (count > 0)
    {
        sum = sum / (float)count;  // Divide sum by the number of close boids (average of velocity)
        sum = glm::normalize(sum); // Turn sum into a unit vector, and
        sum = sum * maxSpeed;      // Multiply by maxSpeed
        // Steer = Desired - Velocity
        glm::vec3 steer;
        steer = sum - get_speed(); // sum = desired(average)
        // steer.limit(maxForce); pas compris
        return steer;
    }
    else
    {
        glm::vec3 temp(0, 0, 0);
        return temp;
    }
}