#include <iostream>
#include <vector>
#include <chrono> 
#include <iomanip>
#include <cstdlib> 
#include <algorithm> 

struct SortStats {
    size_t comparisons = 0;   
    size_t assignments = 0;  
};

void insertionSort(std::vector<int>& arr, SortStats& stats) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        size_t j = i;

        stats.assignments++; 
        while (j > 0 && arr[j - 1] > key) {
            stats.comparisons++; 
            arr[j] = arr[j - 1];
            stats.assignments++; 
            --j;
        }

        if (j > 0) stats.comparisons++; 
        arr[j] = key;
        stats.assignments++;
    }
}

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
  
            std::vector<int> arr = generateArray(n, type);

            SortStats stats;

            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(arr, stats);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;

            std::cout << std::setw(10) << n
                      << std::setw(15) << type
                      << std::setw(20) << duration.count()
                      << std::setw(20) << stats.comparisons
                      << std::setw(20) << stats.assignments << std::endl;
        }
    }

    return 0;
}
