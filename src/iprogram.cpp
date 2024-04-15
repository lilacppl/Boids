#include "iprogram.hpp"

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

    // Variable uniforme
    uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
    uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
}

void Program::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_name);
}
void Program::debind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

// A mettre avant le draw dans la boucle
void Program::use(glm::mat4& viewmatrix, p6::Context* ctx)
{
    // Texture
    m_Program.use();
    // glActiveTexture(GL_TEXTURE0 + m_index);
    glBindTexture(GL_TEXTURE_2D, m_name);
    m_uTexture = glGetUniformLocation(m_Program.id(), "uTexture");
    glUniform1i(m_uTexture, m_index);

    // Variables uniformes
    const glm::mat4 globalMVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, -5.f});
    // glm::mat4       objectMVMatrix = glm::rotate(globalMVMatrix, 0, {0.f, 1.f, 0.f});
    glm::mat4 objectMVMatrix = glm::scale(objectMVMatrix, glm::vec3{0.2f});
    glm::mat4 projMatrix     = glm::inverse(viewmatrix) * glm::perspective(glm::radians(70.f), ctx->aspect_ratio(), 0.1f, 100.f);

    // envoi des matrices vers le GPU
    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(objectMVMatrix));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(objectMVMatrix))));
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * objectMVMatrix));
}