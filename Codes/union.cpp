#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Initially, each node is its own parent
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int xr = find(x);
        int yr = find(y);

        if (xr == yr) return false; // Already in same set

        // Union by rank
        if (rank[xr] < rank[yr]) {
            parent[xr] = yr;
        } else if (rank[xr] > rank[yr]) {
            parent[yr] = xr;
        } else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }

    int countGroups() {
        int count = 0;
        for (int i = 0; i < parent.size(); i++)
            if (parent[i] == i)
                count++;
        return count;
    }
};

int main() {
    // Example: 6 companies
    vector<string> companies = {"A", "B", "C", "D", "E", "F"};
    unordered_map<string, int> nameToId;
    for (int i = 0; i < companies.size(); ++i)
        nameToId[companies[i]] = i;

    UnionFind uf(companies.size());

    // Simulated M&A mergers: each pair represents a merge
    vector<pair<string, string>> mergers = {
        {"A", "B"},
        {"C", "D"},
        {"B", "C"},  // A-B-C-D now connected
        {"E", "F"},
        {"A", "D"},  // Already connected, ignored
    };

    cout << "Processing Mergers:\n";
    for (auto &merge : mergers) {
        string u = merge.first;
        string v = merge.second;
        bool merged = uf.unite(nameToId[u], nameToId[v]);
        cout << u << " + " << v << " => " << (merged ? "Merged" : "Already Connected") << endl;
    }

    cout << "\nTotal independent systems after mergers: " << uf.countGroups() << endl;

    return 0;
}
