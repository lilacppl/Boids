
#pragma once
#include <p6/p6.h>
#include <vector>
#include "imguivariables.hpp"
#include "iprogram.hpp"
#include "mesh.hpp"
#include "objectposition.hpp"

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
    std::vector<ObjectPositionScale> mushroom = {
        ObjectPositionScale(glm::vec3(-3.0f, -5.f, -9.5f), 3.f),
        ObjectPositionScale(glm::vec3(0.5f, -5.f, -7.0f), 1.f),
        ObjectPositionScale(glm::vec3(0.3f, -5.f, -4.f), 0.2f),
        ObjectPositionScale(glm::vec3(0.1f, -5.f, -4.f), 0.4f)
    };

    std::vector<ObjectPositionScale> shark = {
        ObjectPositionScale(glm::vec3(0.0f, 0.f, -20.0f), 10.f),
        ObjectPositionScale(glm::vec3(1.0f, 1.f, -20.0f), 5.f),
        ObjectPositionScale(glm::vec3(-3.0f, 1.f, -20.0f), 3.f)
    };

    void drawSceneObjOfSameMesh(const std::vector<ObjectPositionScale> list, const Mesh& mesh, const p6::Context& ctx, const glm::mat4& viewmatrix, const Program& program, const int& time) const;
    void drawShark(const Mesh& mesh, const p6::Context& ctx, const glm::mat4& viewmatrix, const Program& program, ImguiVariables& var, const int& time) const;
};