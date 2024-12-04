#include <iostream>
#include <stack>
#include <cstdlib> 
#include <ctime>  


void printStack(std::stack<int> s, const std::string& stackName) {
    std::cout << stackName << ": ";
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

int main() {
    
    int variant = 7; 
    int S = variant * 5 + 50;


    std::stack<int> initialStack;
    std::srand(std::time(0)); 
    for (int i = 0; i < S; ++i) {
        initialStack.push(std::rand() % 1000 + 1);
    }

    std::stack<int> evenStack; 
    std::stack<int> oddStack;  

    while (!initialStack.empty()) {
        int value = initialStack.top();
        initialStack.pop();

        if (value % 2 == 0) {
            evenStack.push(value);
        } else {
            oddStack.push(value);
        }
    }

    printStack(evenStack, "Парний стек");
    printStack(oddStack, "Непарний стек");

    return 0;
}
