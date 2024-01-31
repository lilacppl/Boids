#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "doctest/doctest.h"
#include "glfw/src/internal.h"
#include "glm/ext/scalar_constants.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "vertex3d.hpp"

class VBO {
    GLuint m_vbo;

    VBO();
    VBO(std::vector<Vertex3D> vertices);
    ~VBO();

    void bind();
    void debind();
};

VBO::VBO()
{
    GLuint VBO;
    m_vbo = VBO;
    glGenBuffers(1, &m_vbo);
}

VBO::VBO(std::vector<Vertex3D> vertices)
{
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), vertices.data(), GL_STATIC_DRAW);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &m_vbo);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void VBO::debind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
