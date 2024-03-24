#pragma once
#define _USE_MATH_DEFINES
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <random>
#include <thread>
#include <vector>
#include "doctest/doctest.h"
#include "glm/fwd.hpp"

// Structure pour stocker le temps de début ( à mettre juste avant la boucle)
struct Timer {
    std::chrono::high_resolution_clock::time_point debut;
    Timer()
        : debut(std::chrono::high_resolution_clock::now()) {}
};

// Fonction renvoyant le temps écoulé depuis le début de la boucle en millisecondes (dans la boucle)
long long int tempsEcoule(const Timer& timer)
{
    auto current = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(current - timer.debut).count();
}

// renvoie une variable réelle uniforme entre 0 et 1
double rand01()
{
    thread_local std::default_random_engine gen{std::random_device{}()};
    thread_local auto                       distrib = std::uniform_real_distribution<double>{0.0, 1.0};

    return distrib(gen);
}

// renvoie un nombre d'évènements suivant une loi de poisson de paramètre lambda
// lambda : nombre moyen d'évènement par intervalle de temps
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
        int    time          = static_cast<int>(time_fraction * 60000);
        events.push_back(time);
    }
    return events;
}

// loi normale pour la hauteur de l'eau
double loi_normale()
{
    float esperance  = 3;
    float ecart_type = 2;
    // variable aléatoire uniforme entre 0 et 1
    double u1 = rand01();
    // densité de probabilité d'une loi normale centrée réduite
    double z1 = 1 / (sqrt(2 * M_PI) * ecart_type) * exp(-((u1 - esperance) * (u1 - esperance)) / (2 * ecart_type * ecart_type));

    return z1;
}

void water_level(long long int& temps, std::vector<int> event_time_table, int& number_events)
{
    if (temps % 60000 == 0)
    {
        number_events    = loi_de_poisson(2);
        event_time_table = events_times();
    }
    if (std::find(event_time_table.begin(), event_time_table.end(), temps) != event_time_table.end())
    {
        // baisser l'eau
    }
}