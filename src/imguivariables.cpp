#include "imguivariables.hpp"

void ImguiVariables::UpdateValues()
{
    ImGui::Begin("Change values");
    // ImGui::SliderFloat("Square size", &m_square_radius, 0.1f, 1.f);
    ImGui::SliderInt("Boids number", &m_boids_number, 1, 50);
    ImGui::SliderFloat("Neighbor distance", &m_neighbor_dist, 0.f, 2.f);
    ImGui::SliderFloat("Separation factor", &m_avoid_factor, 0.f, 0.1f);
    ImGui::SliderFloat("Max speed", &m_max_speed, 0.f, 0.02f);
    ImGui::SliderFloat("Min speed", &m_min_speed, 0.f, 0.01f);
    ImGui::SliderFloat("LOD", &m_lod_value, 1.f, 4.f);

    ImGui::End();
}

