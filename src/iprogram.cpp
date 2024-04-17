#include "iprogram.hpp"
#include "glm/ext/matrix_transform.hpp"

// Initialisation
Program::Program(std::string texture_path, std::string vs_path, std::string fs_path)
    : m_image(p6::load_image_buffer(texture_path)), m_Program{p6::load_shader(vs_path, fs_path)}
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
    // mettre aussi ici les lumieres
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
void Program::use(const glm::mat4& viewmatrix, p6::Context& ctx, const glm::vec3& position, const float scale_value, glm::vec3 direction) const
{
    // Texture
    m_Program.use();
    // glActiveTexture(GL_TEXTURE0 + m_index);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_name);

    // std::cerr << m_uTexture << std::endl;
    // // glUniform1i(m_uTexture, m_index);
    // glUniform1i(m_uTexture, 0);

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    // glm::mat4 MVMatrix     = glm::translate(glm::mat4{1.f}, glm::vec3(0.f, 0.f, -5.f));
    // std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

    glm::mat4 MVMatrix     = glm::translate(glm::mat4{1.f}, position);
    MVMatrix               = glm::scale(MVMatrix, glm::vec3{scale_value});
    MVMatrix               = glm::rotate(MVMatrix, direction[0], glm::vec3{1, 0, 0});
    MVMatrix               = glm::rotate(MVMatrix, direction[1], glm::vec3{0, 1, 0});
    MVMatrix               = glm::rotate(MVMatrix, direction[2], glm::vec3{0, 0, 1});
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 MVPMatrix    = ProjMatrix * viewmatrix * MVMatrix;

    // envoi des matrices
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
}

void Program::useText() const
{
    // glUniform1i(m_uTexture, m_index);
    glUniform1i(m_uTexture, 0);
}