#include <iostream>
#include <vector>
#include <limits>
#include <omp.h>

const int INF = std::numeric_limits<int>::max();

void parallelDijkstra(const std::vector<std::vector<int>>& graph, int src) {
    int n = graph.size();
    std::vector<int> dist(n, INF);
    std::vector<bool> visited(n, false);

    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;

        #pragma omp parallel for
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = true;

        #pragma omp parallel for
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print distances or validate the result
    for (int i = 0; i < n; i++) {
        std::cout << "Distance from " << src << " to " << i << " is " << dist[i] << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> graph = {
        {0, 10, 20, 0, 0},
        {10, 0, 0, 50, 10},
        {20, 0, 0, 20, 33},
        {0, 50, 20, 0, 2},
        {0, 10, 33, 2, 0}
    };

    parallelDijkstra(graph, 0);

    return 0;
}
