#include "scene.hpp"
#include <vector>
#include "probas.hpp"

Scene::Scene()
    : m_imguiVariables(), m_vertices(), m_first_boids(m_imguiVariables.GetBoidsNumber()), m_cube(m_vertices.cube), m_fish(m_vertices.fish), m_fishlow(m_vertices.fishlow), m_fishverylow(m_vertices.fishverylow), m_shark(m_vertices.shark), m_fish_program(textures[0], "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_cube_program("./assets/eau.png", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_arpenteur_program("./assets/arpenteur_color.png", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_seaweed_program("./assets/algue_color.png", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_shark_program("./assets/material_diffuse.png", "../shaders/3D.vs.glsl", "../shaders/Light.fs.glsl"), m_seaweed(m_vertices.seaweed), m_mushroom(m_vertices.mushroom)
{
}

void Scene::Init(p6::Context& ctx)
{
    m_arpenteur.eventManager(ctx);
    m_events_tables = eventsTimes(2, 0, 500);
    // m_events_tables2 = eventsTimes(3, 0, 10000);
    m_events_shark = eventsTimesShark(0, 10000, 300); // genere un intervalle de debut aléatoire
}

float random = rand01();
void  Scene::ResetChrono()
{
    if (m_reset_time)
        m_chronoreset.reset();
};

void Scene::update(const p6::Context& ctx)
{
    m_index++;
    m_current_time = tempsEcoule(m_chrono);
    float chrono2  = tempsEcoule(m_chronoreset);
    m_viewMatrix   = m_arpenteur.getViewMatrix();
    glm::vec3 position(0.f, 0.f, 0.f);

    if (niveauEau(m_index, m_events_tables, 2, 500))
    {
        // std::cout << m_events_tables[0] << std::endl;
        m_cube_hscale = loiNormale(0.8, 0.1);
        if (m_cube_hscale < 0.5)
            m_cube_hscale = 0.99;
    }

    // int spawn_time   = m_events_shark.first;
    // int despawn_time = m_events_shark.second;
    // std::cout << spawn_time << std::endl;

    // if (m_index >= spawn_time && m_index <= despawn_time)
    // {
    //     std::cout << "requin" << std::endl;
    //     m_objects.drawShark(m_shark, ctx, m_viewMatrix, m_shark_program, m_imguiVariables, m_current_time);
    // }

    for (const auto& event : m_events_shark)
    {
        int spawn_time   = event.first;
        int despawn_time = event.second;

        // Vérifier si m_index se trouve dans l'intervalle [spawn_time, despawn_time]
        if (m_index >= spawn_time && m_index <= despawn_time)
        {
            std::cout << "requin" << std::endl;
            m_objects.drawShark(m_objects.shark[0], m_shark, ctx, m_viewMatrix, m_shark_program, m_imguiVariables, m_current_time);
        }
    }

    // hauteur de la partie en y positifs du cube
    float height = m_cube_size * m_cube_hscale / 2;

    m_imguiVariables.UpdateValues();
    m_viewMatrix = m_arpenteur.getViewMatrix();
    m_arpenteur.update(ctx, m_arpenteur_program, height, m_current_time);
    // m_objects.drawShark(m_objects.shark[0], m_shark, ctx, m_viewMatrix, m_shark_program, m_imguiVariables, m_current_time);

    // m_cube.DrawMesh(ctx, m_viewMatrix, m_cube_program, position, m_cube_size, glm::vec3(0, 0, 0), m_cube_hscale, m_current_time);
    m_arpenteur.eventUpdate();
    // if (texture_markov(m_chrono))
    // {
    //     // m_fish_program = markov_program();
    // }

    // std::cout << m_current_time << std::endl;

    m_first_boids.update(ctx, m_imguiVariables.GetBoidsNumber(), m_cube_size / 2.0, m_imguiVariables.GetNeighborDist(), m_imguiVariables.GetAvoidFactor(), m_imguiVariables.GetMaxSpeed(), m_imguiVariables.GetMinSpeed(), returnFishMeshUsingLodValue(), m_viewMatrix, m_fish_program, height, m_current_time);

    // m_current_time = tempsEcoule(m_chrono);
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

void Scene::cleanupRessources()
{
    m_fish_program.deleteTextureBufferArray();
    m_cube_program.deleteTextureBufferArray();
    m_arpenteur_program.deleteTextureBufferArray();
    m_seaweed_program.deleteTextureBufferArray();
    m_shark_program.deleteTextureBufferArray();
    m_cube.DeleteVboVao();
    m_fish.DeleteVboVao();
    m_fishlow.DeleteVboVao();
    m_fishverylow.DeleteVboVao();
    m_shark.DeleteVboVao();
    m_seaweed.DeleteVboVao();
    m_mushroom.DeleteVboVao();
}
