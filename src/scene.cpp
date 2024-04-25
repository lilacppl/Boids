#include "scene.hpp"
#include <vector>
#include "probas.hpp"

Scene::Scene()
    : m_imguiVariables(), m_vertices(), m_first_boids(m_imguiVariables.GetBoidsNumber()), m_cube(m_vertices.cube), m_fish(m_vertices.fish), m_fishlow(m_vertices.fishlow), m_fishverylow(m_vertices.fishverylow), m_shark(m_vertices.shark), m_fish_program(textures[0], "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_cube_program("./assets/eau.png", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_arpenteur_program("./assets/arpenteur_color.png", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_seaweed_program("./assets/algue_color.png", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_shark_program("./assets/material_diffuse.png", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_seaweed(m_vertices.seaweed)
{
}

void Scene::Init(p6::Context& ctx)
{
    m_arpenteur.eventManager(ctx);
    m_events_tables = eventsTimes(2, 0);
}

// void Scene::ResetChrono()
// {
//     if (m_reset_time)
//         m_chrono.reset();
// };
// Program& Scene::markovProgram()
// {
//     switch (m_actual_state)
//     {
//     case 0:
//         return m_p0;
//         break;
//     case 1:
//         return m_p1;
//         break;
//     case 2:
//         return m_p2;
//         break;
//     case 3:
//         return m_p3;
//         break;
//     }
//     return m_p4;
// }

float random = rand01();

void Scene::update(const p6::Context& ctx)
{
    // taille du cube
    float cube_scale = 10.0;
    // hauteur du cube (appliquée en plus de la taille globale cube_scale)
    float height_scale = 1.0;
    // hauteur de la partie en y positifs du cube

    m_current_time = tempsEcoule(m_chrono);
    m_viewMatrix   = m_arpenteur.getViewMatrix();
    glm::vec3 position(0.f, 0.f, 0.f);

    // ResetChrono();

    // if (niveauEau(m_current_time, m_events_tables, 2)) // POUR POISSON c'est cette condition
    // {
    //     m_events_tables = eventsTimes(2, m_current_time);
    //     // hauteur du cube (appliquée en plus de la taille globale cube_scale)
    //     m_cube_hscale = uniform(0.3f, 1.0f);
    //     std::cout << "true" << std::endl;
    // }

    if (random < 0.2)
    {
        m_objects.drawShark(m_shark, ctx, m_viewMatrix, m_shark_program, m_imguiVariables, m_current_time);
        // std::cout << m_current_time << std::endl;
        // if (m_current_time > 20000)
        // {
        //     m_reset_time = true;
        //     std::cout << "shark" << std::endl;
        // }
        // else
        // {
        //     m_reset_time = false;
        // }
    }

    // hauteur de la partie en y positifs du cube
    float height = m_cube_size * m_cube_hscale / 2;

    m_imguiVariables.UpdateValues();
    m_viewMatrix = m_arpenteur.getViewMatrix();
    m_arpenteur.update(ctx, m_arpenteur_program, height, m_current_time);

    m_cube.DrawMesh(ctx, m_viewMatrix, m_cube_program, position, m_cube_size, glm::vec3(0, 0, 0), m_cube_hscale, m_current_time);
    m_arpenteur.update(ctx, m_arpenteur_program, height, m_current_time);
    m_arpenteur.eventUpdate();
    // if (texture_markov(m_chrono))
    // {
    //     // m_fish_program = markov_program();
    // }

    // std::cout << m_current_time << std::endl;

    m_first_boids.update(ctx, m_imguiVariables.GetBoidsNumber(), m_cube_size / 2.0, m_imguiVariables.GetNeighborDist(), m_imguiVariables.GetAvoidFactor(), m_imguiVariables.GetMaxSpeed(), m_imguiVariables.GetMinSpeed(), returnFishMeshUsingLodValue(), m_viewMatrix, m_fish_program, height, m_current_time);

    m_current_time = tempsEcoule(m_chrono);
}

void Scene::draw(const p6::Context& ctx) const
{
    m_objects.drawSceneObjOfSameMesh(m_objects.seaweed, m_seaweed, ctx, m_viewMatrix, m_seaweed_program, m_current_time);
    // m_objects.drawSceneObjOfSameMesh(m_objects.stone, m_stone, ctx, m_viewMatrix, m_stone_program);
}

Mesh& Scene::returnFishMeshUsingLodValue()
{
    if (m_imguiVariables.GetLodValue() < 3.0f)
    {
        if (m_imguiVariables.GetLodValue() < 2.0f)
        {
            return m_fishverylow;
        }
        else
            return m_fishlow;
    }
    else
        return m_fish;
}

int Scene::getState()
{
    return m_actual_state;
}

void Scene::setState(int a)
{
    m_actual_state = a;
}
