#pragma once

#include <glm/glm.hpp>
class ObjectPositionScale {
private:
    glm::vec3 position;
    float     scale;

public:
    ObjectPositionScale(const glm::vec3& pos, float scl)
        : position(pos), scale(scl) {}

    glm::vec3 getPosition() const
    {
        return position;
    }

    float getScale() const
    {
        return scale;
    }
};
