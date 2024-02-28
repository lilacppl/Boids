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
    void              alignement();
    void              cohesion();
    void              separation();
    void              update(p6::Context& ctx); // contient draw, alignement ... pour tout regrouper
    std::vector<Boid> other_boids(const Boid& b);
};
