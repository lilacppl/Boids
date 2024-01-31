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

class VAO {
    GLuint m_vao;

    VAO();
    ~VAO();

    void bind();
    void debind();
    void vertex_attrib(const GLuint* pos1, const GLuint* pos2);
};

VAO::VAO()
{
    GLuint VAO;
    m_vao = VAO;
    glGenVertexArrays(1, &m_vao);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_vao);
}

void VAO::bind()
{
    glBindVertexArray(m_vao);
}

void VAO::debind()
{
    glBindVertexArray(0);
}

void vertex_attrib(const GLuint* pos1, const GLuint* pos2)
{
    // Activation attribut
    glEnableVertexAttribArray(*pos1);
    glEnableVertexAttribArray(*pos2);

    // on spécifie les attributs du vertex
    glVertexAttribPointer(*pos1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), nullptr);
    glVertexAttribPointer(*pos2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const GLvoid*)(offsetof(Vertex3D, tex)));
}
