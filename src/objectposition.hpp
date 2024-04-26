#pragma once

#include <glm/glm.hpp>
class ObjectPositionScale {
private:
    glm::vec3 position;
    float     scale;

public:
    ObjectPositionScale(const glm::vec3& pos, const float scl)
        : position(pos), scale(scl) {}

    glm::vec3 getPosition() const
    {
        return position;
    }

    void setPosition(const glm::vec3& value)
    {
        position = value;
    }

    void setZ(const float& value)
    {
        position.z = value;
    }

    float getScale() const
    {
        return scale;
    }
};
