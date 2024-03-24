#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../glimac/common.hpp"
#include "glm/gtx/transform.hpp"
// #include "p6/p6.h"
#include "vao.hpp"
// #include "vbo.hpp"

// plus tard : soit faire une classe sphere soit l'inclure dans la classe boid
// penser au fait qu'on aura plusieurs shader -> faire des struct (ou classes du cp)

void init_vao_vbo(const std::vector<glimac::ShapeVertex>& vertices)
{
    VBO vbo(vertices);
    VAO vao;
    vao.bind();
    vbo.bind();
    vao.vertex_attrib();
    vbo.debind();
    vao.debind();
}

void draw_sphere(const p6::Shader* shader, const std::vector<glimac::ShapeVertex> vertices, auto ctx)
{
    // recuperation des matrices du shader
    GLint     uMVPMatrixLocation    = glGetUniformLocation(shader->id(), "uMVPMatrix");
    GLint     uMVMatrixLocation     = glGetUniformLocation(shader->id(), "uMVMatrix");
    GLint     uNormalMatrixLocation = glGetUniformLocation(shader->id(), "uNormalMatrix");
    glm::mat4 ProjMatrix            = glm::perspective(glm::radians(70.f), ctx->aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix              = glm::translate(glm::mat4{1.f}, glm::vec3(0.f, 0.f, -5.f));
    glm::mat4 NormalMatrix          = glm::transpose(glm::inverse(MVMatrix));

    // envoi des matrices vers le GPU
    glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}