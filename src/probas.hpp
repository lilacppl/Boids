#pragma once

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>
#include "doctest/doctest.h"
#include "glm/fwd.hpp"

double rand01()
{
    thread_local std::default_random_engine gen{std::random_device{}()};
    thread_local auto                       distrib = std::uniform_real_distribution<double>{0.0, 1.0};

    return distrib(gen);
}

// lambda : nombre moyen d'évènement par intervalle de temps
// renvoie un nombre d'évènements suivant une loi de poisson de paramètre lambda
int loi_de_poisson(double lambda)
{
    int    k = 0;
    double p = exp(-lambda);
    double F = p;
    double U = rand01();
    while (U > F)
    {
        k++;
        p = p * lambda / k;
        F += p;
    }
    return k;
}

// loi uniforme pour répartir les lambda évènements dans l'intervalle
std::vector<int> events_times()
{
    std::vector<int> events;
    for (int i = 0; i < loi_de_poisson(3); ++i)
    {
        // Utiliser une distribution uniforme pour déterminer le moment de l'événement
        double time_fraction = rand01();
        int    time          = static_cast<int>(time_fraction * 120);
        events.push_back(time);
    }
    return events;
}

// loi normale pour la hauteur de l'eau