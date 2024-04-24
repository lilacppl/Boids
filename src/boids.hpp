#pragma once

#include <cstdlib>
#include <iostream>
// #include <type>
#include <vector>
#include "boid.hpp"
#include "doctest/doctest.h"
#include "imguivariables.hpp"
#include "iprogram.hpp"
#include "p6/p6.h"

// ensemble des Boids

class Boids {
private:
    std::vector<Boid> m_boids; // vecteur de Boid
    // String m_type;
    ImguiVariables m_variables;

    // Program m_program; // du coup on met le programme ici ??

public:
    Boids() = default;
    Boids(const std::vector<Boid> vec);
    Boids(const int number);
    std::vector<Boid> getVect() const; // get le vector de Boids
    int               numberOfBoids() const;
    Boid              getBoid(const int id);
    void              addBoid(const Boid& boid);
    void              deleteBoid();
    void              changeSize(const int boids_number);
    void              draw(const p6::Context& ctx, const float square_radius, const float maxspeed, const float minspeed, const Mesh& mesh, const glm::mat4 viewmatrix, const Program& program); // dessine tous les Boids
    void              alignement(const float neighbor_dist);
    void              cohesion(const float neighbor_dist);
    void              separation(const float avoid_factor);
    // void              update(p6::Context& ctx, int boids_number, float square_radius, float neighbor_dist, float avoid_factor, float maxspeed, float minspeed); // contient draw, alignement ... pour tout regrouper
    void              update(const p6::Context& ctx, const int boids_number, const float square_radius, const float neighbor_dist, const float avoid_factor, const float maxspeed, const float minspeed, const Mesh& mesh, const glm::mat4 viewmatrix, const Program& program);
    std::vector<Boid> other_boids(const Boid& b);
};
