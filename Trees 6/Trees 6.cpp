#include <iostream>
#include <algorithm>

// ��������� ��������� �������
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

    // ���������� �������� ��������� �� ������ � ������� �����������
    int leftMax = std::max(getMaxFromNode(node->left, maxPath), 0);
    int rightMax = std::max(getMaxFromNode(node->right, maxPath), 0);

    // ������������ ������� ������������ ���� ����� ������� �������
    int currentMaxPath = leftMax + node->value + rightMax;
    maxPath = std::max(maxPath, currentMaxPath);

    // ���������� ������������ ����, ������� ����� ���������� �����
    return node->value + std::max(leftMax, rightMax);
}

int solution(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int maxPath = root->value; // �������������� ��������� �����
    getMaxFromNode(root, maxPath);

    return maxPath;
}

int main() {

    // ������ ������ �1
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

    // ������� � �������
    std::cout << "Max path sum: " << solution(root) << std::endl;

    // ������ ������ �2
    Node* root2 = new Node(-5);
    root2->left = new Node(1);
    root2->right = new Node(7);
    root2->right->left = new Node(2);
    root2->right->right = new Node(3);

    // ������� � �������
    std::cout << "Max path sum: " << solution(root2) << std::endl;

    return 0;
}