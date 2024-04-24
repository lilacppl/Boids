

#pragma once
#include <p6/p6.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> // pour glm::pi
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
    ArpenteurCamera()
        : m_Position(glm::vec3(0, 0, 0)), m_Phi(glm::pi<float>()), m_Theta(0.0f)
    {
        m_FrontVector = glm::vec3(-1, 0, 0);
        m_LeftVector  = glm::vec3(0, 0, 1);
        m_UpVector    = glm::vec3(0, 1, 0);
    }

    void updatePosition(const glm::vec3 arpenteurPos, const float arpenteurRotation)
    {
        glm::vec4 positionTemp = glm::vec4(arpenteurPos.x, arpenteurPos.y, arpenteurPos.z, 0);
        positionTemp += (glm::rotate(glm::mat4(1), (p6::degrees_to_radians(arpenteurRotation)).value, glm::vec3(0, 1, 0)) * glm::vec4(m_distance, m_distance / 2, 0, 0));
        // positionTemp += (glm::rotate(glm::mat4(1), (p6::degrees_to_radians(0)).value, glm::vec3(0, 1, 0)) * glm::vec4(m_distance, m_distance / 2, 0, 0));
        m_Position = glm::vec3(positionTemp.x, positionTemp.y, positionTemp.z);
        m_Phi      = arpenteurRotation;
        // std::cout << "Position: (" << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << ")" << std::endl;
    }

    // Méthode pour calculer et renvoyer la matrice de vue associée à la caméra
    glm::mat4 getViewMatrix(const glm::vec3& arpenteurPosition) const
    {
        glm::vec3 eye    = m_Position;        // position de la camera
        glm::vec3 target = arpenteurPosition; // point qu'elle regarde
        glm::vec3 up     = m_UpVector;        // vecteur vertical

        //return glm::lookAt(eye, target, up);
        return glm::lookAt(eye, target, up);

    }
};
