
#pragma once
#include <p6/p6.h>
#include <vector>
#include "iprogram.hpp"
#include "mesh.hpp"
#include "objectposition.hpp"

struct SceneObjectVector {
    std::vector<ObjectPositionScale> seaweed = {
        ObjectPositionScale(glm::vec3(0.0f, -5.f, 0.0f), 0.5f),
        ObjectPositionScale(glm::vec3(0.0f, -5.f, 1.0f), 0.9f),
        ObjectPositionScale(glm::vec3(0.0f, -5.f, 3.0f), 0.3f)
    }; // liste des algues sur forme de vector contenant position et scale

    void drawSceneObjOfSameMesh(std::vector<ObjectPositionScale> list, Mesh& mesh, p6::Context& ctx, const glm::mat4& viewmatrix, Program& program) const
    {
        for (const auto& obj : list)
        {
            // Récupérer la position et l'échelle de l'objet
            glm::vec3 position = obj.getPosition();
            float     scale    = obj.getScale();
            mesh.DrawMesh(ctx, viewmatrix, program, position, scale);
        }
    }

    // void drawAllObjectsOfSameMesh(Mesh& mesh, p6::Context& ctx, const glm::mat4& viewmatrix, Program& program) const
    // {
    //     draw(seaweed, mesh, ctx, viewmatrix, program);
    // }
};