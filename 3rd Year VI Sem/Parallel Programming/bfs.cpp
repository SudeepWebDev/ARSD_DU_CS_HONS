#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

void parallelBFS(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        #pragma omp parallel for
        for (int i = 0; i < graph[node].size(); i++) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                #pragma omp critical
                q.push(neighbor);
            }
        }
    }

    // Print visited nodes or validate the result
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i]) {
            std::cout << "Node " << i << " was visited." << std::endl;
        }
    }
}

int main() {
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 4},
        {1, 5},
        {1, 2, 5},
        {3, 4}
    };

    parallelBFS(graph, 0);

    return 0;
}
