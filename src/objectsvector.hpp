
#pragma once
#include <p6/p6.h>
#include <vector>
#include "imguivariables.hpp"
#include "iprogram.hpp"
#include "mesh.hpp"
#include "objectposition.hpp"
// void setZ(ObjectPositionScale& obj)
// {
//     obj.setZ(-10);
// }

struct SceneObjectVector {
    std::vector<ObjectPositionScale> seaweed = {
        ObjectPositionScale(glm::vec3(0.0f, -5.f, 0.0f), 0.5f),
        ObjectPositionScale(glm::vec3(0.0f, -5.f, 1.0f), 0.9f),
        ObjectPositionScale(glm::vec3(0.0f, -5.f, 3.0f), 0.3f),
        ObjectPositionScale(glm::vec3(2.0f, -5.f, 4.0f), 0.2f),
        ObjectPositionScale(glm::vec3(-3.0f, -5.f, -1.0f), 0.4f),
        ObjectPositionScale(glm::vec3(-2.0f, -5.f, 1.0f), 0.3f),
        ObjectPositionScale(glm::vec3(1.0f, -5.f, 2.0f), 0.2f),
        ObjectPositionScale(glm::vec3(-4.0f, -5.f, -1.5f), 0.5f)
    }; // liste des algues sur forme de vector contenant position et scale
    std::vector<ObjectPositionScale> stone = {
        ObjectPositionScale(glm::vec3(0.0f, -5.f, -10.0f), 0.5f)
    };

    std::vector<ObjectPositionScale> shark = {
        ObjectPositionScale(glm::vec3(0.0f, 0.f, -20.0f), 10.f),
        ObjectPositionScale(glm::vec3(1.0f, 1.f, -20.0f), 5.f),
        ObjectPositionScale(glm::vec3(-3.0f, 1.f, -20.0f), 3.f)
    };

    void drawSceneObjOfSameMesh(const std::vector<ObjectPositionScale> list, const Mesh& mesh, const p6::Context& ctx, const glm::mat4& viewmatrix, const Program& program, const int& time) const
    {
        for (const auto& obj : list)
        {
            // Récupérer la position et l'échelle de l'objet
            glm::vec3 position = obj.getPosition();
            float     scale    = obj.getScale();
            mesh.DrawMesh(ctx, viewmatrix, program, position, scale, glm::vec3(0, 0, 0), 1., time);
        }
    }

    void drawShark(ObjectPositionScale& obj, const Mesh& mesh, const p6::Context& ctx, const glm::mat4& viewmatrix, const Program& program, ImguiVariables& var, const int& time) const
    {
        //     // Si z devient négatif, ajustez-le pour qu'il reste positif dans la plage
        //     // if (z < 0.0f) {
        //     //     z += maxZ;
        //     // }
        float z = obj.getPosition().z * (time / 1000);
        if (z > 6.)
        {
            z = -20;
        }
        obj.setZ(z);
        glm::vec3 position = glm::vec3(obj.getPosition().x, obj.getPosition().y, z);
        float     scale    = obj.getScale();
        mesh.DrawMesh(ctx, viewmatrix, program, obj.getPosition(), scale, glm::vec3(0, 0, 0), 1., time);
        // }
        // float movement_speed = 1.f;

        // // for (auto& obj : shark) // itérer sur une copie des objets
        // // {
        //     // Récupérer la position actuelle du requin
        //     glm::vec3 position = obj.getPosition();

        //     // Mettre à jour la position en fonction du temps et de la vitesse de déplacement
        //     position.z += movement_speed * (time / 1000);

        //     // Réinitialiser la position si le requin dépasse une certaine limite
        //     if (position.z > 6.0f)
        //     {
        //         position.z = -20.0f;
        //     }

        //     // Définir la nouvelle position du requin
        //     obj.setPosition(position);

        //     // Dessiner le requin avec sa nouvelle position
        //     float scale = obj.getScale();
        //     mesh.DrawMesh(ctx, viewmatrix, program, position, scale, glm::vec3(0, 0, 0), 1.0f, time);
        //}
    }

    // void drawAllObjectsOfSameMesh(Mesh& mesh, p6::Context& ctx, const glm::mat4& viewmatrix, Program& program) const
    // {
    //     draw(seaweed, mesh, ctx, viewmatrix, program);
    // }
};
