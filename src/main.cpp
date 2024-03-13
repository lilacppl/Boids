#pragma once

#include <cstdlib>
#include <vector>
#include "scene.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "boids.hpp"
#include "doctest/doctest.h"
#include "imguivariables.hpp"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();
    Scene scene;
    scene.InitializeClasses();
    std::string text = "Hello";
    ctx.imgui        = [&]() {
    };

    // Declare your infinite update loop.
    ctx.update = [&]() {
        scene.update(ctx);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}