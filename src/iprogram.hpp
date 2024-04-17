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
    // p6::Context m_ctx;

public:
    Program(std::string texture_path, std::string vs_path, std::string fs_path);
    ~Program() = default; // jsp si yen a besoin
    void bind() const;
    void debind() const;
    void getUniformLocations();
    void use(const glm::mat4& viewmatrix, p6::Context& ctx, const glm::vec3& position, const float scale_value, glm::vec3 direction) const;
    void useText() const;
};
