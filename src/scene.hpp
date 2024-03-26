
#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../glimac/freefly_camera.hpp"
#include "boids.hpp"
#include "cube.hpp"
#include "doctest/doctest.h"
#include "imguivariables.hpp"

class Scene {
    // mettre les objets de la scene ici ?
    // camera par exemple ?
    // cube..
    // etc
private:
    ImguiVariables m_imguiVariables;
    Boids          m_first_boids;
    Cube           m_cube;
    FreeflyCamera  m_camera;

public:
    Scene();
    void Init(p6::Context& ctx);
    void update(p6::Context& ctx);
};