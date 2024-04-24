#pragma once

#ifndef MESH_HPP
#define MESH_HPP
#include "iprogram.hpp"
#include "p6/p6.h"
// mesh.hpp

class Mesh {
private:
    float m_size;
    VBO   m_vbo;
    VAO   m_vao;
    int   m_vertices_size;

public:
    Mesh();
    Mesh(const std::vector<glimac::ShapeVertex>& vertices);

    void DrawMesh(const p6::Context& ctx, const glm::mat4& viewmatrix, const Program& program, const glm::vec3& position, const float scale_value, const glm::vec3 direction, const float scale_down) const;

    void InitMeshVboVao(const std::vector<glimac::ShapeVertex>& vertices);
};

#endif // MESH_HPP
