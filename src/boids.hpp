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
    Boids();
    ~Boids() = default;
    Boid                getBoid(int id);
    void                addBoid(const Boid& boid);
    void                draw(p6::Context& ctx); // dessine tous les Boids
    std::vector<double> alignement();
    std::vector<double> cohesion();
    std::vector<double> separation();
};

Boids::Boids()
    : m_boids(std::vector<Boids>{}), m_numberOfBoids(8) {}

void Boids::draw(p6::Context& ctx)
{
}
