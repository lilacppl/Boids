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
    // int               m_numberOfBoids;

public:
    Boids(std::vector<Boid> vec, int number);
    ~Boids() = default;
    std::vector<Boid>   getVect() const; // get le vector de Boids
    int                 NumberOfBoids() const;
    Boid                getBoid(int id);
    void                addBoid(const Boid& boid);
    void                draw(p6::Context& ctx); // dessine tous les Boids
    std::vector<double> alignement();
    std::vector<double> cohesion();
    std::vector<double> separation();
};

Boids::Boids(std::vector<Boid> vec, int number)
    : m_boids(vec), m_numberOfBoids(number) {}

std::vector<Boid> Boids::getVect() const
{ // getter du vecteur de boids
    std::vector<Boid> boids = m_boids;
    return (boids);
}

int Boids::NumberOfBoids() const
{
    return (m_boids.size());
}

void Boids::draw(p6::Context& ctx)
{
}

void Boids::addBoid(const Boid& boid)
{
    getVect().push_back(std::move(boid));
}
