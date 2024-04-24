#include "scene.hpp"
#include <vector>
#include "probas.hpp"

Scene::Scene()
    : m_imguiVariables(), m_vertices(), m_first_boids(m_imguiVariables.GetBoidsNumber()), m_cube(m_vertices.cube), m_fish(m_vertices.fish), m_fish_program(textures[0], "../shaders/3D.vs.glsl", "../shaders/text3D.fs.glsl"), m_cube_program("../assets/cube_texture.jpg", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_arpenteur_program("./assets/arpenteur_color.png", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_seaweed_program("./assets/algue_color.png", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_seaweed(m_vertices.seaweed)
{
}

void Scene::Init(p6::Context& ctx)
{
    // ImguiVariables imguivars; // initialisation des variables liées à imgui
    // m_imguiVariables = imguivars;
    // Boids boids2(m_imguiVariables.GetBoidsNumber()); // crée un flock de Boids de taille n
    // m_first_boids = boids2;
    // m_camera.eventManager(ctx);
    // Mesh meh1(m_vertices.fish);
    // m_fish_models.push_back(meh1);
    // m_fish_models.push_back(m_vertices.fishlow);
    m_arpenteur.eventManager(ctx);
}

// Program& Scene::markov_program()
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

void Scene::update(const p6::Context& ctx)
{
    m_imguiVariables.UpdateValues();
    m_viewMatrix = m_arpenteur.getViewMatrix();
    glm::vec3 position(0.f, 0.f, 0.f);
    m_cube.DrawMesh(ctx, m_viewMatrix, m_cube_program, position, 10, glm::vec3(0, 0, 0), 1.);
    m_arpenteur.update(ctx, m_arpenteur_program);
    m_arpenteur.eventUpdate();
    // if (texture_markov(m_chrono))
    // {
    //     // m_fish_program = markov_program();
    // }
    m_first_boids.update(ctx, m_imguiVariables.GetBoidsNumber(), 5.0f, m_imguiVariables.GetNeighborDist(), m_imguiVariables.GetAvoidFactor(), m_imguiVariables.GetMaxSpeed(), m_imguiVariables.GetMinSpeed(), returnFishMeshUsingLodValue(), m_viewMatrix, m_fish_program);
}

void Scene::draw(const p6::Context& ctx) const
{
    m_objects.drawSceneObjOfSameMesh(m_objects.seaweed, m_seaweed, ctx, m_viewMatrix, m_seaweed_program);
    // m_objects.drawSceneObjOfSameMesh(m_objects.stone, m_stone, ctx, m_viewMatrix, m_stone_program);
}

Mesh& Scene::returnFishMeshUsingLodValue()
{
    if (m_imguiVariables.GetLodValue() < 2.0f)
        return m_fishlow;
    if (m_imguiVariables.GetLodValue() > 2.0f)
        return m_fish;
    else
        return m_cube;
}