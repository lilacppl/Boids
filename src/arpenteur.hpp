#pragma once
#include <p6/p6.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> // pour glm::pi
#include "arpenteurcamera.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "mesh.hpp"
#include "vertices.hpp"

class Arpenteur {
private:
    glm::vec3       m_position;
    Vertices        m_vertices;
    float           m_Phi = 0.0f;
    float           m_Theta;
    glm::vec3       m_FrontVector = glm::vec3(-1., 0., 0.);
    glm::vec3       m_LeftVector  = glm::vec3(0., 0., 1.);
    glm::vec3       m_UpVector    = glm::vec3(.0, 1., 0.);
    Mesh            m_mesh;
    ArpenteurCamera m_camera;

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

public:
    Arpenteur();
    glm::vec3 getArpenteurPosition();
    void      update(const p6::Context& ctx, const Program& program, const int& time);
    glm::mat4 getViewMatrix();
    void      moveLeft(float t);
    void      moveFront(float t);
    void      moveUp(float t);
    void      rotateLeft(float degrees);
    void      eventManager(p6::Context& ctx);

    void handleMapBounds(const float square_radius);

    void eventUpdate();
};
