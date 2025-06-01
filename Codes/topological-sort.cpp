#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to perform Topological Sort (Kahn's Algorithm)
// V: number of tasks
// adj: adjacency list representing dependencies (u -> v means u must be done before v)
bool topologicalSort(int V, vector<vector<int>>& adj, vector<int>& result) {
    vector<int> inDegree(V, 0);

    // Calculate in-degree (number of dependencies) for each task
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            inDegree[v]++;
        }
    }

    queue<int> q;
    // Enqueue tasks with no dependencies (in-degree 0)
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    int count = 0; // Count of tasks processed
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);
        count++;

        // For each task dependent on u, reduce in-degree and enqueue if it becomes zero
        for (int v : adj[u]) {
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // If count != V, there is a cycle in the graph (circular dependency)
    return (count == V);
}

int main() {
    int V, E;
    cout << "Enter number of tasks (vertices): ";
    cin >> V;
    cout << "Enter number of dependencies (edges): ";
    cin >> E;

    vector<vector<int>> adj(V);

    cout << "Enter dependencies in format 'A B' meaning 'A must be done before B':\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<int> topoOrder;
    bool isPossible = topologicalSort(V, adj, topoOrder);

    if (!isPossible) {
        cout << "Error: Workflow has cyclic dependencies! Cannot perform automation.\n";
    } else {
        cout << "Valid workflow execution order:\n";
        for (int task : topoOrder) {
            cout << "Task " << task << "\n";
        }
    }

    return 0;
}
