#include "probas.hpp"

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

// renvoie une variable uniforme sur [min,max]
double uniform(const double min, const double max)
{
    return (max - min) * rand01() + min;
}

int plus_one()
{
    if (rand01() < 0.5)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// renvoie un nombre d'évènements suivant une loi de poisson de paramètre lambda
// lambda : nombre moyen d'évènement par intervalle de temps
int loi_de_poisson(const double lambda)
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
std::vector<int> events_times(const int poisson, const long long int temps_ecoule)
{
    std::vector<int> events;
    for (int i = 0; i < poisson; ++i)
    {
        // Utiliser une distribution uniforme pour déterminer le moment de l'événement
        double time_fraction = rand01();
        int    time          = static_cast<int>(time_fraction * 60000);
        events.push_back(time + temps_ecoule);
    }
    return events;
}

// loi normale pour la hauteur de l'eau
float loi_normale(const float esperance, const float ecart_type)
{
    // variable aléatoire uniforme entre 0 et 1
    double u1 = rand01();
    double u2 = rand01();
    // densité de probabilité d'une loi normale centrée réduite
    double z1     = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
    double sample = esperance + ecart_type * z1;
    // std::cout << 1 / (ecart_type / sqrt(2 * 3.14)) * exp((-1 / 2) * pow((((rand01() * 100 - 50) - esperance) / ecart_type), 2)) << std::endl;
    return sample;
}

bool water_level(const long long int temps, std::vector<int>& event_time_table, const int& number_events)
{
    if (temps % 60000 == 0)
    {
        event_time_table = events_times(number_events, temps);
    }
    return std::find(event_time_table.begin(), event_time_table.end(), temps) != event_time_table.end();
}

void markov_suivant(int& actual_state, const glm::vec4 v)
{
    float a = rand01();
    if (a < v[0])
    {
        actual_state = 0;
    }
    else if (a < v[0] + v[1])
    {
        actual_state = 1;
    }
    else if (a < v[0] + v[1] + v[2])
    {
        actual_state = 2;
    }
    else if (a < v[0] + v[1] + v[2] + v[3])
    {
        actual_state = 3;
    }
    else
    {
        actual_state = 4;
    }
}

void chaine_markov(int& actual_state)
{
    switch (actual_state)
    {
    case 0:
        markov_suivant(actual_state, mat[0]);
        break;
    case 1:
        markov_suivant(actual_state, mat[1]);
        break;
    case 2:
        markov_suivant(actual_state, mat[2]);
        break;
    case 3:
        markov_suivant(actual_state, mat[3]);
        break;
    }
}

bool texture_markov(const Timer chrono)
{
    if (tempsEcoule(chrono) % 30000)
        return true;
    else
        return false;
}
