#pragma once
#include <iostream>

struct Vertices {
    std::vector<glimac::ShapeVertex> cube = {
        {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1, 0, 0), glm::vec2(1, 0)},
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1, 0, 0), glm::vec2(0, 0)},
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
        {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1, 0, 0), glm::vec2(1, 1)},
        {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1, 0, 0), glm::vec2(1, 0)},
        // Face avant
        {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1, 0, 0), glm::vec2(1, 0)},
        {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1, 0, 0), glm::vec2(0, 0)},
        {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
        {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 0, 0), glm::vec2(0, 1)},
        {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 0, 0), glm::vec2(1, 1)},
        {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1, 0, 0), glm::vec2(1, 0)},

        // Face gauche
        {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 0)},
        {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 1)},
        {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 1)},
        {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 1)},
        {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
        // // // Face droite
        {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 0)},
        {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
        {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 1)},
        {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, 1, 0), glm::vec2(0, 1)},
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 1)},
        {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0), glm::vec2(1, 0)},
        // // // Face inférieure
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
        {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1), glm::vec2(0, 0)},
        {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
        {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0, 0, 1), glm::vec2(1, 1)},
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
        // // // // Face supérieure
        {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
        {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 1), glm::vec2(0, 0)},
        {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
        {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 1), glm::vec2(0, 1)},
        {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0, 0, 1), glm::vec2(1, 1)},
        {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 0, 1), glm::vec2(1, 0)},
    };
};