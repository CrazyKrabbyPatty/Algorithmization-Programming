#include <iostream>
#include <algorithm>

// Объявляем структуру вершины
struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val, Node* l = nullptr, Node* r = nullptr)
        : value(val), left(l), right(r) {}
};

int getMaxFromNode(Node* node, int& maxPath) {
    if (node == nullptr) {
        return 0;
    }

    // Рекурсивно получаем максимумы из левого и правого поддеревьев
    int leftMax = std::max(getMaxFromNode(node->left, maxPath), 0);
    int rightMax = std::max(getMaxFromNode(node->right, maxPath), 0);

    // Рассчитываем текущий максимальный путь через текущую вершину
    int currentMaxPath = leftMax + node->value + rightMax;
    maxPath = std::max(maxPath, currentMaxPath);

    // Возвращаем максимальный путь, который можно продолжить вверх
    return node->value + std::max(leftMax, rightMax);
}

int solution(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int maxPath = root->value; // Инициализируем значением корня
    getMaxFromNode(root, maxPath);

    return maxPath;
}

int main() {

    // Создаём дерево №1
    Node* root = new Node(-1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(7);
    root->left->right = new Node(3);
    root->left->left->left = new Node(-1);
    root->left->right->right = new Node(-6);
    root->left->right->left = new Node(9);
    root->right->right = new Node(0);
    root->right->right->left = new Node(4);

    // Считаем и выводим
    std::cout << "Max path sum: " << solution(root) << std::endl;

    // Создаём дерево №2
    Node* root2 = new Node(-5);
    root2->left = new Node(1);
    root2->right = new Node(7);
    root2->right->left = new Node(2);
    root2->right->right = new Node(3);

    // Считаем и выводим
    std::cout << "Max path sum: " << solution(root2) << std::endl;

    return 0;
}