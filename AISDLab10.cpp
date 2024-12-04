#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Структура для представлення вузлів дерева
struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

// Функція порівняння для пріоритетної черги
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;  // Менша частота має вищий пріоритет
    }
};

// Функція для побудови дерева Хаффмана
Node* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Створюємо вузли для кожного символу та додаємо їх у пріоритетну чергу
    for (const auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Будуємо дерево
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        // Створюємо новий вузол для об'єднаних символів
        Node* merged = new Node('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;

        pq.push(merged);  // Додаємо новий вузол назад у чергу
    }

    return pq.top();  // Повертаємо корінь дерева
}

// Рекурсивна функція для присвоєння бінарних кодів символам
void generateCodes(Node* root, const string& str, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    // Якщо вузол є листом, то зберігаємо його код
    if (!root->left && !root->right) {
        huffmanCodes[root->character] = str;
    }

    // Рекурсивно проходимо лівий і правий піддерева
    generateCodes(root->left, str + "0", huffmanCodes);
    generateCodes(root->right, str + "1", huffmanCodes);
}

// Функція для кодування тексту
string encodeText(const string& text, const unordered_map<char, string>& huffmanCodes) {
    string encoded = "";
    for (char ch : text) {
        encoded += huffmanCodes.at(ch);  // Додаємо бінарний код кожного символу
    }
    return encoded;
}

// Функція для декодування тексту
string decodeText(const string& encoded, Node* root) {
    string decoded = "";
    Node* current = root;
    for (char bit : encoded) {
        // Переміщаємося по дереву
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        // Якщо ми дійшли до листа, то додаємо символ у результат
        if (!current->left && !current->right) {
            decoded += current->character;
            current = root;  // Повертаємося до кореня
        }
    }
    return decoded;
}

int main() {
    string text = "Жужелиця жимолость жувала";  // Вхідний текст

    // Підрахунок частоти символів
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    // Будуємо дерево Хаффмана
    Node* root = buildHuffmanTree(freqMap);

    // Генеруємо коди для кожного символу
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    // Виведення бінарних кодів для символів
    cout << "Коди символів:\n";
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Кодуємо текст
    string encodedText = encodeText(text, huffmanCodes);
    cout << "\nЗакодований текст: " << encodedText << endl;

    // Декодуємо текст
    string decodedText = decodeText(encodedText, root);
    cout << "\nДекодований текст: " << decodedText << endl;

    return 0;
}
