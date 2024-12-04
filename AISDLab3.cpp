#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>   

int main() {
    int N = 7 * 5 + 50; 
    int S = static_cast<int>(N * 0.75); 
 
    std::unordered_map<int, int> hashTable;

  
    std::srand(std::time(0));

   
    for (int i = 0; i < N; ++i) {
        int key = i + 1;                 
        int value = std::rand() % 1000 + 1;  
        hashTable[key] = value;         
    }

     
    for (auto it = hashTable.begin(); it != hashTable.end();) {
        if (it->second % 2 == 0) {
            it = hashTable.erase(it); 
        } else {
            ++it; 
        }
    }

    std::cout << "Елементи, що залишилися в хеш-таблиці:" << std::endl;
    for (const auto& [key, value] : hashTable) {
        std::cout << "Ключ: " << key << ", Значення: " << value << std::endl;
    }

    return 0;
}
