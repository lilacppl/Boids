#pragma once

#include <iostream>
#include <vector>

class Boids {
    std::vector<double> position[3];
    std::vector<double> direction[3];
    std::vector<double> vitesse[3];
};