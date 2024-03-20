#include "scene.hpp"

void Scene::InitializeClasses()
{
    ImguiVariables imguivars; // initialisation des variables liées à imgui
    m_imguiVariables = imguivars;
    Boids boids2(m_imguiVariables.GetBoidsNumber()); // crée un flock de Boids de taille n
    m_first_boids = boids2;
}

void Scene::update(p6::Context& ctx)
{
    // m_imguiVariables.UpdateValues();
    // ctx.background(p6::NamedColor::CadetBlue);
    // ctx.square((p6::Center{}), p6::Radius{m_imguiVariables.GetSquareRadius()});
    // m_first_boids.update(ctx, m_imguiVariables.GetBoidsNumber(), m_imguiVariables.GetSquareRadius(), m_imguiVariables.GetNeighborDist(), m_imguiVariables.GetAvoidFactor(), m_imguiVariables.GetMaxSpeed(), m_imguiVariables.GetMinSpeed());
}