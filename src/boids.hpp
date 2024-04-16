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
    Boids(std::vector<Boid> vec);
    Boids(const int number);
    std::vector<Boid> getVect() const; // get le vector de Boids
    int               NumberOfBoids() const;
    Boid              getBoid(int id);
    void              addBoid(const Boid& boid);
    void              deleteBoid();
    void              changeSize(const int boids_number);
    void              draw(p6::Context& ctx, float square_radius, float maxspeed, float minspeed, Mesh& mesh, glm::mat4 viewmatrix, Program& program); // dessine tous les Boids
    void              alignement(float neighbor_dist);
    void              cohesion(float neighbor_dist);
    void              separation(float avoid_factor);
    // void              update(p6::Context& ctx, int boids_number, float square_radius, float neighbor_dist, float avoid_factor, float maxspeed, float minspeed); // contient draw, alignement ... pour tout regrouper
    void              update(p6::Context& ctx, int boids_number, float square_radius, float neighbor_dist, float avoid_factor, float maxspeed, float minspeed, Mesh& mesh, glm::mat4 viewmatrix, Program& program);
    std::vector<Boid> other_boids(const Boid& b);
};
