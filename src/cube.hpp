#pragma one
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glimac/common.hpp"
#include "glimac/freefly_camera.hpp"
#include "glimac/sphere_vertices.hpp"
#include "openglutils.hpp"
#include "p6/p6.h"

class Cube {
private:
    float                            m_size;
    std::vector<glimac::ShapeVertex> m_vertices;
    img::Image                       m_firsttexture;
    img::Image                       m_secondtexture;

public:
    void initCube()
    {
        m_size     = 1.0;
        m_vertices = {
            // face arriere
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 0)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 0)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 0)},
            // Face avant
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 0)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 0)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(1, 0, 0), glm::vec2(1, 0)},

            // Face gauche
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 0)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 1)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
            // // // Face droite
            {glm::vec3(0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 0)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 1)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 1, 0), glm::vec2(1, 0)},
            // // // Face inférieure
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 0)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, -0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
            // // // // Face supérieure
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 0)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, 0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
            {glm::vec3(0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 1)},
            {glm::vec3(-0.5f * m_size, 0.5f * m_size, -0.5f * m_size), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
        };
        m_firsttexture  = loadTexture("text2.png");
        m_secondtexture = loadTexture("CloudMap.jpg");
    }
    void DrawCube();
};