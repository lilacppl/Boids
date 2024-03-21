
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../glimac/common.hpp"
#include "../glimac/sphere_vertices.hpp"
#include "p6/p6.h"
#include "scene.hpp"
#include "vao.hpp"
#include "vbo.hpp"

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
    // const p6::Shader shader = p6::load_shader(
    //     "shaders/3D.vs.glsl",
    //     "shaders/normal.fs.glsl"
    // );

    const std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16); // création des vertices de la sphere

    // VBO
    VBO vbo(vertices);
    VAO vao;
    vao.bind();
    static constexpr GLuint pos1 = 0;
    static constexpr GLuint pos2 = 1;
    static constexpr GLuint pos3 = 2;

    vbo.bind();
    // vao.vertex_attrib(&pos, &norm, &color);
    glEnableVertexAttribArray(pos1);
    glEnableVertexAttribArray(pos2);
    glEnableVertexAttribArray(pos3);

    // on spécifie les attributs du vertex
    glVertexAttribPointer(pos1, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), nullptr);
    glVertexAttribPointer(pos2, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, normal)));
    glVertexAttribPointer(pos3, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, texCoords)));
    vbo.debind();
    vao.debind();

    Scene scene;
    scene.InitializeClasses();
    std::string text = "Hello";
    ctx.imgui        = [&]() {
    };
    vao.bind();
    // Declare your infinite update loop.
    ctx.update = [&]() {
        // shader.use();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        scene.update(ctx);
    };
    vbo.debind();
    // Should be done last. It starts the infinite loop.
    ctx.start();

    // bug dans le vertex shader : matrice pas passée
}