#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "doctest/doctest.h"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

struct Vertex3D {
    glm::vec3 pos;
    glm::vec3 tex;
};