#include <iostream>
#include <string>

// Структура вузла бінарного дерева
struct TreeNode {
    std::string name;  // Ім'я абонента
    std::string phone; // Номер телефону
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& name, const std::string& phone)
        : name(name), phone(phone), left(nullptr), right(nullptr) {}
};

// Функція для вставки елемента в дерево
TreeNode* insert(TreeNode* root, const std::string& name, const std::string& phone) {
    if (!root) {
        return new TreeNode(name, phone);
    }
    if (name < root->name) {
        root->left = insert(root->left, name, phone);
    } else if (name > root->name) {
        root->right = insert(root->right, name, phone);
    }
    return root;
}

// Функція для пошуку елемента в дереві
TreeNode* search(TreeNode* root, const std::string& name) {
    if (!root || root->name == name) {
        return root;
    }
    if (name < root->name) {
        return search(root->left, name);
    } else {
        return search(root->right, name);
    }
}

// Функція для знаходження найменшого вузла (потрібно для видалення)
TreeNode* findMin(TreeNode* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

// Функція для видалення елемента з дерева
TreeNode* remove(TreeNode* root, const std::string& name) {
    if (!root) {
        return root;
    }
    if (name < root->name) {
        root->left = remove(root->left, name);
    } else if (name > root->name) {
        root->right = remove(root->right, name);
    } else {
        // Вузол знайдено
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        TreeNode* temp = findMin(root->right);
        root->name = temp->name;
        root->phone = temp->phone;
        root->right = remove(root->right, temp->name);
    }
    return root;
}

// Функція для виводу дерева у симетричному порядку
void inOrder(TreeNode* root) {
    if (root) {
        inOrder(root->left);
        std::cout << "Фамілія: " << root->name << ", Телефон: " << root->phone << std::endl;
        inOrder(root->right);
    }
}

int main() {
    TreeNode* phoneBook = nullptr;

    // Додавання елементів
    phoneBook = insert(phoneBook, "Руденко", "99-479-09-82");
    phoneBook = insert(phoneBook, "Векліч", "99-234-56-27");
    phoneBook = insert(phoneBook, "Шелест", "50-345-67-38");
    phoneBook = insert(phoneBook, "Глумний", "79-274-19-53");
    phoneBook = insert(phoneBook, "Стадницький", "95-786-01-58");
    phoneBook = insert(phoneBook, "Григоренко", "66-300-00-12");

    std::cout << "Телефонний довідник після вставки елементів:" << std::endl;
    inOrder(phoneBook);

    // Пошук елемента
    std::string searchName = "Векліч";
    TreeNode* result = search(phoneBook, searchName);
    if (result) {
        std::cout << "\nЗнайдено: Фамілія: " << result->name << ", Телефон: " << result->phone << std::endl;
    } else {
        std::cout << "\nАбонента " << searchName << " не знайдено." << std::endl;
    }

    // Видалення елемента
    std::cout << "\nВидалення абонента Veklich...\n";
    phoneBook = remove(phoneBook, "Векліч");

    std::cout << "Телефонний довідник після видалення елемента:" << std::endl;
    inOrder(phoneBook);

    return 0;
}
