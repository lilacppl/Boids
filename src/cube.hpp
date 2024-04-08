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

class Cube { // Mesh
private:
    float                            m_size;
    std::vector<glimac::ShapeVertex> m_vertices; // a faire : stocker les vertices en dehors : on veut faire mesh(vertices) pour générer le mesh, cela économise de la place, mais on est obligé de stocker une size de vertices quand meme

    img::Image m_texture = p6::load_image_buffer("../assets/cube_texture.jpg");
    p6::Shader m_shader  = p6::load_shader("../shaders/3D.vs.glsl", "../shaders/text3D.fs.glsl");
    VBO        m_vbo;
    VAO        m_vao;
    GLuint     m_texture_uint; // a faire : classe texture qui marche comme les vao et vbo pour qu'on puisse suppr une texture
    int        m_vertices_size;

public:
    Cube()
        : m_size(10.0f)
    {
        initCube(); // Initialisation du cube
    }

    // Mesh(std::vector<glimac::ShapeVertex> vertices)
    //  {
    //       OpenGLUtils::init_vao(m_vao, m_vbo, vertices);
    // m_vertices_size = vertices.size();
    //   m_texture_uint = OpenGLUtils::texture(m_texture);
    // }

    void initCube() // création d'un cube
    {
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

        OpenGLUtils::init_vao(m_vao, m_vbo, m_vertices);
        // m_shader = p6::load_shader("../shaders/3D.vs.glsl", "../shaders/normal.fs.glsl");//essayer  de changer le shader ici ??
        // m_texture = p6::load_image_buffer("../assets/text.png");

        m_texture_uint = OpenGLUtils::texture(m_texture);
    }
    void DrawCube(p6::Context& ctx, glm::mat4& viewmatrix)
    {
        m_shader.use();
        glEnable(GL_DEPTH_TEST);
        OpenGLUtils::draw_cube(&m_shader, m_vertices, &ctx, m_vao, viewmatrix, m_texture_uint);
    }
};