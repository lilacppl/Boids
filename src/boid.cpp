
#include "boid.hpp"
#include "probas.hpp"
// #include <bits/stdc++.h>

// std::default_random_engine            gen;
// std::uniform_real_distribution<float> distrib_pos(-2.0f, 2.0f);
// std::uniform_real_distribution<float> distrib_speed(0.03f, 0.05f);
// std::vector<int>                      rand_speed{-1, 1};
// std::uniform_int_distribution<int>    distrib_int(0, 1);

Boid::Boid()
    : m_radius(0.01f), m_speed(glm::vec3{loi_normale(0.04f, 0.01f) * plus_one(), loi_normale(0.04f, 0.01f) * plus_one(), loi_normale(0.04f, 0.01f) * plus_one()}), m_position(glm::vec3{uniform(-2.0, 2.0), uniform(-2.0, 2.0), uniform(-2.0, 2.0)}), m_direction(glm::vec3{0.0f, 0.0f, 0.0f})
{}

glm::vec3 Boid::get_position() const
{
    return m_position;
}

glm::vec3 Boid::get_speed() const
{
    return m_speed;
}

void Boid::draw(const p6::Context& ctx, Mesh& mesh, const glm::mat4 viewMatrix, const Program& program)
{
    // ctx.fill = {1, 1, 1, 0.5};
    // ctx.square(p6::Center{get_position()}, p6::Radius{0.01f});
    glm::vec3 position = get_position();
    // std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
    mesh.DrawMesh(ctx, viewMatrix, program, position, .1f, m_direction, 1.0f);
}
glm::vec3 calculate_rotation(const glm::vec3 speed)
{
    return glm::vec3{
        atan2(-speed[2], speed[0]), atan2(-speed[1], speed[0]), 0
    };
}

void Boid::move(float square_radius, float maxspeed, float minspeed)
{
    float margin     = 0.90;
    float turnfactor = 0.001;
    // float maxspeed   = 0.006;
    // float minspeed   = 0.002;
    if (m_position[0] < -square_radius * margin)
    {
        m_speed[0] += turnfactor;
    }
    if (m_position[0] > square_radius * margin)
    {
        m_speed[0] -= turnfactor;
    }
    if (m_position[1] < -square_radius * margin)
    {
        m_speed[1] += turnfactor;
    }
    if (m_position[1] > square_radius * margin)
    {
        m_speed[1] -= turnfactor;
    }
    if (m_position[2] < -square_radius * margin)
    {
        m_speed[2] += turnfactor;
    }
    if (m_position[2] > square_radius * margin)
    {
        m_speed[2] -= turnfactor;
    }
    float speed = sqrt(m_speed[0] * m_speed[0] + m_speed[1] * m_speed[1] + m_speed[2] * m_speed[2]);
    if (speed > maxspeed)
    {
        m_speed[0] = (m_speed[0] / speed) * maxspeed;
        m_speed[1] = (m_speed[1] / speed) * maxspeed;
        m_speed[2] = (m_speed[2] / speed) * maxspeed;
    }

    if (speed < minspeed)
    {
        m_speed[0] = (m_speed[0] / speed) * minspeed;
        m_speed[1] = (m_speed[1] / speed) * minspeed;
        m_speed[2] = (m_speed[2] / speed) * minspeed;
    }

    glm::vec3 new_pos = m_speed + m_position;
    m_position        = new_pos;
    m_direction       = calculate_rotation(m_position);
}
