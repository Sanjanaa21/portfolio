#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

struct TreapNode {
    int key;        // Product ID
    int stock;      // Stock quantity
    int priority;   // Random priority for heap property
    TreapNode* left;
    TreapNode* right;

    TreapNode(int k, int s) : key(k), stock(s), priority(rand()), left(nullptr), right(nullptr) {}
};

class Treap {
private:
    TreapNode* root;

    TreapNode* rotateRight(TreapNode* y) {
        TreapNode* x = y->left;
        TreapNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        return x;
    }

    TreapNode* rotateLeft(TreapNode* x) {
        TreapNode* y = x->right;
        TreapNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        return y;
    }

    TreapNode* insert(TreapNode* node, int key, int stock) {
        if (!node)
            return new TreapNode(key, stock);

        if (key < node->key) {
            node->left = insert(node->left, key, stock);
            if (node->left->priority > node->priority)
                node = rotateRight(node);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, stock);
            if (node->right->priority > node->priority)
                node = rotateLeft(node);
        }
        else {
            // Key exists, update stock
            node->stock = stock;
        }
        return node;
    }

    TreapNode* search(TreapNode* node, int key) {
        if (!node || node->key == key)
            return node;

        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    void inorder(TreapNode* node, vector<pair<int,int>>& result) {
        if (!node) return;
        inorder(node->left, result);
        result.push_back({node->key, node->stock});
        inorder(node->right, result);
    }

    void freeTreap(TreapNode* node) {
        if (!node) return;
        freeTreap(node->left);
        freeTreap(node->right);
        delete node;
    }

public:
    Treap() : root(nullptr) {
        srand(time(nullptr));  // Seed for random priority
    }

    ~Treap() {
        freeTreap(root);
    }

    void addOrUpdateProduct(int productID, int stock) {
        root = insert(root, productID, stock);
    }

    int getStock(int productID) {
        TreapNode* node = search(root, productID);
        if (node)
            return node->stock;
        return -1;  // Product not found
    }

    vector<pair<int,int>> getAllProductsSorted() {
        vector<pair<int,int>> result;
        inorder(root, result);
        return result;
    }
};

int main() {
    Treap inventory;

    // Insert products
    inventory.addOrUpdateProduct(101, 50);
    inventory.addOrUpdateProduct(205, 30);
    inventory.addOrUpdateProduct(150, 20);

    // Update stock
    inventory.addOrUpdateProduct(205, 40);

    // Get stock for a product
    cout << "Stock for product 205: " << inventory.getStock(205) << endl;

    // Print all products sorted by product ID
    cout << "All inventory products sorted:" << endl;
    for (auto& p : inventory.getAllProductsSorted()) {
        cout << "Product ID: " << p.first << ", Stock: " << p.second << endl;
    }

    return 0;
}
