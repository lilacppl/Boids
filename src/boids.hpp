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
    Boids(std::vector<Boid> vec);
    Boids(const int number);
    std::vector<Boid> getVect() const; // get le vector de Boids
    int               NumberOfBoids() const;
    Boid              getBoid(int id);
    void              addBoid(const Boid& boid);
    void              draw(p6::Context& ctx); // dessine tous les Boids
    // std::vector<double> alignement();
    // std::vector<double> cohesion();
    // std::vector<double> separation();
    void update(p6::Context& ctx); // contient draw, alignement ... pour tout regrouper
};

Boids::Boids(std::vector<Boid> vec)
    : m_boids(vec) {}

Boids::Boids(const int number)
{
    for (int i = 0; i < number; i++)
    {
        Boid b1;
        m_boids.push_back(b1);
    }
}
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
    for (auto& i : m_boids)
    {
        i.draw(ctx);
        i.move();
    }
}

void Boids::addBoid(const Boid& boid)
{
    m_boids.push_back(boid);
}


void Boids::update(p6::Context& ctx)
{
    this->draw(ctx);
    //mettre l'alignement et la cohesion
}