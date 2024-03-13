
#pragma once
#include "imguivariables.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "boids.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"
#include "imguivariables.hpp"


class Scene{
    //mettre les objets de la scene ici ?
    //camera par exemple ?
    //cube..
    //etc
    private:
        ImguiVariables m_imguiVariables;
        Boids m_first_boids;

    public:
        Scene() = default;
        void InitializeClasses();
        void update(p6::Context& ctx);
};