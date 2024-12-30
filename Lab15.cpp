#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

// Параметри генетичного алгоритму
const int POPULATION_SIZE = 50;
const int GENERATIONS = 1000;
const double CROSSOVER_RATE = 0.8;
const double MUTATION_RATE = 0.01;

struct Individual {
    double x1, x2;
    double fitness;

    Individual() : x1(0), x2(0), fitness(numeric_limits<double>::max()) {}

    void evaluate() {
        if (3 * x1 + 4 * x2 <= 25 && x1 >= 4 && x2 >= 4 && x1 >= 0 && x2 >= 0) {
            fitness = pow(x1 - 2, 2) + pow(x2 - 4, 2);
        } else {
            fitness = numeric_limits<double>::max(); // Якщо не задовольняє обмеженням, то велика вартість
        }
    }
};

void initialize_population(vector<Individual> &population) {
    for (auto &individual : population) {
        individual.x1 = ((double) rand() / RAND_MAX) * 10; // Ініціалізація x1 та x2 випадковими значеннями
        individual.x2 = ((double) rand() / RAND_MAX) * 10;
        individual.evaluate();
    }
}

Individual crossover(const Individual &parent1, const Individual &parent2) {
    Individual offspring;
    offspring.x1 = (parent1.x1 + parent2.x1) / 2;
    offspring.x2 = (parent1.x2 + parent2.x2) / 2;
    return offspring;
}

void mutate(Individual &individual) {
    if ((double) rand() / RAND_MAX < MUTATION_RATE) {
        individual.x1 += ((double) rand() / RAND_MAX - 0.5);
        individual.x2 += ((double) rand() / RAND_MAX - 0.5);
    }
}

Individual select_parent(const vector<Individual> &population) {
    int idx = rand() % POPULATION_SIZE;
    return population[idx];
}

int main() {
    srand(time(0));

    vector<Individual> population(POPULATION_SIZE);
    initialize_population(population);

    for (int generation = 0; generation < GENERATIONS; ++generation) {
        vector<Individual> new_population;

        for (int i = 0; i < POPULATION_SIZE; ++i) {
            Individual parent1 = select_parent(population);
            Individual parent2 = select_parent(population);

            Individual offspring = crossover(parent1, parent2);
            mutate(offspring);
            offspring.evaluate();

            new_population.push_back(offspring);
        }

        population = new_population;
    }

    Individual best_individual = population[0];
    for (const auto &individual : population) {
        if (individual.fitness < best_individual.fitness) {
            best_individual = individual;
        }
    }

    cout << "Best solution found: \n";
    cout << "x1 = " << best_individual.x1 << "\n";
    cout << "x2 = " << best_individual.x2 << "\n";
    cout << "Fitness = " << best_individual.fitness << "\n";

    return 0;
}
