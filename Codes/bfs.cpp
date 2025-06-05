#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class PartnerGraph {
private:
    unordered_map<string, vector<string>> adj;

public:
    void addRelationship(const string& partner, const string& subPartner) {
        adj[partner].push_back(subPartner);
    }

    void bfs(const string& start) {
        set<string> visited;
        queue<string> q;

        q.push(start);
        visited.insert(start);

        cout << "Starting BFS from " << start << ":\n";

        while (!q.empty()) {
            string current = q.front();
            q.pop();
            cout << "Visiting (BFS): " << current << endl;

            for (const string& neighbor : adj[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }
};

int main() {
    PartnerGraph prm;

    prm.addRelationship("PartnerA", "PartnerB");
    prm.addRelationship("PartnerA", "PartnerC");
    prm.addRelationship("PartnerB", "PartnerD");
    prm.addRelationship("PartnerB", "PartnerE");
    prm.addRelationship("PartnerE", "PartnerG");
    prm.addRelationship("PartnerC", "PartnerF");

    prm.bfs("PartnerA");

    return 0;
}
