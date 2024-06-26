#include "iprogram.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/random.hpp"
#include "probas.hpp"

// Initialisation
Program::Program(std::string texture_path, std::string vs_path, std::string fs_path)
    : m_image(p6::load_image_buffer(texture_path)), m_Program{p6::load_shader(vs_path, fs_path)}, m_actual_state(0), m_shininess(20.), m_intensity(2), m_intensity2(10), m_r(randomColor()), m_g(randomColor()), m_b(randomColor())
{
    // Création de la texture
    glGenTextures(1, &m_name);
    glBindTexture(GL_TEXTURE_2D, m_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    getUniformLocations();
}

void Program::getUniformLocations()
{
    // Variable uniforme
    uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
    uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
    m_uTexture    = glGetUniformLocation(m_Program.id(), "TextureCoordinate");

    m_uKd              = glGetUniformLocation(m_Program.id(), "uKd");
    m_uKs              = glGetUniformLocation(m_Program.id(), "uKs");
    m_uKd2             = glGetUniformLocation(m_Program.id(), "uKd2");
    m_uKs2             = glGetUniformLocation(m_Program.id(), "uKs2");
    m_uShininess       = glGetUniformLocation(m_Program.id(), "uShininess");
    m_uLightDir_vs     = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
    m_uLightPos_vs     = glGetUniformLocation(m_Program.id(), "uLightPos_vs");
    m_uLightIntensity  = glGetUniformLocation(m_Program.id(), "uLightIntensity");
    m_uLightIntensity2 = glGetUniformLocation(m_Program.id(), "uLightIntensity2");
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
void Program::use(const glm::mat4& viewmatrix, const p6::Context& ctx, const glm::vec3& position, const float scale_value, const glm::vec3 direction, const float scale_down, const int& time) const
{
    // Texture
    m_Program.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_name);

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix   = glm::mat4{1.f};
    MVMatrix             = glm::translate(MVMatrix, glm::vec3{0.0, -(1.0 - scale_down) * scale_value / 2.0, 0.0});
    MVMatrix             = glm::scale(MVMatrix, glm::vec3{1, scale_down, 1});
    MVMatrix             = glm::translate(glm::mat4{1.f}, position);

    // On oriente le poisson pour qu'il regarde dans la direction du déplacement
    MVMatrix = glm::rotate(MVMatrix, direction[0], glm::vec3{1, 0, 0});
    MVMatrix = glm::rotate(MVMatrix, direction[1], glm::vec3{0, 1, 0});
    MVMatrix = glm::rotate(MVMatrix, direction[2], glm::vec3{0, 0, 1});
    MVMatrix = glm::scale(MVMatrix, glm::vec3{scale_value});

    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 MVPMatrix    = ProjMatrix * viewmatrix * MVMatrix;

    // envoi des matrices
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    LightVarToShader(viewmatrix, time);
}

void Program::LightVarToShader(const glm::mat4& viewmatrix, const int& time) const
{
    glUniform3f(m_uKd, 1., 1., 1.); // lumiere blanche
    glUniform3f(m_uKs, 0., 0., 1.);
    glUniform3f(m_uKd2, m_r, 0., 0.); // lumiere rouge d'intensité aléatoire m_r
    glUniform3f(m_uKs, 1., 1., 1.);
    glUniform1f(m_uShininess, 20.);
    glUniform3f(m_uLightDir_vs, 1, 1, 1);
    glUniform3f(m_uLightPos_vs, lightPos_vs(viewmatrix, time).x, lightPos_vs(viewmatrix, time).y, lightPos_vs(viewmatrix, time).z);
    glUniform3f(m_uLightIntensity, m_intensity, m_intensity, m_intensity);
    glUniform3f(m_uLightIntensity2, m_intensity2, m_intensity2, m_intensity2);
}

void Program::useText() const
{
    glUniform1i(m_uTexture, 0);
}

float randomIntensityValue()
{
    return loiExponentielle(0.6f, 1.0f, 1.5);
}

float randomColor()
{
    return uniform(0.7, 1.0);
}

glm::vec3 lightPos_vs(const glm::mat4& viewmatrix, const int& time) // position de la lumiere ponctuelle
{
    // faire éventuellement tourner une light
    float     radius           = 5.0;
    float     rotationSpeed    = 0.005;
    float     translationSpeed = 0.1;
    float     angle            = time * rotationSpeed;
    float     translation      = time * translationSpeed;
    float     x                = radius * cos(angle);
    float     z                = radius * sin(angle);
    glm::vec4 lightPos(x, 1, z, 1.0f);
    return glm::vec3(viewmatrix * lightPos);
}

void Program::deleteTextureBufferArray() const
{
    glDeleteTextures(1, &m_name);
}