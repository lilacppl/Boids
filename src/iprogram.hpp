#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "../glimac/common.hpp"
#include "doctest/doctest.h"
#include "glm/ext/scalar_constants.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "vbo.hpp"
#include "vertex3d.hpp"

class Program {
private:
    img::Image m_image;
    int        m_index;
    GLuint     m_name;
    p6::Shader m_Program;
    GLint      m_uTexture; // variable uniforme pour les shaders
    GLint      uMVPMatrix;
    GLint      uMVMatrix;
    GLint      uNormalMatrix;

public:
    Program(std::string texture_path, std::string vs_path, std::string fs_path);
    ~Program();
    void bind();
    void debind();
    void use();
};

// Initialisation
Program::Program(std::string texture_path, std::string vs_path, std::string fs_path)
    : m_image(p6::load_image_buffer(texture_path)), m_Program{p6::load_shader(vs_path, fs_path)}
{
    // Création de la texture
    glGenTextures(1, &m_name);
    glBindTexture(GL_TEXTURE_2D, m_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Variable uniforme
    uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
    uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
}

void Program::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_name);
}
void Program::debind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

// A mettre avant le draw dans la boucle
void Program::use()
{
    // Texture
    m_Program.use();
    glActiveTexture(GL_TEXTURE0 + m_index);
    glBindTexture(GL_TEXTURE_2D, m_name);
    m_uTexture = glGetUniformLocation(m_Program.id(), "uTexture");
    glUniform1i(m_uTexture, m_index);

    // Variables uniformes
    // const glm::mat4 globalMVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, -5.f});
    // const glm::mat4 earthMVMatrix  = glm::rotate(globalMVMatrix, ctx.time(), {0.f, 1.f, 0.f});
    // glm::mat4       projMatrix     = glm::inverse(view) * glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);

    // envoi des matrices vers le GPU
    // glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
    // glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
    // glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * earthMVMatrix));
}
// INTEGRER LA VIEWMATRIX ET CTX DANS LA CLASSE