#include "mesh.hpp"

Mesh::Mesh()
    : m_size(0.0f)
{
}

Mesh::Mesh(const std::vector<glimac::ShapeVertex>& vertices)
{
    InitMeshVboVao(vertices);
    m_vertices_size = vertices.size();
}

// void DrawMesh(p6::Context& ctx, const glm::mat4& viewmatrix, Program& program, const glm::vec3& position, const float scale_value, glm::vec3 direction)
void Mesh::DrawMesh(const p6::Context& ctx, const glm::mat4& viewmatrix, const Program& program, const glm::vec3& position, const float scale_value, const glm::vec3 direction, const float scale_down, const int& time) const
{
    // program.getUniformLocations();

    program.use(viewmatrix, ctx, position, scale_value, direction, scale_down, time);
    // glEnable(GL_DEPTH_TEST);
    m_vao.bind();
    program.bind();
    program.useText();
    glDrawArrays(GL_TRIANGLES, 0, m_vertices_size);
    // OpenGLUtils::draw_mesh(&m_shader, m_vertices_size, &ctx, m_vao, viewmatrix, m_texture_uint, scale);
}

void Mesh::InitMeshVboVao(const std::vector<glimac::ShapeVertex>& vertices)
{
    m_vao.bind();
    m_vbo.buffer(vertices);
    m_vbo.bind();
    m_vao.vertexAttrib();
    m_vbo.debind();
    m_vao.debind();
}

void Mesh::DeleteVboVao() const{
    m_vbo.~VBO();
    m_vao.~VAO();
}