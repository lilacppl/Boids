#pragma once

#include "boids.hpp"
#include <cmath>
#include <cstdlib>

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

int Boids::numberOfBoids() const
{
    return (m_boids.size());
}

void Boids::draw(const p6::Context& ctx, const float square_radius, const float maxspeed, const float minspeed, const Mesh& mesh, const glm::mat4 viewmatrix, const Program& program, float& height)
{
    for (auto& i : m_boids)
    {
        // i.draw(ctx);
        i.draw(ctx, mesh, viewmatrix, program);
        i.move(square_radius, maxspeed, minspeed, height);
    }
}

void Boids::addBoid(const Boid& boid)
{
    m_boids.push_back(boid);
}
void Boids::deleteBoid()
{
    m_boids.pop_back();
}
void Boids::changeSize(const int boids_number)
{
    if (boids_number > this->numberOfBoids())
    {
        for (unsigned int i = 0; i < (boids_number - numberOfBoids()); i++)
        {
            Boid newboid;
            this->addBoid(newboid);
        }
    }
    else if (boids_number < this->numberOfBoids())
    {
        for (unsigned int i = 0; i < (numberOfBoids() - boids_number); i++)
        {
            this->deleteBoid();
        }
    }
}

std::vector<Boid> Boids::otherBoids(const Boid& active_boid)
{
    std::vector<Boid> others;
    for (Boid& boid : m_boids)
    {
        if (boid.getPosition() != active_boid.getPosition() && boid.getSpeed() != active_boid.getSpeed())
        {
            others.push_back(boid);
        }
    }
    return others;
}

void Boids::update(const p6::Context& ctx, const int boids_number, const float square_radius, const float neighbor_dist, const float avoid_factor, const float maxspeed, const float minspeed, const Mesh& mesh, const glm::mat4 viewmatrix, const Program& program,float & height)
{
    alignement(neighbor_dist);
    cohesion(neighbor_dist);
    separation(avoid_factor);
    changeSize(boids_number);
    draw(ctx, square_radius, maxspeed, minspeed, mesh, viewmatrix, program,height);
}

void Boids::alignement(const float neighbor_dist)
{
    // float neighbordist    = 0.15; // Field of vision
    float matching_factor = 0.01;

    for (auto& b : m_boids) // on boucle sur chaque boid
    {
        glm::vec3 sum(0, 0, 0);
        int       neighboring_boids = 0;
        for (auto& other_b : otherBoids(b)) // pour chaque autre boid existant :
        {
            float distance = 0;
            for (int i = 0; i < 3; i++)
            {
                distance += (b.getPosition()[i] - other_b.getPosition()[i]) * (b.getPosition()[i] - other_b.getPosition()[i]);
            }
            distance = std::sqrt(distance);
            if (distance < neighbor_dist) // si l'autre boid est assez proche, on ajoute sa vitesse à la somme
            {
                sum += other_b.getSpeed();
                neighboring_boids++;
            }
        }

        if (neighboring_boids > 0) // si il y a plus d'un boid dans la zone d'alignement
        {
            sum = sum / (float)neighboring_boids; // on moyenne les vitesses des boids dans la zone
            for (int i = 0; i < 2; i++)
            {
                b.m_speed[i] += (sum[i] - b.m_speed[i]) * matching_factor;
            }
        }
    }
}

void Boids::cohesion(const float neighbor_dist)
{
    // float neighbordist     = 0.15; // Field of vision
    float centering_factor = 0.01;

    for (auto& b : m_boids) // on boucle sur chaque boid
    {
        glm::vec3 sum(0, 0, 0); // somme des positions
        int       neighboring_boids = 0;
        for (auto& other_b : otherBoids(b)) // pour chaque autre boid existant :
        {
            float distance = 0;
            for (int i = 0; i < 3; i++)
            {
                distance += (b.getPosition()[i] - other_b.getPosition()[i]) * (b.getPosition()[i] - other_b.getPosition()[i]);
            }
            distance = std::sqrt(distance);
            if (distance < neighbor_dist) // si l'autre boid est assez proche, on ajoute sa vitesse à la somme
            {
                sum += other_b.getSpeed();
                neighboring_boids++;
            }
        }
        if (neighboring_boids > 0) // si il y a plus d'un boid dans la zone d'alignement
        {
            sum = sum / (float)neighboring_boids; // on moyenne les positions des boids dans la zone
            for (int i = 0; i < 2; i++)
            {
                b.m_speed[i] += (sum[i] - b.m_speed[i]) * centering_factor;
            }
        }
    }
}

void Boids::separation(const float avoid_factor)
{
    float neighborprotect = 0.09;
    // float avoidfactor     = 0.02;
    float close_dx, close_dy;
    for (auto& b : m_boids)
    {
        close_dx = 0;
        close_dy = 0;
        for (auto& other_b : otherBoids(b))
        {
            float distance = 0;
            for (int i = 0; i < 3; i++)
            {
                distance += (b.getPosition()[i] - other_b.getPosition()[i]) * (b.getPosition()[i] - other_b.getPosition()[i]);
            }
            distance = std::sqrt(distance);
            if (distance < neighborprotect) // si l'autre boid est assez proche, on ajoute sa vitesse à la somme
            {
                close_dx += b.m_position[0] - other_b.m_position[0];
                close_dy += b.m_position[1] - other_b.m_position[1];
            }
        }
        b.m_speed[0] += close_dx * avoid_factor;
        b.m_speed[1] += close_dy * avoid_factor;
    }
}