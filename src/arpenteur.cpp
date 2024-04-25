#pragma once
#include "arpenteur.hpp"

Arpenteur::Arpenteur()
    : m_position(glm::vec3(0.0f)), m_mesh(m_vertices.fish), m_Phi(0.), m_Theta(0.0f)
{
    m_camera.updatePosition(m_position, 0);
}

glm::vec3 Arpenteur::getArpenteurPosition()
{
    return m_position;
}

void Arpenteur::update(const p6::Context& ctx, const Program& program, const int& time)
{
    m_camera.updatePosition(m_position, m_Phi);
    handleMapBounds(4.0);
    m_mesh.DrawMesh(ctx, m_camera.getViewMatrix(m_position), program, m_position, 0.1, glm::vec3(0., 0., 0.), 1., time);
}

glm::mat4 Arpenteur::getViewMatrix()
{
    return m_camera.getViewMatrix(m_position);
}

void Arpenteur::moveLeft(const float t)
{
    m_position += t * m_LeftVector;
}

void Arpenteur::moveFront(const float t)
{
    m_position += t * m_FrontVector;
}

void Arpenteur::moveUp(const float t)
{
    glm::vec3 upMovement = t * m_UpVector;
    m_position += upMovement;
}

void Arpenteur::rotateLeft(const float degrees)
{
    m_Phi += glm::radians(degrees);
}

void Arpenteur::handleMapBounds(const float square_radius)
{
    float margin = 1.0;
    if (m_position[0] < -square_radius)
    {
        m_position.x = square_radius - 0.1;
    }
    if (m_position[0] > square_radius * margin)
    {
        m_position.x = -square_radius + 0.1;
    }
    if (m_position[1] < -square_radius * margin)
    {
        m_position.y = square_radius - 0.1;
    }
    if (m_position[1] > square_radius * margin)
    {
        m_position.y = -square_radius + 0.1;
    }
    if (m_position[2] < -square_radius * margin)
    {
        m_position.z = square_radius - 0.1;
    }
    if (m_position[2] > square_radius * margin)
    {
        m_position.z = -square_radius + 0.1;
    }
}

void Arpenteur::eventManager(p6::Context& ctx)
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
        else if (key.logical == "a")
            m_rotateLeft = true;
        else if (key.logical == "e")
            m_rotateRight = true;
    };
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
}

void Arpenteur::eventUpdate()
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