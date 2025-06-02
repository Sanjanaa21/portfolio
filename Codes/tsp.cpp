#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

using namespace std;

const int NUM_CITIES = 5;
const int NUM_ANTS = 10;
const int MAX_ITER = 100;
const double ALPHA = 1.0;       // pheromone importance
const double BETA = 5.0;        // distance importance
const double RHO = 0.5;         // evaporation rate
const double Q = 100.0;         // pheromone deposit factor

double dist[NUM_CITIES][NUM_CITIES];     // distance between cities
double pheromone[NUM_CITIES][NUM_CITIES]; // pheromone levels

vector<int> bestTour;
double bestTourLength = numeric_limits<double>::max();

// Euclidean distance between 2D points
double distance(pair<int, int> a, pair<int, int> b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

// Initialize distance and pheromone matrices
void initializeGraph(vector<pair<int, int>>& cities) {
    for (int i = 0; i < NUM_CITIES; ++i) {
        for (int j = 0; j < NUM_CITIES; ++j) {
            if (i != j)
                dist[i][j] = distance(cities[i], cities[j]);
            else
                dist[i][j] = 1e9; // big value to avoid self-loops

            pheromone[i][j] = 1.0;
        }
    }
}

// Choose next city based on probability
int selectNextCity(int current, vector<bool>& visited) {
    double sum = 0.0;
    vector<double> probs(NUM_CITIES, 0.0);

    for (int i = 0; i < NUM_CITIES; ++i) {
        if (!visited[i]) {
            probs[i] = pow(pheromone[current][i], ALPHA) * pow(1.0 / dist[current][i], BETA);
            sum += probs[i];
        }
    }

    double r = (double)rand() / RAND_MAX * sum;
    double cumulative = 0.0;
    for (int i = 0; i < NUM_CITIES; ++i) {
        if (!visited[i]) {
            cumulative += probs[i];
            if (cumulative >= r)
                return i;
        }
    }

    // Fallback
    for (int i = 0; i < NUM_CITIES; ++i) {
        if (!visited[i]) return i;
    }

    return -1; // should not reach
}

// Simulate ant colony for given iterations
void antColonyOptimization() {
    for (int iter = 0; iter < MAX_ITER; ++iter) {
        vector<vector<int>> allTours(NUM_ANTS);
        vector<double> tourLengths(NUM_ANTS, 0.0);

        // Each ant builds a tour
        for (int ant = 0; ant < NUM_ANTS; ++ant) {
            vector<bool> visited(NUM_CITIES, false);
            int start = rand() % NUM_CITIES;
            visited[start] = true;
            allTours[ant].push_back(start);

            int current = start;

            for (int step = 1; step < NUM_CITIES; ++step) {
                int next = selectNextCity(current, visited);
                allTours[ant].push_back(next);
                visited[next] = true;
                tourLengths[ant] += dist[current][next];
                current = next;
            }

            // return to start
            tourLengths[ant] += dist[current][start];
            allTours[ant].push_back(start);

            // Update best
            if (tourLengths[ant] < bestTourLength) {
                bestTourLength = tourLengths[ant];
                bestTour = allTours[ant];
            }
        }

        // Evaporate pheromones
        for (int i = 0; i < NUM_CITIES; ++i)
            for (int j = 0; j < NUM_CITIES; ++j)
                pheromone[i][j] *= (1 - RHO);

        // Deposit pheromones
        for (int ant = 0; ant < NUM_ANTS; ++ant) {
            for (int i = 0; i < NUM_CITIES; ++i) {
                int from = allTours[ant][i];
                int to = allTours[ant][i + 1];
                pheromone[from][to] += Q / tourLengths[ant];
                pheromone[to][from] += Q / tourLengths[ant];
            }
        }
    }
}

// Driver
int main() {
    srand(time(0));

    // Sample cities (x, y)
    vector<pair<int, int>> cities = {
        {0, 0}, {2, 3}, {5, 4}, {6, 1}, {3, 0}
    };

    initializeGraph(cities);
    antColonyOptimization();

    cout << "Best tour length: " << bestTourLength << endl;
    cout << "Best tour: ";
    for (int city : bestTour)
        cout << city << " ";
    cout << endl;

    return 0;
}
