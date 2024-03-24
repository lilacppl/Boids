#pragma once
// #include <glm/ext/matrix_clip_space.hpp>
// #include <glm/ext/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include "../glimac/common.hpp"
// #include "../glimac/freefly_camera.hpp"
// #include "../glimac/sphere_vertices.hpp"
#include "boid3d.hpp"
#include "openglutils.hpp"

// #include "p6/p6.h"

class Cube {
private:
    float                            m_size;
    std::vector<glimac::ShapeVertex> m_vertices;
    img::Image                       m_firsttexture  = OpenGLUtils::loadTexture("text2.png");
    img::Image                       m_secondtexture = OpenGLUtils::loadTexture("CloupMap.jpg");
    p6::Shader                       m_shader        = p6::Shader("3D.vs.glsl", "normal.fs.glsl");
    VBO                              m_vbo;
    VAO                              m_vao;

public:
    void initCube() // création d"un cube
    {
        m_size     = 1.0;
        m_vertices = {
            // face arriere
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 0)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 0)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 0)},
            // Face avant
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 0)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 0)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 0)},

            // Face gauche
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 0)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 1)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
            // // // Face droite
            {glm::vec3(0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 0)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 1)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 0)},
            // // // Face inférieure
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 0)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
            // // // // Face supérieure
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 0)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
        };
        // m_vbo(m_vertices); //faire un nouveau constructeur pour le vbo
        //  m_firsttexture  = OpenGLUtils::loadTexture("text2.png");
        //  m_secondtexture = OpenGLUtils::loadTexture("CloudMap.jpg");
        //  m_shader        = OpenGLUtils::loadShader("3D.vs.glsl", "normal.fs.glsl");
        OpenGLUtils::init_vao_vbo(m_vertices);
        // GLuint text1 = OpenGLUtils::texture(m_firsttexture);
    }
    void DrawCube(auto ctx)
    {
        m_shader.use();
        glEnable(GL_DEPTH_TEST);
        OpenGLUtils::draw_sphere(&m_shader, m_vertices, &ctx);
    }
};