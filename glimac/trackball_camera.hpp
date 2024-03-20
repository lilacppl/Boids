#ifndef TRACKBALL_CAMERA_HPP
#define TRACKBALL_CAMERA_HPP
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "common.hpp"



class TrackballCamera {
private:
    float m_Distance;
    float m_AngleX;
    float m_AngleY;

public:
    TrackballCamera()
        : m_Distance(5.0f), m_AngleX(0.0f), m_AngleY(0.0f) {}

    // Méthode pour avancer/reculer la caméra
    void moveFront(float delta)
    {
        m_Distance += delta;
    }

    // Méthode pour tourner latéralement autour du centre de vision
    void rotateLeft(float degrees)
    {
        m_AngleY += degrees;
    }

    // Méthode pour tourner verticalement autour du centre de vision
    void rotateUp(float degrees)
    {
        m_AngleX += degrees;
    }

    // Méthode pour calculer la matrice de vue (View Matrix)
    glm::mat4 getViewMatrix() const
    {
        // Conversion des angles en radians
        float radiansX = glm::radians(m_AngleX);
        float radiansY = glm::radians(m_AngleY);

        // Création des matrices de transformation
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -m_Distance));
        glm::mat4 rotationX   = glm::rotate(glm::mat4(1.0f), radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotationY   = glm::rotate(glm::mat4(1.0f), radiansY, glm::vec3(0.0f, 1.0f, 0.0f));

        // Calcul de la matrice de vue en combinant les transformations
        return rotationY * rotationX * translation;
    }
};

#endif // TRACKBALL_CAMERA_HPP
