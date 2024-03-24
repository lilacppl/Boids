#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../glimac/common.hpp"
#include "doctest/doctest.h"
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
    void vertex_attrib();
};

