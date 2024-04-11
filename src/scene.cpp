#include "scene.hpp"

Scene::Scene()
    : m_imguiVariables(), m_vertices(), m_first_boids(m_imguiVariables.GetBoidsNumber()), m_cube(m_vertices.cube), m_camera(), m_fish(m_vertices.fish)
{
}

void Scene::Init(p6::Context& ctx)
{
    // ImguiVariables imguivars; // initialisation des variables liées à imgui
    // m_imguiVariables = imguivars;
    // Boids boids2(m_imguiVariables.GetBoidsNumber()); // crée un flock de Boids de taille n
    // m_first_boids = boids2;
    m_camera.eventManager(ctx);
}

void Scene::update(p6::Context& ctx)
{
    m_imguiVariables.UpdateValues();
    m_camera.eventUpdate();
    glm::mat4 viewMatrix = m_camera.getViewMatrix();
    m_cube.DrawMesh(ctx, viewMatrix);
    m_fish.DrawMesh(ctx, viewMatrix);
    // ctx.square((p6::Center{}), p6::Radius{m_imguiVariables.GetSquareRadius()});
    // m_first_boids.update(ctx, m_imguiVariables.GetBoidsNumber(), m_imguiVariables.GetSquareRadius(), m_imguiVariables.GetNeighborDist(), m_imguiVariables.GetAvoidFactor(), m_imguiVariables.GetMaxSpeed(), m_imguiVariables.GetMinSpeed());
}