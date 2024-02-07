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
    glm::vec3 m_direction;
    glm::vec3 m_speed;
    float     maxSpeed;
    float     maxForce;

public:
    Boid();
    ~Boid() = default;
    glm::vec3 get_position() const;
    glm::vec3 get_direction() const;
    glm::vec3 get_speed() const;
    void      set_position(glm::vec3& vect);
    void      set_direction(glm::vec3& vect);
    void      set_speed(glm::vec3& vect);
    void      move();
    void      draw(p6::Context& ctx);
};

Boid::Boid()
    : m_position(glm::vec3{0, 0, 0}), m_direction(glm::vec3{1, 1, 0}), m_speed(glm::vec3{0.001, 0.001, 0}) {}

glm::vec3 Boid::get_position() const
{
    return m_position;
}

glm::vec3 Boid::get_direction() const
{
    return m_direction;
}
glm::vec3 Boid::get_speed() const
{
    return m_speed;
}

void Boid::set_position(glm::vec3& vect)
{
    m_position = vect;
}
void Boid::set_direction(glm::vec3& vect)
{
    m_direction = vect;
}
void Boid::set_speed(glm::vec3& vect)
{
    m_speed = vect;
}

void Boid::draw(p6::Context& ctx)
{
    ctx.fill = {1, 1, 1, 0.5};
    ctx.square(p6::Center{get_position()}, p6::Radius{0.05f});
}

void Boid::move()
{
    glm::vec3 new_pos = get_speed() + get_position();
    set_position(new_pos);
}