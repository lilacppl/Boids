
#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "boids.hpp"
#include "cube.hpp"
#include "doctest/doctest.h"
#include "imguivariables.hpp"
// #include "p6/p6.h"

class Scene {
    // mettre les objets de la scene ici ?
    // camera par exemple ?
    // cube..
    // etc
private:
    ImguiVariables m_imguiVariables;
    Boids          m_first_boids;
    Cube           m_cube;

public:
    Scene();
    void InitializeClasses();
    void update(p6::Context& ctx);
};