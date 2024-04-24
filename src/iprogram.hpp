#pragma once

#include <cmath>
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "../glimac/common.hpp"
#include "doctest/doctest.h"
#include "glm/ext/scalar_constants.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "img/src/Image.h"
#include "p6/p6.h"
#include "vbo.hpp"
// #include "vertex3d.hpp"

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

    // pour la lumiere
    GLint m_uKd;
    GLint m_uKs;
    GLint m_uKd2;
    GLint m_uKs2;
    GLint m_uShininess;
    GLint m_uLightDir_vs;
    GLint m_uLightIntensity;
    GLint m_uLightPos_vs;

public:
    int m_actual_state = 0; // état de départ pour Markov
    Program(std::string texture_path, std::string vs_path, std::string fs_path);

    ~Program() = default; // jsp si yen a besoin sisi c bien
    void bind() const;
    void debind() const;
    void getUniformLocations();
    // void use(const glm::mat4& viewmatrix, p6::Context& ctx, const glm::vec3& position, const float scale_value, glm::vec3 direction) const;
    void use(const glm::mat4& viewmatrix, const p6::Context& ctx, const glm::vec3& position, const float scale_value, const glm::vec3 direction, const float scale_down) const;
    // void use(const glm::mat4& viewmatrix, p6::Context& ctx, glm::vec3& position, float scale_value, const glm::vec3& arpenteur_position);
    void useText() const;
    void LightVarToShader(const glm::mat4& viewmatrix) const;
    void setTexture();

    // rajouter une fonction qui libere les textures etc a la fin
};

float randomShininess();

float randomIntensityValue();

glm::vec3 lightDir_vs(const glm::mat4& viewmatrix);

glm::vec3 lightPos_vs(const glm::mat4& viewmatrix, const float radius, const float angle, const glm::vec3& position);
