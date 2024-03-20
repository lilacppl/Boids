#pragma once

#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../glimac/common.hpp"
#include "../glimac/sphere_vertices.hpp"
#include "p6/p6.h"
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

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    const p6::Shader shader = p6::load_shader(
        "../shaders/3D.vs.glsl",
        "../shaders/normal.fs.glsl"
    );

    const std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16); // création des vertices de la sphere

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