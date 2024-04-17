#pragma once
#include <p6/p6.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> // pour glm::pi
// #include "common.hpp"

#include "arpenteurcamera.hpp"
#include "mesh.hpp"
#include "vertices.hpp"

class Arpenteur {
private:
    glm::vec3 m_position;
    Vertices  m_vertices;
    float     m_Phi;
    float     m_Theta;

    // juste position rotation

    glm::vec3       m_FrontVector = glm::vec3(-1., 0., 0.);
    glm::vec3       m_LeftVector  = glm::vec3(0., 0., 1.);
    glm::vec3       m_UpVector    = glm::vec3(.0, 1., 0.);
    Mesh            m_mesh;
    ArpenteurCamera m_camera;
    // c juste un objet qui bouge avec les input

    // mettre la cam la
    // fonction draw le mesh
    // la cam = matrice de l'arpenteur, matrice de rotation de l'arpenteur, matrice
    // dans l'objet cam : matrice, de rotation, matrice de position,
    // position de la cam :translation(position arpenteur)
    // rotation : rotate(rotation arpenteur)
    // translation (distance que je veux)

    bool  m_moveForward  = false;
    bool  m_moveBackward = false;
    bool  m_moveLeft     = false;
    bool  m_moveRight    = false;
    bool  m_moveUp       = false;
    bool  m_moveDown     = false;
    bool  m_rotateLeft   = false;
    bool  m_rotateRight  = false;
    float m_sensi        = 10.f;
    float m_speed        = 0.1f;

    // void computeDirectionVectors()
    // {
    //     float cosPhi   = cos(m_Phi);
    //     float sinPhi   = sin(m_Phi);
    //     float cosTheta = cos(m_Theta);
    //     float sinTheta = sin(m_Theta);

    //     m_FrontVector = glm::vec3(cosTheta * sinPhi, sinTheta, cosTheta * cosPhi);
    //     m_LeftVector  = glm::vec3(sin(m_Phi + glm::pi<float>() / 2), 0, cos(m_Phi + glm::pi<float>() / 2));
    //     m_UpVector    = glm::cross(m_FrontVector, m_LeftVector);
    // }

public:
    Arpenteur()
        : m_position(glm::vec3(0.0f)), m_mesh(m_vertices.fish)
    {
        // computeDirectionVectors();
        m_camera.updatePosition(m_position, 0.);
    }

    void update(p6::Context& ctx, Program& program)
    {
        // eventManager(ctx);
        m_camera.updatePosition(m_position, m_Phi);
        m_mesh.DrawMesh(ctx, m_camera.getViewMatrix(m_position), program, m_position, 0.1, m_position);
    }

    glm::mat4 getViewMatrix() const
    {
        return m_camera.getViewMatrix(m_position);
    }

    // Méthode pour déplacer la caméra le long du vecteur Left
    void moveLeft(float t)
    {
        m_position += t * m_LeftVector;
    }

    // Méthode pour déplacer la caméra le long du vecteur Front
    void moveFront(float t)
    {
        m_position += t * m_FrontVector;
    }

    void moveUp(float t)
    {
        // Calculer le vecteur de déplacement en fonction de l'axe Up
        glm::vec3 upMovement = t * m_UpVector;
        // Ajouter le déplacement à la position de la caméra
        m_position += upMovement;
    }

    // Méthode pour tourner la caméra autour de l'arpenteur
    void rotateLeft(float degrees)
    {
        m_Phi += glm::radians(degrees);
        // computeDirectionVectors();
    }

    // // Méthode pour tourner la caméra verticalement autour de l'axe Left
    // void rotateUp(float degrees)
    // {
    //     m_Theta += glm::radians(degrees);
    //     computeDirectionVectors();
    // }

    // void eventManager(p6::Context& ctx)
    // {
    //     if (ctx.key_is_pressed(GLFW_KEY_O))
    //         moveFront(0.2);
    //     if (ctx.key_is_pressed(GLFW_KEY_L))
    //         moveFront(-0.2);
    //     if (ctx.key_is_pressed(GLFW_KEY_K))
    //         moveLeft(0.2);
    //     if (ctx.key_is_pressed(GLFW_KEY_A))
    //     {
    //         moveLeft(-0.2);
    //         std::cout << "tourne";
    //     }

    //     if (ctx.key_is_pressed(GLFW_KEY_N))
    //         m_Phi -= 0.3;
    //     if (ctx.key_is_pressed(GLFW_KEY_B))
    //         m_Phi += 0.3;
    // }
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
                m_moveUp = true;
            else if (key.logical == "a")
                m_rotateLeft = true;
            else if (key.logical == "e")
                m_rotateRight = true;
        };
        // ctx.mouse_pressed = [&](p6::MouseButton mouse) {
        //     if (mouse.button == p6::Button::Left)
        //     {
        //         m_rotateLeft = true;
        //     }
        //     else if (mouse.button == p6::Button::Right)
        //     {
        //         m_rotateRight = true;
        //     }
        // };
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
            else if (key.logical == "a")
                m_rotateLeft = false;
            else if (key.logical == "e")
                m_rotateRight = false;
        };
        // ctx.mouse_released = [&](p6::MouseButton mouse) {
        //     m_rotateLeft  = false;
        //     m_rotateRight = false;
        // };
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
