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

int Boids::NumberOfBoids() const
{
    return (m_boids.size());
}

void Boids::draw(p6::Context& ctx, float square_radius)
{
    for (auto& i : m_boids)
    {
        i.draw(ctx);
        i.move(square_radius);
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
    if (boids_number > this->NumberOfBoids())
    {
        for (unsigned int i = 0; i < (boids_number - NumberOfBoids()); i++)
        {
            Boid newboid;
            this->addBoid(newboid);
        }
    }
    else if (boids_number < this->NumberOfBoids())
    {
        for (unsigned int i = 0; i < (NumberOfBoids() - boids_number); i++)
        {
            this->deleteBoid();
        }
    }
}

std::vector<Boid> Boids::other_boids(const Boid& active_boid)
{
    std::vector<Boid> others;
    for (Boid& boid : m_boids)
    {
        if (boid.get_position() != active_boid.get_position() && boid.get_speed() != active_boid.get_speed())
        {
            others.push_back(boid);
        }
    }
    return others;
}

void Boids::update(p6::Context& ctx, float square_radius)
{
    alignement();
    cohesion();
    draw(ctx, square_radius);
}

void Boids::alignement()
{
    float neighbordist    = 0.1; // Field of vision
    float matching_factor = 1;

    for (auto& b : m_boids) // on boucle sur chaque boid
    {
        glm::vec3 sum(0, 0, 0);
        int       neighboring_boids = 0;
        for (auto& other_b : other_boids(b)) // pour chaque autre boid existant :
        {
            float distance = 0;
            for (int i = 0; i < 3; i++)
            {
                distance += (b.get_position()[i] - other_b.get_position()[i]) * (b.get_position()[i] - other_b.get_position()[i]);
            }
            distance = std::sqrt(distance);
            if (distance < neighbordist) // si l'autre boid est assez proche, on ajoute sa vitesse à la somme
            {
                sum += other_b.get_speed();
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

void Boids::cohesion()
{
    float neighbordist     = 0.1; // Field of vision
    float centering_factor = 0.1;

    for (auto& b : m_boids) // on boucle sur chaque boid
    {
        glm::vec3 sum(0, 0, 0); // somme des positions
        int       neighboring_boids = 0;
        for (auto& other_b : other_boids(b)) // pour chaque autre boid existant :
        {
            float distance = 0;
            for (int i = 0; i < 3; i++)
            {
                distance += (b.get_position()[i] - other_b.get_position()[i]) * (b.get_position()[i] - other_b.get_position()[i]);
            }
            distance = std::sqrt(distance);
            if (distance < neighbordist) // si l'autre boid est assez proche, on ajoute sa vitesse à la somme
            {
                sum += other_b.get_speed();
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