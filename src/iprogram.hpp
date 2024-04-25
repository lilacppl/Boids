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
    GLint      m_uTexture;
    GLint      uMVPMatrix;
    GLint      uMVMatrix;
    GLint      uNormalMatrix;


    GLint m_uKd;
    GLint m_uKs;
    GLint m_uKd2;
    GLint m_uKs2;
    GLint m_uShininess;
    GLint m_uLightDir_vs;
    GLint m_uLightIntensity;
    GLint m_uLightIntensity2;

    GLint m_uLightPos_vs;
    int   m_frame_index = 0;
    float m_shininess;
    float m_intensity;
    float m_intensity2;
    float m_r;
    float m_g;
    float m_b;
    // static bool  m_light_change;

public:
    int m_actual_state = 0; // état de départ pour Markov
    Program(std::string texture_path, std::string vs_path, std::string fs_path);

    ~Program() = default;
    void bind() const;
    void debind() const;
    void getUniformLocations();
    void use(const glm::mat4& viewmatrix, const p6::Context& ctx, const glm::vec3& position, const float scale_value, const glm::vec3 direction, const float scale_down, const int& time) const;
    void useText() const;
    void LightVarToShader(const glm::mat4& viewmatrix, const int& time) const;
    void deleteTextureBufferArray() const;
};


float randomIntensityValue();

float randomColor();

glm::vec3 lightPos_vs(const glm::mat4& viewmatrix, const int& time);
