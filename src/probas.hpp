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
#include "doctest/doctest.h"
#include "glm/glm.hpp"

static std::vector<int> event_time_table;

// Matrice de passage pour chaîne de Markov
static const glm::mat4 mat{{1 / 2, 1 / 6, 1 / 6, 1 / 6}, {1 / 4, 1 / 8, 1 / 4, 3 / 8}, {1 / 6, 1 / 6, 1 / 2, 1 / 6}, {1 / 4, 3 / 8, 1 / 4, 1 / 8}};

// Structure pour stocker le temps de début ( à mettre juste avant la boucle)
struct Timer {
    std::chrono::high_resolution_clock::time_point debut;
    Timer()
        : debut(std::chrono::high_resolution_clock::now()) {}
};

long long int    tempsEcoule(const Timer& timer);
double           rand01();
double           uniform(const int min, const int max);
int              loi_de_poisson(double lambda);
std::vector<int> events_times(int poisson, long long int temps_ecoule);
double           loi_normale();
bool             water_level(long long int temps, std::vector<int> event_time_table, int& number_events);
void             markov_suivant(int& actual_state, glm::vec4 v);
void             chaine_markov(int actual_state);