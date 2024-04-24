#pragma once
#include <iostream>
#include <vector>
#include "../glimac/common.hpp"
#include "glm/glm.hpp"

// fonction permettant de remplir l'attribut fish de vertices avec les vertex issus d'un .obj placé dans assets
std::vector<glimac::ShapeVertex> tinyVertice(const std::string inputfile);

// Contient les vertex du cube de base ainsi que des boids/poissons
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

    std::vector<glimac::ShapeVertex> fish        = tinyVertice("./assets/fish_color.obj");
    std::vector<glimac::ShapeVertex> seaweed     = tinyVertice("./assets/algue.obj");
    std::vector<glimac::ShapeVertex> fishlow     = tinyVertice("./assets/poissonopenglow.obj");
    std::vector<glimac::ShapeVertex> fishverylow = tinyVertice("./assets/poissonopenglverylow.obj");
    std::vector<glimac::ShapeVertex> shark       = tinyVertice("./assets/shark.obj");
};