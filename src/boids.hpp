#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include "doctest/doctest.h"
#include "p6/p6.h"

class Boids {
public:
    std::vector<double> m_position[3];
    std::vector<double> m_direction[3];
    std::vector<double> m_speed[3];

    Boids();
    ~Boids() = default;
    void move();
    void draw(auto ctx);
};

Boids::Boids()
    : m_position(std::vector<double>{0, 0, 0}), m_direction(std::vector<double>{0, 1, 0}), m_speed(std::vector<double>{0.5, 0.5, 1}) {}

void Boids::draw(auto ctx)
{
    ctx.fill = {1, 1, 1, 0.5};
    ctx.square(p6::Center{}, p6::Radius{0.3f});
}

void Boids::move()
{
}