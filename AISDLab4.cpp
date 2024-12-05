#include <iostream>
#include <string>

struct TreeNode {
    std::string name;  
    std::string phone; 
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& name, const std::string& phone)
        : name(name), phone(phone), left(nullptr), right(nullptr) {}
};

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

TreeNode* findMin(TreeNode* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}


TreeNode* remove(TreeNode* root, const std::string& name) {
    if (!root) {
        return root;
    }
    if (name < root->name) {
        root->left = remove(root->left, name);
    } else if (name > root->name) {
        root->right = remove(root->right, name);
    } else {
      
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

void inOrder(TreeNode* root) {
    if (root) {
        inOrder(root->left);
        std::cout << "Фамілія: " << root->name << ", Телефон: " << root->phone << std::endl;
        inOrder(root->right);
    }
}

int main() {
    TreeNode* phoneBook = nullptr;

    phoneBook = insert(phoneBook, "Руденко", "99-479-09-82");
    phoneBook = insert(phoneBook, "Векліч", "99-234-56-27");
    phoneBook = insert(phoneBook, "Шелест", "50-345-67-38");
    phoneBook = insert(phoneBook, "Глумний", "79-274-19-53");
    phoneBook = insert(phoneBook, "Стадницький", "95-786-01-58");
    phoneBook = insert(phoneBook, "Григоренко", "66-300-00-12");

    std::cout << "Телефонний довідник після вставки елементів:" << std::endl;
    inOrder(phoneBook);

    std::string searchName = "Векліч";
    TreeNode* result = search(phoneBook, searchName);
    if (result) {
        std::cout << "\nЗнайдено: Фамілія: " << result->name << ", Телефон: " << result->phone << std::endl;
    } else {
        std::cout << "\nАбонента " << searchName << " не знайдено." << std::endl;
    }

    std::cout << "\nВидалення абонента Veklich...\n";
    phoneBook = remove(phoneBook, "Векліч");

    std::cout << "Телефонний довідник після видалення елемента:" << std::endl;
    inOrder(phoneBook);

    return 0;
}
