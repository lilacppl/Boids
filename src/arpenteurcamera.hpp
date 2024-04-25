

#pragma once
#include <p6/p6.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> // pour glm::pi
#include "glm/ext/quaternion_geometric.hpp"
#include "mesh.hpp"

class ArpenteurCamera {
private:
    glm::vec3 m_Position;
    float     m_Phi;
    float     m_Theta;

    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;
    float     m_distance = 0.7f;

public:
    ArpenteurCamera();
    void      updatePosition(const glm::vec3 arpenteurPos, const float arpenteurRotation);
    glm::mat4 getViewMatrix(const glm::vec3& arpenteurPosition);
};
