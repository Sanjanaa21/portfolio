#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int sum;
    Node* left;
    Node* right;

    Node(int val = 0) : sum(val), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : left(l), right(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

class PersistentSegmentTree {
    int n;
    vector<Node*> versions;

public:
    PersistentSegmentTree(const vector<int>& data) {
        n = data.size();
        Node* root = build(data, 0, n - 1);
        versions.push_back(root);
    }

    // Build the initial tree
    Node* build(const vector<int>& data, int l, int r) {
        if (l == r)
            return new Node(data[l]);

        int m = (l + r) / 2;
        return new Node(build(data, l, m), build(data, m + 1, r));
    }

    // Update: returns root of new version
    Node* update(Node* node, int l, int r, int idx, int val) {
        if (l == r)
            return new Node(val);

        int m = (l + r) / 2;
        if (idx <= m)
            return new Node(update(node->left, l, m, idx, val), node->right);
        else
            return new Node(node->left, update(node->right, m + 1, r, idx, val));
    }

    // Public update method
    void createNewVersion(int idx, int val) {
        Node* newRoot = update(versions.back(), 0, n - 1, idx, val);
        versions.push_back(newRoot);
    }

    // Query sum in range [l, r] for a given version
    int query(Node* node, int l, int r, int ql, int qr) {
        if (!node || r < ql || l > qr) return 0;
        if (ql <= l && r <= qr) return node->sum;

        int m = (l + r) / 2;
        return query(node->left, l, m, ql, qr) +
               query(node->right, m + 1, r, ql, qr);
    }

    // Public query method
    int queryVersion(int version, int ql, int qr) {
        if (version >= versions.size()) {
            cout << "Invalid version\n";
            return -1;
        }
        return query(versions[version], 0, n - 1, ql, qr);
    }
};
int main() {
    vector<int> sales = {10, 20, 30, 40, 50}; // Initial sales data
    PersistentSegmentTree pst(sales);

    pst.createNewVersion(2, 100); // Version 1: update index 2 → 100
    pst.createNewVersion(0, 200); // Version 2: update index 0 → 200

    cout << "Sum in version 0 [0, 4]: " << pst.queryVersion(0, 0, 4) << endl; // 150
    cout << "Sum in version 1 [0, 4]: " << pst.queryVersion(1, 0, 4) << endl; // 220
    cout << "Sum in version 2 [0, 2]: " << pst.queryVersion(2, 0, 2) << endl; // 200 + 20 + 100 = 320

    return 0;
}
