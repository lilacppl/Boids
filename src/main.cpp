#pragma once
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../glimac/common.hpp"
#include "../glimac/sphere_vertices.hpp"
#include "boid3d.hpp"
#include "p6/p6.h"
#include "scene.hpp"
// #include "vao.hpp"
// #include "vbo.hpp"

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

    VBO vbo(vertices);
    VAO vao;
    vao.bind();
    vbo.bind();
    vao.vertex_attrib();
    vbo.debind();
    vao.debind();

    // Scene scene;
    // scene.InitializeClasses();
    std::string text = "Hello";
    ctx.imgui        = [&]() {
    };
    // Declare your infinite update loop.
    ctx.update = [&]() {
        vao.bind();
        shader.use();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        draw_sphere(&shader, vertices, &ctx);
        // scene.update(ctx)
        vao.debind();
    };
    // Should be done last. It starts the infinite loop.
    ctx.start();

    // bug dans le vertex shader : matrice pas passée
}