#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
using namespace std;

const int MAX_V = 100; // Max number of vertices

// Residual capacity matrix
int capacity[MAX_V][MAX_V];

// Visited array for DFS
bool visited[MAX_V];

// DFS function to find an augmenting path
int dfs(int u, int t, int flow, int V) {
    if (u == t)
        return flow;

    visited[u] = true;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && capacity[u][v] > 0) {
            int min_flow = min(flow, capacity[u][v]);
            int bottleneck = dfs(v, t, min_flow, V);

            if (bottleneck > 0) {
                capacity[u][v] -= bottleneck;
                capacity[v][u] += bottleneck;
                return bottleneck;
            }
        }
    }

    return 0;
}

// Ford-Fulkerson algorithm
int fordFulkerson(int source, int sink, int V) {
    int maxFlow = 0;

    while (true) {
        memset(visited, 0, sizeof(visited));
        int flow = dfs(source, sink, INT_MAX, V);

        if (flow == 0)
            break;

        maxFlow += flow;
    }

    return maxFlow;
}

int main() {
    int V = 6; // Number of vertices

    // Initialize capacity matrix with 0
    memset(capacity, 0, sizeof(capacity));

    // Add edges: capacity[u][v] = capacity of edge u → v
    capacity[0][1] = 16;
    capacity[0][2] = 13;
    capacity[1][2] = 10;
    capacity[1][3] = 12;
    capacity[2][1] = 4;
    capacity[2][4] = 14;
    capacity[3][2] = 9;
    capacity[3][5] = 20;
    capacity[4][3] = 7;
    capacity[4][5] = 4;

    int source = 0, sink = 5;
    int maxFlow = fordFulkerson(source, sink, V);

    cout << "Maximum possible flow: " << maxFlow << endl;

    return 0;
}
