#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF 100  // Represent infinity (no direct path)

void printDistanceTable(const vector<vector<int>>& dist, int nodes) {
    cout << "\nDistance Table:\n";
    for (int i = 0; i < nodes; ++i) {
        cout << "Node " << i << ": ";
        for (int j = 0; j < nodes; ++j) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

void bellmanFord(int nodes, vector<vector<int>>& cost) {
    vector<vector<int>> dist(nodes, vector<int>(nodes, INF));  // Distance vector

    // Initialize the distance matrix for direct paths
    for (int i = 0; i < nodes; ++i) {
        for (int j = 0; j < nodes; ++j) {
            if (cost[i][j] != INF && i != j) {
                dist[i][j] = cost[i][j];
            }
        }
    }

    // Bellman-Ford algorithm (Relaxation)
    for (int k = 0; k < nodes - 1; ++k) {
        for (int i = 0; i < nodes; ++i) {
            for (int j = 0; j < nodes; ++j) {
                for (int l = 0; l < nodes; ++l) {
                    if (dist[i][j] > dist[i][l] + dist[l][j]) {
                        dist[i][j] = dist[i][l] + dist[l][j];
                    }
                }
            }
        }
    }

    // Printing the final Distance Table
    printDistanceTable(dist, nodes);
}

int main() {
    int nodes;

    // Input the number of nodes
    cout << "Enter the number of nodes: ";
    cin >> nodes;

    // Input the cost matrix (100 represents infinity, i.e., no direct path)
    vector<vector<int>> cost(nodes, vector<int>(nodes));
    cout << "Enter the cost matrix (Enter 100 for INF):\n";
    for (int i = 0; i < nodes; ++i) {
        for (int j = 0; j < nodes; ++j) {
            cin >> cost[i][j];
        }
    }

    // Run Bellman-Ford algorithm for distance vector routing
    bellmanFord(nodes, cost);

    return 0;
}
