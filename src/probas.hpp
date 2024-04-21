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
static glm::mat4 mat{{1 / 2, 1 / 6, 1 / 6, 1 / 6}, {1 / 4, 1 / 8, 1 / 4, 3 / 8}, {1 / 6, 1 / 6, 1 / 2, 1 / 6}, {1 / 4, 3 / 8, 1 / 4, 1 / 8}};

// vecteur des textures pour poissons
static const std::vector<std::string> textures{"../assets/fish_color.png", "../assets/fish_color.png", "../assets/fish_color.png", "../assets/fish_color.png","../assets/fish_color.png"};

// Structure pour stocker le temps de début ( à mettre juste avant la boucle)
struct Timer {
    std::chrono::high_resolution_clock::time_point debut;
    Timer()
        : debut(std::chrono::high_resolution_clock::now()) {}
};

// Fonction renvoyant le temps écoulé depuis le début de la boucle en millisecondes (dans la boucle)
long long int tempsEcoule(const Timer& timer);

// renvoie une variable réelle uniforme entre 0 et 1
double rand01();
double uniform(const double min, const double max);
int    plus_one();

// renvoie un nombre d'évènements suivant une loi de poisson de paramètre lambda
// lambda : nombre moyen d'évènement par intervalle de temps
int loi_de_poisson(double lambda);

// loi uniforme pour répartir les lambda évènements dans l'intervalle
std::vector<int> events_times();
// loi normale pour la hauteur de l'eau
float loi_normale(float esperance, float ecart_type);

bool water_level(long long int& temps, std::vector<int> event_time_table, int& number_events);

void markov_suivant(int& actual_state, const glm::vec4 v);
void chaine_markov(int& actual_state);
bool texture_markov(Timer chrono);
