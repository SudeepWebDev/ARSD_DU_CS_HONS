#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
	int src, dest, weight;
};

void printDistances(const vector<int>& dist, int V) {
	cout << "Vertex\tDistance from Source\n";
	for (int i = 0; i < V; ++i) {
		cout << i << "\t\t" << dist[i] << "\n";
	}
}

void bellmanFord(const vector<Edge>& edges, int V, int src) {
	vector<int> dist(V, INT_MAX);
	dist[src] = 0;

	for (int i = 1; i <= V - 1; ++i) {
		for (const auto& edge : edges) {
			int u = edge.src;
			int v = edge.dest;
			int weight = edge.weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
			}
		}
	}

	for (const auto& edge : edges) {
		int u = edge.src;
		int v = edge.dest;
		int weight = edge.weight;
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
			cout << "Graph contains negative weight cycle\n";
			return;
		}
	}
	printDistances(dist, V);
}

int main() {
	int V = 5; 
	int E = 5; 

	vector<Edge> edges = {
		{1, 3, 2}, {4, 3, -1}, {2, 4, 1},
		{1, 2, 1}, {0, 1, 5}
	};

	int src = 0; 
	bellmanFord(edges, V, src);
	return 0;
}
