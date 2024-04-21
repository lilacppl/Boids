#include "iprogram.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/random.hpp"
#include "probas.hpp"

// Initialisation
Program::Program(std::string texture_path, std::string vs_path, std::string fs_path)
    : m_image(p6::load_image_buffer(texture_path)), m_Program{p6::load_shader(vs_path, fs_path)}, m_actual_state(0)
{
    // Création de la texture
    glGenTextures(1, &m_name);
    glBindTexture(GL_TEXTURE_2D, m_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Program::getUniformLocations()
{
    // Variable uniforme
    uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
    uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
    m_uTexture    = glGetUniformLocation(m_Program.id(), "TextureCoordinate");

    m_uKd             = glGetUniformLocation(m_Program.id(), "uKd");
    m_uKs             = glGetUniformLocation(m_Program.id(), "uKs");
    m_uKd2            = glGetUniformLocation(m_Program.id(), "uKd2");
    m_uKs2            = glGetUniformLocation(m_Program.id(), "uKs2");
    m_uShininess      = glGetUniformLocation(m_Program.id(), "uShininess");
    m_uLightDir_vs    = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
    m_uLightPos_vs    = glGetUniformLocation(m_Program.id(), "uLightPos_vs");
    m_uLightIntensity = glGetUniformLocation(m_Program.id(), "uLightIntensity");
}

void Program::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_name);
}
void Program::debind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

// A mettre avant le draw dans la boucle
void Program::use(const glm::mat4& viewmatrix, p6::Context& ctx, glm::vec3& position, float scale_value, glm::vec3 direction, float scale_down)
{
    // Texture
    m_Program.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_name);

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    // glm::mat4 MVMatrix     = glm::translate(glm::mat4{1.f}, glm::vec3(0.f, 0.f, -5.f));
    // std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

    glm::mat4 MVMatrix = glm::translate(glm::mat4{1.f}, position);
    // On oriente le poisson pour qu'il regarde dans la direction du déplacement
    MVMatrix = glm::rotate(MVMatrix, direction[0], glm::vec3{1, 0, 0});
    MVMatrix = glm::rotate(MVMatrix, direction[1], glm::vec3{0, 1, 0});
    MVMatrix = glm::rotate(MVMatrix, direction[2], glm::vec3{0, 0, 1});
    MVMatrix = glm::scale(MVMatrix, glm::vec3{scale_value});
    if (scale_down != 1) // je crois que cv tt le temps rentrer dedans car c un float donc jamais egal a 1
    {
        MVMatrix = glm::scale(MVMatrix, glm::vec3{1, scale_down, 1});
        // MVMatrix = glm::translate(MVMatrix, glm::vec3{0.0f, 1 * (1.0f - scale_down), 0.0f});
    }

    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 MVPMatrix    = ProjMatrix * viewmatrix * MVMatrix;

    // envoi des matrices
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    LightVarToShader(viewmatrix);
}

// // A mettre avant le draw dans la boucle
// void Program::use(const glm::mat4& viewmatrix, p6::Context& ctx, glm::vec3& position, float scale_value, const glm::vec3& arpenteur_position)
// {
//     // Texture
//     m_Program.use();
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, m_name);

//     glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
//     glm::mat4 MVMatrix     = glm::translate(glm::mat4{1.f}, position);
//     MVMatrix               = glm::scale(MVMatrix, glm::vec3{scale_value});
//     glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
//     glm::mat4 MVPMatrix    = ProjMatrix * viewmatrix * MVMatrix;

//     // envoi des matrices
//     glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
//     glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
//     glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
//     LightVarToShader(viewmatrix, arpenteur_position);
// }

void ::Program::LightVarToShader(const glm::mat4& viewmatrix)
{
    glUniform3f(m_uKd, 1., 1., 1.);  // lumiere blanche
    glUniform3f(m_uKs, 0., 0., 1.);  // reflets bleus
    glUniform3f(m_uKd2, 1., 0., 0.); // lumiere blanche
    glUniform3f(m_uKs, 1., 1., 1.);  // reflets bleus
    // glUniform1f(m_uShininess, randomShininess());
    glUniform1f(m_uShininess, 100.);
    glUniform3f(m_uLightDir_vs, lightDir_vs(viewmatrix).x, lightDir_vs(viewmatrix).y, lightDir_vs(viewmatrix).z);
    // glUniform3f(m_uLightPos_vs, lightPos_vs(viewmatrix, 10, 90, arpenteur_position).x, lightPos_vs(viewmatrix, 10, 90, arpenteur_position).y, lightPos_vs(viewmatrix, 10, 90, arpenteur_position).z);

    // glm::vec4 arp(arpenteur_position.x * -1, arpenteur_position.y, arpenteur_position.z, 1.0f);
    // glm::vec3 lightpos = (arp * viewmatrix);
    glUniform3f(m_uLightPos_vs, 0., 0., 0.);
    // glUniform3f(m_uLightPos_vs, arpenteur_position.x, arpenteur_position.y, arpenteur_position.z);
    // std::cout << arpenteur_position.x << std::endl;
    glUniform3f(m_uLightIntensity, 8., 8., 8.);
}

void Program::useText() const
{
    glUniform1i(m_uTexture, 0);
}

// a relier éventuellement aux maths

float randomShininess()
{
    return glm::linearRand(10.0f, 100.0f); // a relier aux maths
}

float randomIntensityValue()
{
    return glm::linearRand(0.5f, 1.5f);
}

glm::vec3 lightDir_vs(const glm::mat4& viewmatrix) // lumiere directionnelle : soleil

{
    glm::vec4 lightDir(1.0f, 1.0f, 1.0f, 1.0f);
    return glm::vec3(viewmatrix * lightDir);
}

glm::vec3 lightPos_vs(const glm::mat4& viewmatrix, const float radius, const float angle, const glm::vec3& position) // position de la lumiere ponctuelle
{
    // faire éventuellement tourner une light
    float x = radius * cos(angle);
    // glm::vec4 lightPos(x, 0, 1, 1.0f);
    glm::vec4 lightPos(position, 1.0f);
    return glm::vec3(viewmatrix * lightPos);
}

void Program::set_texture()
{
    chaine_markov(m_actual_state);
    // m_image = p6::load_image_buffer(textures[m_actual_state]);
    // glGenTextures(1, &m_name);
    // glBindTexture(GL_TEXTURE_2D, m_name);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);
}
