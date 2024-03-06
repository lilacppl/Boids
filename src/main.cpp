#pragma once

#include <cstdlib>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT
#include "boids.hpp"
#include "doctest/doctest.h"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();
    auto        square_radius = 0.5f;
    auto        boids_number  = 30;
    std::string text          = "Hello";
    ctx.imgui                 = [&]() {
        // Show a simple window
        ImGui::Begin("Test");
        ImGui::SliderFloat("Square size", &square_radius, 0.1f, 1.f);
        ImGui::SliderInt("Boids number", &boids_number, 1, 50);
        ImGui::End();
        // Show the official ImGui demo window
        // It is very useful to discover all the widgets available in ImGui
        ImGui::ShowDemoWindow();
    };

    // prep code
    Boids boids2(boids_number); // crée un flock de Boids de taille n

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::CadetBlue);
        ctx.square((p6::Center{}), p6::Radius{square_radius});
        boids2.update(ctx, square_radius);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}