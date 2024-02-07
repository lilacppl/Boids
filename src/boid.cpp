#pragma once

#include "boid.hpp"

static constexpr float maxSpeed = 5;
static constexpr float maxForce = 10;

Boid::Boid()
    : m_position(glm::vec3{0, 0, 0}), m_speed(glm::vec3{0.001, 0.001, 0}) {}

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
    ctx.square(p6::Center{get_position()}, p6::Radius{0.05f});
}

void Boid::move()
{
    glm::vec3 new_pos = get_speed() + get_position();
    m_position        = new_pos;
}