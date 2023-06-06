# Write a Program to check if a given graph is a complete graph. 
# Represent the graph using the Adjacency List representation.

# defining the is_complete_graph function with two parameters graph and num_vertices.
def is_complete_graph(graph, num_vertices):
    # Check if every pair of vertices is connected
    for i in range(num_vertices):
        for j in range(num_vertices):
            if i != j and j not in graph[i]:
                return False
    return True

def main():
    # initailsing graph dict where keys will be vertices and values will be neighbors
    graph = {}
    num_vertices = int(input("Enter the number of vertices in the graph: "))

    # Taking input for the graph in adjacency list form
    print('\nNote: Here whole numbers are used to represent vertices\n')
    print("Enter the graph in adjacency list")
    for i in range(num_vertices):
        vertex = input(f"Enter the vertices connected to vertex {i}, separated by commas: ")
        vertices = [int(v) for v in vertex.split(",")]
        graph[i] = vertices

    print("\nAdjacency list representation:")
    for vertex, neighbors in graph.items():
        print(f"{vertex}: {neighbors}")

    if is_complete_graph(graph, num_vertices):
        print("The graph is a complete graph.")
    else:
        print("The graph is not a complete graph.")

if __name__ == "__main__":
    main()
