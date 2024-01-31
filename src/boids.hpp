#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include "boid.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

// ensemble des Boids

class Boids {
private:
    std::vector<Boid> m_boids; // vecteur de Boid
    int               m_numberOfBoids;

public:
    Boids(std::vector<Boids> vec, int number);
    ~Boids() = default;
    Boid                getBoid(int id);
    void                addBoid(const Boid& boid);
    void                draw(p6::Context& ctx); // dessine tous les Boids
    std::vector<double> alignement();
    std::vector<double> cohesion();
    std::vector<double> separation();
};

Boids::Boids(std::vector<Boids> vec, int number)
    : m_boids(vec), m_numberOfBoids(number) {}

void Boids::draw(p6::Context& ctx)
{
}
