#pragma once
// #include <glm/ext/matrix_clip_space.hpp>
// #include <glm/ext/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include "../glimac/common.hpp"
// #include "../glimac/freefly_camera.hpp"
// #include "../glimac/sphere_vertices.hpp"
#include "iprogram.hpp"
// #include "openglutils.hpp"
#include "p6/p6.h"

class Mesh { // Mesh
private:
    float m_size;
    VBO   m_vbo;
    VAO   m_vao;
    int   m_vertices_size;

public:
    // Program m_program;
    float m_scale_down = 1; // Pour le cube, lorsqu'il rapetisse, la valeur change
                            // Mesh(const Mesh&)    = delete;

    Mesh()
        : m_size(0.0f)
    {
    }

    Mesh(std::vector<glimac::ShapeVertex>& vertices)
    {
        // OpenGLUtils::init_vao(m_vao, m_vbo, vertices);
        InitMeshVboVao(vertices);
        m_vertices_size = vertices.size();
        // m_texture_uint  = OpenGLUtils::texture(m_texture);
    }

    // void DrawMesh(p6::Context& ctx, const glm::mat4& viewmatrix, Program& program, const glm::vec3& position, const float scale_value, glm::vec3 direction)
    void DrawMesh(const p6::Context& ctx, const glm::mat4& viewmatrix, const Program& program, const glm::vec3& position, const float scale_value, const glm::vec3 direction, const float scale_down) const
    {
        // program.getUniformLocations();

        program.use(viewmatrix, ctx, position, scale_value, direction, scale_down);
        // glEnable(GL_DEPTH_TEST);
        m_vao.bind();
        program.bind();
        program.useText();
        glDrawArrays(GL_TRIANGLES, 0, m_vertices_size);
        // OpenGLUtils::draw_mesh(&m_shader, m_vertices_size, &ctx, m_vao, viewmatrix, m_texture_uint, scale);
    }

    void InitMeshVboVao(std::vector<glimac::ShapeVertex>& vertices)
    {
        m_vao.bind();
        m_vbo.buffer(vertices);
        m_vbo.bind();
        m_vao.vertex_attrib();
        m_vbo.debind();
        m_vao.debind();
    }
};