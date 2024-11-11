#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) : V(V), E(E) {}

    void addEdge(int src, int dest, int weight) {
        edges.push_back(Edge(src, dest, weight));
    }

    int findParent(vector<int>& parent, int i) {
        if (parent[i] == i)
            return i;
        return findParent(parent, parent[i]);
    }

    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int xroot = findParent(parent, x);
        int yroot = findParent(parent, y);

        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    void kruskalMST() {
        vector<Edge> result;
        int e = 0;
        int i = 0;

        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

        vector<int> parent(V);
        vector<int> rank(V, 0);

        for (int v = 0; v < V; ++v)
            parent[v] = v;

        while (e < V - 1 && i < E) {
            Edge next_edge = edges[i++];

            int x = findParent(parent, next_edge.src);
            int y = findParent(parent, next_edge.dest);

            if (x != y) {
                result.push_back(next_edge);
                unionSets(parent, rank, x, y);
                e++;
            }
        }

        cout << "Edges in the Minimum Spanning Tree:\n";
        for (auto& edge : result)
            cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }
};

int main() {
    int V = 4;
    int E = 5;
    Graph g(V, E);

    g.addEdge(0, 1, 10); 
    g.addEdge(1, 3, 15); 
    g.addEdge(2, 3, 4); 
    g.addEdge(2, 0, 6); 
    g.addEdge(0, 3, 5); 

    g.kruskalMST();

    return 0;
}
