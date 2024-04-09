#ifndef FREEFLY_CAMERA_HPP
#define FREEFLY_CAMERA_HPP
#pragma once
#include <p6/p6.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> // pour glm::pi
#include "common.hpp"
#include "mesh.hpp"

class FreeflyCamera {
private:
    glm::vec3 m_Position;
    float     m_Phi;
    float     m_Theta;

    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;
    bool      m_moveForward  = false;
    bool      m_moveBackward = false;
    bool      m_moveLeft     = false;
    bool      m_moveRight    = false;
    bool      m_moveUp       = false;
    bool      m_moveDown     = false;
    bool      m_rotateLeft   = false;
    bool      m_rotateRight  = false;
    float     m_sensi        = 0.2f;
    float     m_speed        = 0.1f;
    float     m_distance     = 1.f;

    void computeDirectionVectors()
    {
        float cosPhi   = cos(m_Phi);
        float sinPhi   = sin(m_Phi);
        float cosTheta = cos(m_Theta);
        float sinTheta = sin(m_Theta);

        m_FrontVector = glm::vec3(cosTheta * sinPhi, sinTheta, cosTheta * cosPhi);
        m_LeftVector  = glm::vec3(sin(m_Phi + glm::pi<float>() / 2), 0, cos(m_Phi + glm::pi<float>() / 2));
        m_UpVector    = glm::cross(m_FrontVector, m_LeftVector);
    }

public:
    FreeflyCamera()
        : m_Position(glm::vec3(0.0f)), m_Phi(glm::pi<float>()), m_Theta(0.0f)
    {
        computeDirectionVectors();
    }
    // Méthode pour déplacer la caméra le long du vecteur Left
    void moveLeft(float t)
    {
        m_Position += t * m_LeftVector;
    }

    // Méthode pour déplacer la caméra le long du vecteur Front
    void moveFront(float t)
    {
        m_Position += t * m_FrontVector;
    }

    void moveUp(float t)
    {
        // Calculer le vecteur de déplacement en fonction de l'axe Up
        glm::vec3 upMovement = t * m_UpVector;
        // Ajouter le déplacement à la position de la caméra
        m_Position += upMovement;
    }

    // Méthode pour tourner la caméra latéralement autour de l'axe Up
    void rotateLeft(float degrees)
    {
        m_Phi += glm::radians(degrees);
        computeDirectionVectors();
    }

    // Méthode pour tourner la caméra verticalement autour de l'axe Left
    void rotateUp(float degrees)
    {
        m_Theta += glm::radians(degrees);
        computeDirectionVectors();
    }

    // Méthode pour calculer et renvoyer la matrice de vue associée à la caméra
    glm::mat4 getViewMatrix() const
    {
        glm::vec3 eye    = m_Position;
        glm::vec3 target = m_Position + m_FrontVector;
        glm::vec3 up     = m_UpVector;

        return glm::lookAt(eye, target, up);
    }
    void eventManager(p6::Context& ctx)
    {
        ctx.key_pressed = [&](p6::Key key) {
            if (key.logical == "z")
                m_moveForward = true;
            else if (key.logical == "s")
                m_moveBackward = true;
            else if (key.logical == "q")
                m_moveLeft = true;
            else if (key.logical == "d")
                m_moveRight = true;
            else if (key.logical == " ")
                m_moveUp = true;
            else if (key.logical == "w")
                m_moveDown = true;
        };
        ctx.mouse_pressed = [&](p6::MouseButton mouse) {
            if (mouse.button == p6::Button::Left)
            {
                m_rotateLeft = true;
            }
            else if (mouse.button == p6::Button::Right)
            {
                m_rotateRight = true;
            }
        };
        // Gestionnaire d'événements de touche relâchée
        ctx.key_released = [&](p6::Key key) {
            if (key.logical == "z")
                m_moveForward = false;
            else if (key.logical == "s")
                m_moveBackward = false;
            else if (key.logical == "q")
                m_moveLeft = false;
            else if (key.logical == "d")
                m_moveRight = false;
            else if (key.logical == " ")
                m_moveUp = false;
            else if (key.logical == "w")
                m_moveDown = false;
        };
        ctx.mouse_released = [&](p6::MouseButton mouse) {
            m_rotateLeft  = false;
            m_rotateRight = false;
        };
    }

    void eventUpdate()
    {
        if (m_moveForward)
            moveFront(m_speed);
        if (m_moveBackward)
            moveFront(-m_speed);
        if (m_moveLeft)
            moveLeft(m_speed);
        if (m_moveRight)
            moveLeft(-m_speed);
        if (m_moveUp)
            moveUp(m_speed);
        if (m_moveDown)
            moveUp(-m_speed);
        if (m_rotateLeft)
            rotateLeft(10 * m_sensi);
        if (m_rotateRight)
            rotateLeft(-10 * m_sensi);
    }
};

#endif // FREEFLY_CAMERA_HPP
