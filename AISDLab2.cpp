#include <iostream>
#include <queue>
#include <cstdlib> 
#include <ctime>   


bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}


void printPrimesFromQueue(const std::queue<int>& q) {
    std::queue<int> temp = q; 
    std::cout << "Прості числа в черзі: ";
    while (!temp.empty()) {
        int value = temp.front();
        temp.pop();
        if (isPrime(value)) {
            std::cout << value << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
   
    int S = 7 * 5 + 50;

   
    std::queue<int> myQueue;
    std::srand(std::time(0));

    for (int i = 0; i < S; ++i) {
        myQueue.push(std::rand() % 1000 + 1);
    }

 
    printPrimesFromQueue(myQueue);

    return 0;
}
