#include <iostream>
#include <vector>
#include <chrono> // для вимірювання часу
#include <iomanip> // для форматування виводу
#include <cstdlib> // для генерації випадкових чисел

// Структура для збору статистики
struct SortStats {
    size_t comparisons = 0;   // Кількість порівнянь
    size_t assignments = 0;   // Кількість присвоєнь
};

// Розбиття масиву для швидкого сортування
size_t partition(std::vector<int>& arr, size_t low, size_t high, SortStats& stats) {
    int pivot = arr[high]; // Вибираємо опорний елемент
    stats.assignments++; // Присвоєння для pivot
    size_t i = low - 1;   // Індекс для меншого елемента

    for (size_t j = low; j < high; ++j) {
        stats.comparisons++; // Порівняння arr[j] з pivot
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
            stats.assignments += 3; // Swap виконує 3 присвоєння
        }
    }
    std::swap(arr[i + 1], arr[high]);
    stats.assignments += 3; // Swap для опорного елемента
    return i + 1;
}

// Алгоритм швидкого сортування
void quickSort(std::vector<int>& arr, size_t low, size_t high, SortStats& stats) {
    if (low < high) {
        size_t pi = partition(arr, low, high, stats);
        if (pi > 0) quickSort(arr, low, pi - 1, stats); // Сортуємо ліву частину
        quickSort(arr, pi + 1, high, stats);           // Сортуємо праву частину
    }
}

// Функція для генерації масиву
std::vector<int> generateArray(size_t n, const std::string& type) {
    std::vector<int> arr(n);
    if (type == "random") {
        for (size_t i = 0; i < n; ++i) {
            arr[i] = rand() % 10000;
        }
    } else if (type == "ascending") {
        for (size_t i = 0; i < n; ++i) {
            arr[i] = i;
        }
    } else if (type == "descending") {
        for (size_t i = 0; i < n; ++i) {
            arr[i] = n - i - 1;
        }
    }
    return arr;
}

int main() {
    std::vector<size_t> sizes = {10, 100, 1000, 5000, 10000};
    std::vector<std::string> types = {"random", "ascending", "descending"};

    std::cout << std::setw(10) << "Size"
              << std::setw(15) << "Type"
              << std::setw(20) << "Time (ms)"
              << std::setw(20) << "Comparisons"
              << std::setw(20) << "Assignments" << std::endl;

    for (size_t n : sizes) {
        for (const auto& type : types) {
            // Генерація масиву
            std::vector<int> arr = generateArray(n, type);

            // Статистика сортування
            SortStats stats;

            // Вимірювання часу сортування
            auto start = std::chrono::high_resolution_clock::now();
            quickSort(arr, 0, arr.size() - 1, stats);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;

            // Вивід результатів
            std::cout << std::setw(10) << n
                      << std::setw(15) << type
                      << std::setw(20) << duration.count()
                      << std::setw(20) << stats.comparisons
                      << std::setw(20) << stats.assignments << std::endl;
        }
    }

    return 0;
}
