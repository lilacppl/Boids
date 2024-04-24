#include "probas.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "scene.hpp"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    const p6::Shader shader = p6::load_shader(
        "../shaders/3D.vs.glsl",
        "../shaders/text3D.fs.glsl"
    );
    Scene      scene;
    scene.Init(ctx);
    std::string text = "Hello";
    ctx.imgui        = [&]() {
    };

    ctx.update = [&]() {

        // vao.bind();
        shader.use();
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        // OpenGLUtils::draw_sphere(&shader, vertices, &ctx);
        scene.update(ctx);
        scene.draw(ctx);
    };
    // Should be done last. It starts the infinite loop.
    ctx.start();
}