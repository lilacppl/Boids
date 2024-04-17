#include "scene.hpp"

Scene::Scene()
    : m_imguiVariables(), m_vertices(), m_first_boids(m_imguiVariables.GetBoidsNumber()), m_cube(m_vertices.cube), m_fish(m_vertices.fish), m_fish_program("./assets/ecaille.png", "./shaders/3D.vs.glsl", "../shaders/text3D.fs.glsl"), m_cube_program("./assets/cube_texture.jpg", "../shaders/3D.vs.glsl", "../shaders/text3D.fs.glsl"), m_arpenteur()
{
}

void Scene::Init(p6::Context& ctx)
{
    // ImguiVariables imguivars; // initialisation des variables liées à imgui
    // m_imguiVariables = imguivars;
    // Boids boids2(m_imguiVariables.GetBoidsNumber()); // crée un flock de Boids de taille n
    // m_first_boids = boids2;
    // m_camera.eventManager(ctx);
    m_arpenteur.eventManager(ctx);
}

void Scene::update(p6::Context& ctx)
{
    m_imguiVariables.UpdateValues();
    glm::mat4 viewMatrix = m_arpenteur.getViewMatrix();
    glm::vec3 position(0.f, 0.f, 0.f);
    m_cube.DrawMesh(ctx, viewMatrix, m_cube_program, position, 10);
    m_arpenteur.update(ctx, m_fish_program);
    m_arpenteur.eventUpdate();
    // m_fish.DrawMesh(ctx, viewMatrix, 0.5, m_fish_program);
    m_first_boids.update(ctx, m_imguiVariables.GetBoidsNumber(), 100, m_imguiVariables.GetNeighborDist(), m_imguiVariables.GetAvoidFactor(), m_imguiVariables.GetMaxSpeed(), m_imguiVariables.GetMinSpeed(), m_fish, viewMatrix, m_fish_program);
    // ctx.square((p6::Center{}), p6::Radius{m_imguiVariables.GetSquareRadius()});
    // m_first_boids.update(ctx, m_imguiVariables.GetBoidsNumber(), m_imguiVariables.GetSquareRadius(), m_imguiVariables.GetNeighborDist(), m_imguiVariables.GetAvoidFactor(), m_imguiVariables.GetMaxSpeed(), m_imguiVariables.GetMinSpeed());
}