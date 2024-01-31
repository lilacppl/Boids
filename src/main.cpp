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
    std::string text          = "Hello";
    ctx.imgui                 = [&]() {
        // Show a simple window
        ImGui::Begin("Test");
        ImGui::SliderFloat("Square size", &square_radius, 0.f, 1.f);
        ImGui::InputText("Text", &text);
        ImGui::End();
        // Show the official ImGui demo window
        // It is very useful to discover all the widgets available in ImGui
        // ImGui::ShowDemoWindow();
    };

    // prep code
    std::vector<Boids> boids_vector;
    Boids              b1;
    boids_vector.push_back(b1);
    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::CadetBlue);
        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
        ctx.square(p6::Center{}, p6::Radius{square_radius});
        // boids_vector[1].draw(ctx);
        //b1.draw(ctx);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}