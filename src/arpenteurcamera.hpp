

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
    ArpenteurCamera()
        : m_Position(glm::vec3(0, 0, 0))
    {
        m_FrontVector = glm::vec3(-1, 0, 0);
        m_LeftVector  = glm::vec3(0, 0, 1);
        m_UpVector    = glm::vec3(0, 1, 0);
    }
    void computeDirectionVectors()
    {
        // float cosPhi = cos(m_Phi);
        // float sinPhi = sin(m_Phi);
        // // m_FrontVector = glm::vec3(-1.0 * (cosPhi), 0.0, 1.0 * sinPhi);
        // m_FrontVector = glm::vec3(1.0 * (cosPhi), 0.0, 1.0 * sinPhi);
        // m_FrontVector = glm::normalize(m_FrontVector);
        // m_LeftVector  = glm::cross(m_UpVector, m_FrontVector);
        // // m_LeftVector  = glm::vec3(glm::cos(m_Phi + (p6::PI / 2)), 0, glm::sin(m_Phi + (p6::PI / 2)));
        // m_LeftVector = glm::normalize(m_LeftVector);

        // float cosPhi   = cos(m_Phi);
        // float sinPhi   = sin(m_Phi);
        // float cosTheta = cos(m_Theta);
        // float sinTheta = sin(m_Theta);

        // m_FrontVector = glm::vec3(cosTheta * sinPhi, sinTheta, cosTheta * cosPhi);
        // m_LeftVector  = glm::vec3(sin(m_Phi + glm::pi<float>() / 2), 0, cos(m_Phi + glm::pi<float>() / 2));
        // m_UpVector    = glm::cross(m_FrontVector, m_LeftVector);
    }

    void updatePosition(const glm::vec3 arpenteurPos, const float arpenteurRotation)
    {
        glm::vec4 positionTemp = glm::vec4(arpenteurPos.x, arpenteurPos.y, arpenteurPos.z, 0);
        positionTemp += (glm::rotate(glm::mat4(1), (p6::degrees_to_radians(arpenteurRotation)).value, glm::vec3(0, 1, 0)) * glm::vec4(m_distance, m_distance / 2, 0, 0));
        // positionTemp += (glm::rotate(glm::mat4(1), (p6::degrees_to_radians(0)).value, glm::vec3(0, 1, 0)) * glm::vec4(m_distance, m_distance / 2, 0, 0));
        m_Position = glm::vec3(positionTemp.x, positionTemp.y, positionTemp.z);
        // m_Phi      = arpenteurRotation;
        // computeDirectionVectors();
        // std::cout << "Position: (" << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << ")" << std::endl;
    }

    // Méthode pour calculer et renvoyer la matrice de vue associée à la caméra
    glm::mat4 getViewMatrix(const glm::vec3& arpenteurPosition)
    {
        glm::vec3 eye    = m_Position;        // position de la camera
        glm::vec3 target = arpenteurPosition; // point qu'elle regarde
        glm::vec3 up     = m_UpVector;        // vecteur vertical

        // return glm::lookAt(eye, target, up);

        // // Vecteur vers la gauche (left) en utilisant le produit vectoriel entre le vecteur de direction et le vecteur up
        // glm::vec3 front = glm::normalize(m_Position - arpenteurPosition);
        // glm::vec3 left  = glm::normalize(glm::cross(up, front));

        // // Vecteur vers le haut (up) en utilisant à nouveau le produit vectoriel entre left et front
        // glm::vec3 newUp = glm::cross(front, left); // Cela assure que les vecteurs sont perpendiculaires et forment un système orthogonal

        // // Mettre à jour les vecteurs de la caméra
        // m_FrontVector += front;
        // m_LeftVector += left;
        // m_UpVector = newUp;

        return glm::lookAt(eye, target, up);
    }

    glm::vec3 getFrontVector()
    {
        return m_FrontVector;
    }
    glm::vec3 getLeftVector()
    {
        return m_LeftVector;
    }

    glm::vec3 getUpVector()
    {
        return m_UpVector;
    }
};
