#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
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
#include "boids.hpp"
#include "doctest/doctest.h"
#include "glm/glm.hpp"

static std::vector<int> event_time_table;

// Matrice de passage pour chaîne de Markov
static glm::mat4 mat{{1.0 / 2., 1. / 6., 1. / 6., 1. / 6.}, {1. / 4., 1. / 8., 1. / 4., 3. / 8.}, {1. / 6., 1. / 6., 1. / 2., 1. / 6.}, {1. / 4., 3. / 8., 1. / 4., 1. / 8.}};

// vecteur des textures pour poissons
static const std::vector<std::string> textures{"../assets/fish_color.png", "../assets/fish_color.png", "../assets/fish_color.png", "../assets/fish_color.png", "../assets/fish_color.png"};

// Structure pour stocker le temps de début ( à mettre juste avant la boucle)
struct Timer {
    std::chrono::high_resolution_clock::time_point debut;
    Timer()
        : debut(std::chrono::high_resolution_clock::now()) {}
    void reset()
    {
        debut = std::chrono::high_resolution_clock::now();
    }
};

// Fonction renvoyant le temps écoulé depuis le début de la boucle en millisecondes (dans la boucle)
long long int tempsEcoule(const Timer& timer);

// renvoie une variable réelle uniforme entre 0 et 1
double rand01();
double uniform(const double min, const double max);
int    plusOne();

// renvoie un nombre d'évènements suivant une loi de poisson de paramètre lambda
// lambda : nombre moyen d'évènement par intervalle de temps
int loiDePoisson(const double lambda);

// loi uniforme pour répartir les lambda évènements dans l'intervalle
std::vector<int> eventsTimes(const int poisson, const int& temps_ecoule, int duree);
// loi normale pour la hauteur de l'eau
float loiNormale(const float esperance, const float ecart_type);

void   markovSuivant(int& actual_state, const glm::vec4& v);
void   chaineMarkov(int& actual_state);
bool   textureMarkov(const Timer chrono);
double loiExponentielle(double min, double max, double lambda);
double loiBeta(float alpha, float beta);
double betaReduite();

static bool niveauEau(const int& temps, std::vector<int>& event_time_table, const int& number_events, int duree)
{
    if (temps % duree == 0)
    {
        // Générer les temps des événements si nécessaire
        std::vector<int> generated_event_times = eventsTimes(number_events, temps, duree);
        event_time_table                       = generated_event_times;
    }

    return (std::find(event_time_table.begin(), event_time_table.end(), temps) != event_time_table.end());

    // return false;
}
// std::pair<int, int>               eventsTimesShark(const int& temps_ecoule, int duree, int duree_requins);
std::vector<std::pair<int, int>> eventsTimesShark(const int& temps_ecoule, int duree, int duree_requins);
