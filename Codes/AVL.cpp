#include <iostream>
#include <string>
using namespace std;

// Node structure for AVL Tree
struct LogNode {
    int key; // timestamp or version number
    string message;
    int height;
    LogNode* left;
    LogNode* right;

    LogNode(int k, const string& msg)
        : key(k), message(msg), height(1), left(nullptr), right(nullptr) {}
};

// Utility functions
int height(LogNode* node) {
    return node ? node->height : 0;
}

int getBalance(LogNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Right rotate
LogNode* rightRotate(LogNode* y) {
    LogNode* x = y->left;
    LogNode* T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Left rotate
LogNode* leftRotate(LogNode* x) {
    LogNode* y = x->right;
    LogNode* T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Insert a log entry
LogNode* insert(LogNode* node, int key, const string& message) {
    if (!node) return new LogNode(key, message);

    if (key < node->key)
        node->left = insert(node->left, key, message);
    else if (key > node->key)
        node->right = insert(node->right, key, message);
    else
        return node; // duplicate keys not allowed

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Balance the node
    int balance = getBalance(node);

    // 4 cases of unbalance

    // Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// In-order traversal to display logs in order
void displayLogs(LogNode* root) {
    if (!root) return;
    displayLogs(root->left);
    cout << "[Version " << root->key << "] " << root->message << endl;
    displayLogs(root->right);
}

// Clean up tree memory
void freeTree(LogNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Test the AVL Log System
int main() {
    LogNode* root = nullptr;

    root = insert(root, 3, "Synced product data with remote server.");
    root = insert(root, 1, "Initialized CRM sync module.");
    root = insert(root, 4, "Resolved sync conflicts.");
    root = insert(root, 2, "Fetched new leads from API.");

    cout << "=== Ordered Synchronization Logs ===\n";
    displayLogs(root);

    freeTree(root);
    return 0;
}
