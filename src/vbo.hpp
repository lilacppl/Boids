#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "doctest/doctest.h"
#include "../glimac/common.hpp"
#include "../glimac/sphere_vertices.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "vertex3d.hpp"


class VBO {
private:
    GLuint m_vbo;

public:
    VBO();
    VBO(std::vector<glimac::ShapeVertex> vertices);
    ~VBO();
    VBO(const VBO& other)            = delete;
    VBO& operator=(const VBO& other) = delete;
    VBO(VBO&& other) noexcept;
    VBO& operator=(VBO&& other) noexcept;

    void bind();
    void debind();
};

VBO::VBO()
{
    glGenBuffers(1, &m_vbo);
}

VBO::VBO(std::vector<glimac::ShapeVertex> vertices)
{
    glGenBuffers(1, &m_vbo);
    bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);
    debind();
}

VBO::~VBO()
{
    glDeleteBuffers(1, &m_vbo);
}

VBO::VBO(VBO&& other) noexcept // Move constructor
    : m_vbo{other.m_vbo}
{
    other.m_vbo = 0; // Make sure that other won't delete the _id we just copied
}

VBO& VBO::operator=(VBO&& other) noexcept // Move assignment operator
{
    if (this != &other)
    {                               // Make sure that we don't do silly things when we try to move an object to itself
        glDeleteBuffers(1, &m_vbo); // Delete the previous object
        m_vbo       = other.m_vbo;  // Copy the object
        other.m_vbo = 0;            // Make sure that other won't delete the _id we just copied
    }
    return *this; // move assignment must return a reference to this, so we do it
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void VBO::debind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
