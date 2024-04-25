#include "arpenteurcamera.hpp"

ArpenteurCamera::ArpenteurCamera()
    : m_Position(glm::vec3(0, 0, 0))
{
    m_FrontVector = glm::vec3(-1, 0, 0);
    m_LeftVector  = glm::vec3(0, 0, 1);
    m_UpVector    = glm::vec3(0, 1, 0);
}

void ArpenteurCamera::updatePosition(const glm::vec3 arpenteurPos, const float arpenteurRotation)
{
    glm::vec4 positionTemp = glm::vec4(arpenteurPos.x, arpenteurPos.y, arpenteurPos.z, 0);
    positionTemp += (glm::rotate(glm::mat4(1), (p6::degrees_to_radians(arpenteurRotation)).value, glm::vec3(0, 1, 0)) * glm::vec4(m_distance, m_distance / 2, 0, 0));
    m_Position = glm::vec3(positionTemp.x, positionTemp.y, positionTemp.z);
}

glm::mat4 ArpenteurCamera::getViewMatrix(const glm::vec3& arpenteurPosition)
{
    glm::vec3 eye    = m_Position;        // position de la camera
    glm::vec3 target = arpenteurPosition; // point qu'elle regarde
    glm::vec3 up     = m_UpVector;        // vecteur vertical
    return glm::lookAt(eye, target, up);
}