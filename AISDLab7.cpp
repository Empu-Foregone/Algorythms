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

// Функція для створення купи
void heapify(std::vector<int>& arr, size_t n, size_t i, SortStats& stats) {
    size_t largest = i;        // Індекс найбільшого елемента
    size_t left = 2 * i + 1;   // Лівий дочірній елемент
    size_t right = 2 * i + 2;  // Правий дочірній елемент

    // Перевіряємо лівий дочірній елемент
    if (left < n) {
        stats.comparisons++;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    // Перевіряємо правий дочірній елемент
    if (right < n) {
        stats.comparisons++;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    // Якщо найбільший елемент не корінь
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        stats.assignments += 3; // Три присвоєння в swap
        heapify(arr, n, largest, stats); // Рекурсивний виклик
    }
}

// Алгоритм сортування купою
void heapSort(std::vector<int>& arr, SortStats& stats) {
    size_t n = arr.size();

    // Створення купи
    for (size_t i = n / 2 - 1; i < n; --i) {
        heapify(arr, n, i, stats);
    }

    // Витягуємо елементи з купи
    for (size_t i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        stats.assignments += 3; // Три присвоєння в swap
        heapify(arr, i, 0, stats);
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
            heapSort(arr, stats);
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
