#pragma once
// #include <glm/ext/matrix_clip_space.hpp>
// #include <glm/ext/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include "../glimac/common.hpp"
// #include "../glimac/freefly_camera.hpp"
// #include "../glimac/sphere_vertices.hpp"
#include "boid3d.hpp"
#include "iprogram.hpp"
#include "openglutils.hpp"
#include "p6/p6.h"

class Mesh { // Mesh
private:
    float m_size;
    // std::vector<glimac::ShapeVertex> m_vertices; // a faire : stocker les vertices en dehors : on veut faire mesh(vertices) pour générer le mesh, cela économise de la place, mais on est obligé de stocker une size de vertices quand meme

    // img::Image m_texture = p6::load_image_buffer("../assets/cube_texture.jpg");
    // p6::Shader m_shader  = p6::load_shader("../shaders/3D.vs.glsl", "../shaders/text3D.fs.glsl");
    VBO m_vbo;
    VAO m_vao;
    // GLuint m_texture_uint; // a faire : classe texture qui marche comme les vao et vbo pour qu'on puisse suppr une texture
    int m_vertices_size;

public:
    // Cube()
    //     : m_size(10.0f)
    // {
    //     initCube(); // Initialisation du cube
    // }
    Program m_program;

    Mesh(std::vector<glimac::ShapeVertex>& vertices)
        : m_program("../assets/CloudMap.jpg", "../shaders/3D.vs.glsl", "../shaders/text3D.fs.glsl")
    {
        OpenGLUtils::init_vao(m_vao, m_vbo, vertices);
        m_vertices_size = vertices.size();
        // m_texture_uint  = OpenGLUtils::texture(m_texture);
    }

    void DrawMesh(p6::Context& ctx, const glm::mat4& viewmatrix,Program& program,const glm::vec3& position,const float scale_value)
    {
        program.getUniformLocations();
        program.use(viewmatrix, ctx, position, scale_value);
        // glEnable(GL_DEPTH_TEST);
        m_vao.bind();
        program.bind();
        program.useText();
        glDrawArrays(GL_TRIANGLES, 0, m_vertices_size);
        // OpenGLUtils::draw_mesh(&m_shader, m_vertices_size, &ctx, m_vao, viewmatrix, m_texture_uint, scale);
    }
};