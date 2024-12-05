#include <iostream>
#include <vector>
#include <chrono> 
#include <iomanip> 
#include <cstdlib> 

struct SortStats {
    size_t comparisons = 0;   
    size_t assignments = 0;  
};
void merge(std::vector<int>& arr, size_t left, size_t mid, size_t right, SortStats& stats) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);

    for (size_t i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
        stats.assignments++;
    }
    for (size_t j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
        stats.assignments++;
    }

    size_t i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        stats.comparisons++; 
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
        stats.assignments++; 
    }

    while (i < n1) {
        arr[k++] = L[i++];
        stats.assignments++;
    }

    while (j < n2) {
        arr[k++] = R[j++];
        stats.assignments++;
    }
}

void mergeSort(std::vector<int>& arr, size_t left, size_t right, SortStats& stats) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, stats);
        mergeSort(arr, mid + 1, right, stats);

        merge(arr, left, mid, right, stats);
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
            mergeSort(arr, 0, arr.size() - 1, stats);
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
