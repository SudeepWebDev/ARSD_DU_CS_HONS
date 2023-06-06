# Write a Program to check if a given graph is a complete graph. 
# Represent the graph using the Adjacency Matrix representation.

# defining the is_complete_graph function with two parameters graph and num_vertices.
def is_complete_graph(graph, num_vertices):
    for i in range(num_vertices):
        # Check if each vertex is connected to all other vertices
        for j in range(num_vertices):
            if i != j and graph[i][j] != 1:
                return False
    return True

def main():
    graph = []
    num_vertices = int(input("Enter the no. of vertices present in graph: "))
    print()
    # taking input for graph in adjacency matrix form
    for i in range(num_vertices):
        rows = []
        for j in range(num_vertices):
            cell = int(input(f"Enter the value of {i,j}: "))
            rows.append(cell)
        graph.append(rows)

    print('\nAdjacency matrix representation:')
    print(f'{graph}\n')
    
    if(is_complete_graph(graph, num_vertices)):
        print('It is complete graph')
    else: 
        print('It is not complete graph')

if __name__ == "__main__":
    main()
