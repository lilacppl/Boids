#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../glimac/common.hpp"
#include "glm/gtx/transform.hpp"
// #include "p6/p6.h"
#include "vao.hpp"
#include "vbo.hpp"

// plus tard : soit faire une classe sphere soit l'inclure dans la classe boid
// penser au fait qu'on aura plusieurs shader -> faire des struct (ou classes du cp)

void init_vao_vbo(const std::vector<glimac::ShapeVertex>& vertices);

void draw_sphere(const p6::Shader* shader, const std::vector<glimac::ShapeVertex> vertices, auto ctx);