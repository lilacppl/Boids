#include "objectsvector.hpp"

void SceneObjectVector::drawSceneObjOfSameMesh(const std::vector<ObjectPositionScale> list, const Mesh& mesh, const p6::Context& ctx, const glm::mat4& viewmatrix, const Program& program, const int& time) const
{
    for (const auto& obj : list)
    {
        glm::vec3 position = obj.getPosition();
        float     scale    = obj.getScale();
        mesh.DrawMesh(ctx, viewmatrix, program, position, scale, glm::vec3(0, 0, 0), 1., time);
    }
}

void SceneObjectVector::drawShark(const Mesh& mesh, const p6::Context& ctx, const glm::mat4& viewmatrix, const Program& program, ImguiVariables& var, const int& time) const
{
    for (const auto& obj : shark)
    {
        float     z        = obj.getPosition().z + time / 100;
        glm::vec3 position = glm::vec3(obj.getPosition().x, obj.getPosition().y, z);
        float     scale    = obj.getScale();
        mesh.DrawMesh(ctx, viewmatrix, program, position, scale, glm::vec3(0, 0, 0), 1., time);
    }
}