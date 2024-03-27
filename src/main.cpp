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
#include "vao.hpp"
#include "vbo.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "boids.hpp"
#include "doctest/doctest.h"
#include "imguivariables.hpp"
#include "openglutils.hpp"

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

    // load obj
    std::string              inputfile = "../assets/untitled.obj";
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./assets"; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty())
    {
        std::cout << "TinyObjReader: " << reader.Warning();
    }
    auto& attrib    = reader.GetAttrib();
    auto& shapes    = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    std::vector<glimac::ShapeVertex> vertices;
    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            glimac::ShapeVertex v;
            v.position = glm::vec3{attrib.vertices[3 * index.vertex_index], attrib.vertices[3 * index.vertex_index + 1], attrib.vertices[3 * index.vertex_index + 2]};
            v.normal   = glm::vec3{attrib.normals[3 * index.vertex_index], attrib.normals[3 * index.vertex_index + 1], attrib.normals[3 * index.vertex_index + 2]};
            vertices.push_back(v);
        }
    }
    // Créer un VAO et lier le VBO
    VAO vao;
    VBO vbo(vertices);
    vao.bind();
    vbo.bind();
    vao.vertex_attrib();
    vbo.debind();
    vao.debind();

    const p6::Shader shader = p6::load_shader(
        "../shaders/3D.vs.glsl",
        "../shaders/normal.fs.glsl"
    );

    // const std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16); // création des vertices de la sphere

    // VBO vbo(vertices);
    // VAO vao;
    // vao.bind();
    // vbo.bind();
    // vao.vertex_attrib();
    // vbo.debind();
    // vao.debind();

    Scene       scene;
    std::string text = "Hello";
    ctx.imgui        = [&]() {
    };

    // Declare your infinite update loop.
    ctx.update = [&]() {
        // vao.bind();
        shader.use();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        // OpenGLUtils::draw_sphere(&shader, vertices, &ctx);
        // scene.update(ctx);
        // vao.debind();
        OpenGLUtils::draw_cube(&shader, vertices, &ctx, vao);
    };
    // Should be done last. It starts the infinite loop.
    ctx.start();
}