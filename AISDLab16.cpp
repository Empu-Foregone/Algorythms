#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>  // Додаємо цю бібліотеку для INT_MAX
#include <cmath>

#define POPULATION_SIZE 2927   // Збільшено розмір популяції
#define GENERATIONS 5000      // Збільшено кількість поколінь
#define CROSSOVER_RATE 0.4    // Вищий коефіцієнт схрещування
#define MUTATION_RATE 0.5    // Знижений коефіцієнт мутації
#define TARGET_FITNESS 3      // Ідеальний розв'язок, коли рівняння виконано точно

// Структура індивідуума
struct Individual {
    int x;
    int y;
    int fitness;
};

// Фітнес-функція: оцінка відповідності рівнянню
int fitness(Individual ind) {
    // Рівняння: x^2 - xy + y^2 = x + y
    int left = ind.x * ind.x - ind.x * ind.y + ind.y * ind.y;
    int right = ind.x + ind.y;
    return std::abs(left - right);  // Чим менше значення, тим краще
}

// Ініціалізація популяції
void init_population(Individual population[POPULATION_SIZE]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i].x = rand() % 2001 - 1000;  // x від -1000 до 1000
        population[i].y = rand() % 2001 - 1000;  // y від -1000 до 1000
        population[i].fitness = fitness(population[i]);
    }
}

// Селекція: вибір кращих індивідуумів
void selection(Individual population[POPULATION_SIZE], Individual selected[POPULATION_SIZE / 2]) {
    int selected_index = 0;
    for (int i = 0; i < POPULATION_SIZE / 2; i++) {
        int min_fitness = INT_MAX;
        int best_index = 0;
        // Вибір індивідуума з найкращою фітнес-оцінкою
        for (int j = 0; j < POPULATION_SIZE; j++) {
            if (population[j].fitness < min_fitness) {
                min_fitness = population[j].fitness;
                best_index = j;
            }
        }
        selected[selected_index++] = population[best_index];
        population[best_index].fitness = INT_MAX;  // Відмічаємо цей індивідуум як обраний
    }
}

// Схрещування: створення нового індивідуума
Individual crossover(Individual parent1, Individual parent2) {
    Individual offspring;
    if (rand() / (double)RAND_MAX < CROSSOVER_RATE) {
        offspring.x = (rand() % 2) ? parent1.x : parent2.x;
        offspring.y = (rand() % 2) ? parent1.y : parent2.y;
    } else {
        offspring.x = parent1.x;
        offspring.y = parent1.y;
    }
    offspring.fitness = fitness(offspring);
    return offspring;
}

// Мутація: випадкова зміна значень
void mutate(Individual* ind) {
    if (rand() / (double)RAND_MAX < MUTATION_RATE) {
        ind->x = rand() % 2001 - 1000;  // Нові значення x в діапазоні від -1000 до 1000
        ind->y = rand() % 2001 - 1000;  // Нові значення y в діапазоні від -1000 до 1000
        ind->fitness = fitness(*ind);
    }
}

// Головна функція
int main() {
    srand(time(NULL));  // Ініціалізація генератора випадкових чисел

    Individual population[POPULATION_SIZE];
    Individual selected[POPULATION_SIZE / 2];
    int generation = 0;

    // Ініціалізація популяції
    init_population(population);

    // Основний цикл генетичного алгоритму
    while (generation < GENERATIONS) {
        selection(population, selected);

        // Створення нових особин через схрещування та мутацію
        for (int i = 0; i < POPULATION_SIZE / 2; i++) {
            Individual offspring = crossover(selected[i], selected[(i + 1) % (POPULATION_SIZE / 2)]);
            mutate(&offspring);
            population[i] = offspring;
        }

        // Перевірка, чи знайдений розв'язок
        for (int i = 0; i < POPULATION_SIZE; i++) {
            if (population[i].fitness == TARGET_FITNESS) {
                std::cout << "Розв'язок знайдено: x = " << population[i].x << ", y = " << population[i].y << std::endl;
                return 0;
            }
        }

        generation++;
    }

    // Якщо розв'язок не знайдено
    std::cout << "Розв'язок не знайдено після " << GENERATIONS << " поколінь." << std::endl;
    return 0;
}
