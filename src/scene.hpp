
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
#include "probas.hpp"
#include "vertices.hpp"

class Scene {
private:
    ImguiVariables m_imguiVariables;
    Vertices       m_vertices;
    Boids          m_first_boids;
    Mesh           m_cube;
    Mesh           m_fish;
    Mesh           m_fishlow;
    Mesh           m_fishverylow;
    Mesh           m_shark;
    // MeshVec        m_fish_models;

    // FreeflyCamera m_camera;
    Program m_fish_program;
    Program m_cube_program;
    Program m_arpenteur_program;
    Program m_seaweed_program;
    Program m_shark_program;
    // std::vector<Program> programs ; //a faire
    Arpenteur m_arpenteur;
    Mesh      m_seaweed;
    Mesh      m_mushroom;
    // Mesh              m_stone;
    SceneObjectVector m_objects;
    glm::mat4         m_viewMatrix;
    Timer             m_chrono;

    int              m_current_time = 0;
    int              m_actual_state = 0;
    std::vector<int> m_events_tables{};
    const float      m_cube_size   = 10.0f;
    float            m_cube_hscale = 0.9f;
    bool             m_reset_time  = false;
    int              m_index       = 0;

public:
    // Scene(p6::Context& ctx);

public:
    Scene();
    void     Init(p6::Context& ctx);
    void     ResetChrono();
    void     update(const p6::Context& ctx);
    void     draw(const p6::Context& ctx) const;
    Mesh&    returnFishMeshUsingLodValue();
    Program& markovProgram();
    int      getState();
    void     setState(int a);
    void     cleanupRessources();
};

// static Program m_p0(textures[0], "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl");
// static Program m_p1(textures[1], "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl");
// static Program m_p2(textures[2], "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl");
// static Program m_p3(textures[3], "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl");
// static Program m_p4(textures[4], "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl");