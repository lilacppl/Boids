#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../glimac/common.hpp"
#include "../glimac/sphere_vertices.hpp"
#include "doctest/doctest.h"
#include "glm/ext/scalar_constants.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "vao.hpp"
// #include "vertex3d.hpp"

class VBO {
private:
    GLuint m_vbo;

public:
    VBO();
    void buffer(std::vector<glimac::ShapeVertex> vertices);
    VBO(std::vector<glimac::ShapeVertex> vertices);
    ~VBO();
    VBO(const VBO& other)            = delete;
    VBO& operator=(const VBO& other) = delete;
    VBO(VBO&& other) noexcept;
    VBO& operator=(VBO&& other) noexcept;

    void bind();
    void debind();
    friend class VAO;
};
