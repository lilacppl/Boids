#include "vao.hpp"

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

void VAO::vertex_attrib()
{
    static constexpr GLuint pos1 = 0;
    static constexpr GLuint pos2 = 1;
    static constexpr GLuint pos3 = 2;

    // Activation attribut
    glEnableVertexAttribArray(pos1);
    glEnableVertexAttribArray(pos2);
    glEnableVertexAttribArray(pos3);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo.m_vbo);

    // on spécifie les attributs du vertex
    // glVertexAttribPointer(pos1, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), nullptr);
    glVertexAttribPointer(pos1, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, position)));
    glVertexAttribPointer(pos2, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, normal)));
    glVertexAttribPointer(pos3, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, texCoords)));
}
