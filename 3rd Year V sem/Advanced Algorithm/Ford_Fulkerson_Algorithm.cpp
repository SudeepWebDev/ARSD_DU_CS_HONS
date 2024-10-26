#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

class Graph {
    int V; 
    vector<vector<pair<int, int>>> adj; 

public:
    Graph(int V) : V(V), adj(V) {}
    
    void addEdge(int u, int v, int capacity) {
        adj[u].push_back({v, capacity});
        adj[v].push_back({u, 0}); 
    }

    bool bfs(int source, int sink, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1); 
        parent[source] = -2; 
        queue<pair<int, int>> q; 
        q.push({source, INT_MAX});

        while (!q.empty()) {
            int u = q.front().first;
            int flow = q.front().second;
            q.pop();

            
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int capacity = edge.second;

                if (parent[v] == -1 && capacity > 0) { 
                    parent[v] = u;
                    int new_flow = min(flow, capacity); 

                    if (v == sink) 
                        return true;

                    q.push({v, new_flow});
                }
            }
        }
        return false;
    }

    
    int fordFulkerson(int source, int sink) {
        int maxFlow = 0;
        vector<int> parent(V);

        
        while (bfs(source, sink, parent)) {
            int flow = INT_MAX;
            int v = sink;

            
            while (v != source) {
                int u = parent[v];
                for (auto& edge : adj[u]) {
                    if (edge.first == v) {
                        flow = min(flow, edge.second);
                        break;
                    }
                }
                v = u;
            }
            
            v = sink;
            while (v != source) {
                int u = parent[v];

                for (auto& edge : adj[u]) {
                    if (edge.first == v) {
                        edge.second -= flow;
                        break;
                    }
                }

                for (auto& edge : adj[v]) {
                    if (edge.first == u) {
                        edge.second += flow;
                        break;
                    }
                }
                v = u;
            }

            maxFlow += flow; 
        }
        return maxFlow;
    }
};

int main() {
    int V = 6;
    Graph g(V);

    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(2, 1, 4);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);

    cout << "The maximum possible flow is " << g.fordFulkerson(0, 5) << endl;

    return 0;
}
