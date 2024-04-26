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

int plusOne()
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
int loiDePoisson(const double lambda)
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
std::vector<int> eventsTimes(const int poisson, const int& temps_ecoule, int duree)
{
    std::vector<int> events;
    for (int i = 0; i < poisson; ++i)
    {
        // Utiliser une distribution uniforme pour déterminer le moment de l'événement
        double time_fraction = rand01();
        int    time          = static_cast<int>(time_fraction * duree);
        events.push_back(time + temps_ecoule);
    }
    // std::cout<<events[0]<< ", temps  "<<temps_ecoule<<std::endl;
    return events;
}

// loi normale pour la hauteur de l'eau
float loiNormale(const float esperance, const float ecart_type)
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

void markovSuivant(int& actual_state, const glm::vec4& v)
{
    float a = rand01();
    // if (a < v[0])
    // {
    //     actual_state = 0;
    //     std::cout << "Transition vers l'état 0" << std::endl;
    // }
    // else if (a < v[0] + v[1])
    // {
    //     actual_state = 1;
    //     std::cout << "Transition vers l'état 1" << std::endl;
    // }
    // else if (a < v[0] + v[1] + v[2])
    // {
    //     actual_state = 2;
    // }
    // else if (a < v[0] + v[1] + v[2] + v[3])
    // {
    //     actual_state = 3;
    // }
    // else
    // {
    //     actual_state = 4;
    //     std::cout << "cest le 4" << std::endl;
    // }
    if (a < v[0])
    {
        actual_state = 0;
        std::cout << "Transition vers l'état 0" << std::endl;
    }
    else if (a < v[1])
    {
        actual_state = 1;
        std::cout << "Transition vers l'état 1" << std::endl;
    }
    else if (a < v[2])
    {
        actual_state = 2;
    }
    else if (a < v[3])
    {
        actual_state = 3;
    }
    else
    {
        actual_state = 4;
        // std::cout << "cest le 4" << std::endl;
    }
    std::cout << "valeur du vecteur" << v[0] << v[1] << std::endl;
}

void chaineMarkov(int& actual_state)
{
    switch (actual_state)
    {
    case 0:
        markovSuivant(actual_state, mat[0]);
        break;
    case 1:
        markovSuivant(actual_state, mat[1]);
        break;
    case 2:
        markovSuivant(actual_state, mat[2]);
        break;
    case 3:
        markovSuivant(actual_state, mat[3]);
        break;
    }
}

bool textureMarkov(const Timer chrono)
{
    if (tempsEcoule(chrono) % 30000)
        return true;
    else
        return false;
}

double loiBeta(float alpha, float beta)
{
    float x, y;
    do
    {
        float u = rand01();
        float v = rand01();

        x = std::pow(u, 1.0f / alpha);
        y = std::pow(v, 1.0f / beta);
    } while (x + y > 1.0f);

    return (2.0f * x / (x + y)) - 1.0f;
}

double betaReduite()
{
    return loiBeta(2.0, 2.0) / 1.6 + 1.0;
}

double loiExponentielle(double min, double max, double lambda)
{
    // génération d'un float selon loi exponentielle avec la méthode de l'inverse
    // de la fonction de répartition
    double u1 = rand01();
    double u2 = -log(1 - u1) / lambda;
    return min + (max - min) * u2;
}

std::vector<std::pair<int, int>> eventsTimesShark(const int& temps_ecoule, int duree, int duree_requins)
{
    double                         lambda = 10;
    std::default_random_engine     generator;
    std::poisson_distribution<int> poisson_distribution(lambda);
    int                            number_of_events = poisson_distribution(generator);

    std::vector<std::pair<int, int>> event_times;
    for (int i = 0; i < number_of_events; ++i)
    {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        double                                 time_fraction = distribution(generator);
        int                                    spawn_time    = static_cast<int>(time_fraction * duree) + temps_ecoule; // Instant de spawn du requin
        int                                    despawn_time  = spawn_time + duree_requins;                             // Instant de disparition du requin

        event_times.push_back(std::make_pair(spawn_time, despawn_time));
        std::cout << "event shark ajouté" << std::endl;
    }

    return event_times;
}
