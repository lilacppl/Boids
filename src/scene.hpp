
#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../glimac/freefly_camera.hpp"
#include "arpenteur.hpp"
#include "boids.hpp"
#include "doctest/doctest.h"
#include "imguivariables.hpp"
#include "iprogram.hpp"
#include "mesh.hpp"
#include "objectsvector.hpp"
#include "vertices.hpp"
#include "probas.hpp"

class Scene {
private:
    ImguiVariables m_imguiVariables;
    Vertices       m_vertices;
    Boids          m_first_boids;
    Mesh           m_cube;
    Mesh           m_fish;
    // FreeflyCamera  m_camera;
    Program m_fish_program;
    Program m_cube_program;
    Program m_arpenteur_program;
    Program m_seaweed_program;
    // std::vector<Program> programs ; //a faire
    Arpenteur m_arpenteur;
    // std::vector<Mesh> m_seaweed;
    Mesh              m_seaweed;
    SceneObjectVector m_objects;
    glm::mat4         m_viewMatrix;

public:
    // Scene(p6::Context& ctx);
    Scene();
    void Init(p6::Context& ctx);
    void update(p6::Context& ctx);
    void draw(p6::Context& ctx);
};