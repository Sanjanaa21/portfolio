
#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;

#define V 7 // Total nodes: Source, 3 channels, 2 customers, Sink

// Breadth-First Search to find augmenting path
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

// Ford-Fulkerson algorithm
int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;

    // Create residual graph
    int rGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V]; // To store path
    int max_flow = 0; // Result

    // Augment flow while path from source to sink exists
    while (bfs(rGraph, s, t, parent)) {
        // Find min capacity in path
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Update residual capacities
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    // Graph as capacity matrix
    int graph[V][V] = { {0, 10, 5, 15, 0, 0, 0},  // Source to channels
                        {0, 0, 0, 0, 6, 4, 0},    // Email to customers
                        {0, 0, 0, 0, 5, 0, 0},    // SMS to customer A
                        {0, 0, 0, 0, 5, 10, 0},   // Social to customers
                        {0, 0, 0, 0, 0, 0, 10},   // Customer A to sink
                        {0, 0, 0, 0, 0, 0, 5},    // Customer B to sink
                        {0, 0, 0, 0, 0, 0, 0} };  // Sink

    int source = 0, sink = 6;

    cout << "Maximum number of campaign messages delivered: "
         << fordFulkerson(graph, source, sink) << endl;

    return 0;
}
