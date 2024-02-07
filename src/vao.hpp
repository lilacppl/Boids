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
private:
    GLuint m_vao;

public:
    VAO();
    ~VAO();
    VAO(const VAO& other)            = delete;
    VAO& operator=(const VAO& other) = delete;
    VAO(VAO&& other) noexcept;
    VAO& operator=(VAO&& other) noexcept;

    void bind();
    void debind();
    void vertex_attrib(const GLuint* pos1, const GLuint* pos2);
};

VAO::VAO()
{
    glGenVertexArrays(1, &m_vao);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_vao);
}

VAO::VAO(VAO&& other) noexcept // Move constructor
    : m_vao{other.m_vao}
{
    other.m_vao = 0; // Make sure that other won't delete the _id we just copied
}

VAO& VAO::operator=(VAO&& other) noexcept // Move assignment operator
{
    if (this != &other)
    {                               // Make sure that we don't do silly things when we try to move an object to itself
        glDeleteBuffers(1, &m_vao); // Delete the previous object
        m_vao       = other.m_vao;  // Copy the object
        other.m_vao = 0;            // Make sure that other won't delete the _id we just copied
    }
    return *this; // move assignment must return a reference to this, so we do it
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
