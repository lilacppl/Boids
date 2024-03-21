#pragma once
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glimac/common.hpp"
#include "glimac/freefly_camera.hpp"
#include "glimac/sphere_vertices.hpp"
#include "p6/p6.h"
#include "vao.hpp"
#include "vbo.hpp"

class OpenGLUtils {
public:
    static void loadShader(string vs, string fs)
    {
        const p6::Shader shader = p6::load_shader(
            "vs",
            "fs"
        );
    }

    static const img::Image loadTexture(string name)
    {
        name = "assets/" + name;
        return p6_load_image_buffer(name.c_str());
    }

    static VBO VaoandVbo(std::vector<glimac::ShapeVertex> vertices)
    {
        return VBO vbo(vertices);
    }

    static Gluint texture(img::Image img)
    {
        Gluint text;
        glGenTextures(1, &text);
        glBindTexture(GL_TEXTURE_2D, text);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        return text;
    }
    static void multiText(Gluint text1, Gluint text2, std::vector<glimac::ShapeVertex> vertices)
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
        glBindTexture(GL_TEXTURE_2D, txture2);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, txture3);
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
};
