#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

class PartnerGraph {
private:
    unordered_map<string, vector<string>> adj;

public:
    void addRelationship(const string& partner, const string& subPartner) {
        adj[partner].push_back(subPartner);
    }

    void dfsUtil(const string& partner, set<string>& visited) {
        visited.insert(partner);
        cout << "Visiting (DFS): " << partner << endl;

        for (const string& neighbor : adj[partner]) {
            if (visited.find(neighbor) == visited.end()) {
                dfsUtil(neighbor, visited);
            }
        }
    }

    void dfs(const string& start) {
        set<string> visited;
        cout << "Starting DFS from " << start << ":\n";
        dfsUtil(start, visited);
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

    prm.dfs("PartnerA");

    return 0;
}
