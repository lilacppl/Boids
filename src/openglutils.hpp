#pragma once
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "../glimac/common.hpp"
#include "../glimac/freefly_camera.hpp"
#include "../glimac/sphere_vertices.hpp"
#include "p6/p6.h"
// #include "vao.hpp"
// #include "vbo.hpp"

class OpenGLUtils {
public:
    static p6::Shader loadShader(std::string vs, std::string fs)
    {
        // const p6::Shader shader = p6::load_shader(
        //     "vs",
        //     "fs"
        // );
        return p6::load_shader(
            vs,
            fs
        );
    }

    static const img::Image loadTexture(std::string name)
    {
        name = "assets/" + name;
        return p6::load_image_buffer(name.c_str());
    }

    // static VBO VaoandVbo(std::vector<glimac::ShapeVertex> vertices)
    // {
    //     return vbo(vertices);
    // }

    static GLuint texture(img::Image img)
    {
        GLuint text;
        glGenTextures(1, &text);
        glBindTexture(GL_TEXTURE_2D, text);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        return text;
    }
    static void multiText(GLuint text1, GLuint text2, std::vector<glimac::ShapeVertex> vertices, p6::Shader shader)
    {
        // à mettre dans le rendu
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, text1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, text2);
        GLint uEarthLocation = glGetUniformLocation(shader.id(), "TextureCoordinate");
        // Récupère la location de la deuxième texture dans le shader
        GLint uCloudTextureLocation = glGetUniformLocation(shader.id(), "CloudTextureCoordinate");
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, text1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, text2);
        // Indique à OpenGL qu'il doit aller chercher sur l'unité de texture 0
        // pour lire dans la texture uEarthTexture
        glUniform1i(uEarthLocation, 0);
        // Indique à OpenGL qu'il doit aller chercher sur l'unité de texture 1
        // pour lire dans la texture uCloudTexture
        glUniform1i(uCloudTextureLocation, 1);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    static void init_vao_vbo(const std::vector<glimac::ShapeVertex>& vertices)
    {
        VBO vbo(vertices);
        VAO vao;
        vao.bind();
        vbo.bind();
        vao.vertex_attrib();
        vbo.debind();
        vao.debind();
    }

    static void init_vao(VAO& vao, VBO& vbo, const std::vector<glimac::ShapeVertex>& vertices)
    {
        vao.bind();
        vbo.buffer(vertices);
        vbo.bind();
        vao.vertex_attrib();
        vbo.debind();
        vao.debind();
    }

    static void draw_sphere(const p6::Shader* shader, const std::vector<glimac::ShapeVertex> vertices, auto ctx)
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

    static void draw_cube(const p6::Shader* shader, const std::vector<glimac::ShapeVertex> vertices, auto ctx, VAO& vao, glm::mat4 viewMatrix)
    {
        // recuperation des matrices du shader
        GLint     uMVPMatrixLocation    = glGetUniformLocation(shader->id(), "uMVPMatrix");
        GLint     uMVMatrixLocation     = glGetUniformLocation(shader->id(), "uMVMatrix");
        GLint     uNormalMatrixLocation = glGetUniformLocation(shader->id(), "uNormalMatrix");
        glm::mat4 ProjMatrix            = glm::perspective(glm::radians(70.f), ctx->aspect_ratio(), 0.1f, 100.f);
        glm::mat4 MVMatrix              = glm::translate(glm::mat4{1.f}, glm::vec3(0.f, 0.f, -5.f));
        glm::mat4 NormalMatrix          = glm::transpose(glm::inverse(MVMatrix));
        glm::mat4 MVPMatrix             = ProjMatrix * viewMatrix;

        // envoi des matrices vers le GPU
        glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
};
