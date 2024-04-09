
#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../glimac/freefly_camera.hpp"
#include "arpenteur.hpp"
#include "boids.hpp"
#include "mesh.hpp"
#include "doctest/doctest.h"
#include "imguivariables.hpp"
#include "vertices.hpp"


class Scene {
private:
    ImguiVariables m_imguiVariables;
    Vertices       m_vertices;
    Boids          m_first_boids;
    Mesh           m_cube;
    FreeflyCamera  m_camera;


public:
    Scene();
    void Init(p6::Context& ctx);
    void update(p6::Context& ctx);
};