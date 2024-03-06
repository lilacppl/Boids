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
    void              deleteBoid();
    void              changeSize(const int boids_number);
    void              draw(p6::Context& ctx, float square_radius, float maxspeed, float minspeed); // dessine tous les Boids
    void              alignement(float neighbor_dist);
    void              cohesion(float neighbor_dist);
    void              separation(float avoid_factor);
    void              update(p6::Context& ctx, int boids_number, float square_radius, float neighbor_dist, float avoid_factor, float maxspeed, float minspeed); // contient draw, alignement ... pour tout regrouper
    std::vector<Boid> other_boids(const Boid& b);
};
