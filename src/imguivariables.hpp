#pragma once
#include <cstdlib>
#include <iostream>
#include "doctest/doctest.h"
#include "imguivariables.hpp"
#include "p6/p6.h"

class ImguiVariables {
private:
    float m_square_radius = 0.5f;
    int   m_boids_number  = 30;
    float m_neighbor_dist = 0.15f;
    float m_avoid_factor  = 0.02f;
    float m_max_speed     = 0.006f;
    float m_min_speed     = 0.002f;

public:
    ImguiVariables() = default;
    void  UpdateValues();
    float GetSquareRadius() const { return m_square_radius; }
    int   GetBoidsNumber() const { return m_boids_number; }
    float GetNeighborDist() const { return m_neighbor_dist; }
    float GetAvoidFactor() const { return m_avoid_factor; }
    float GetMaxSpeed() const { return m_max_speed; }
    float GetMinSpeed() const { return m_min_speed; }
};