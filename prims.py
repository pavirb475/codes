import sys

def prims_algorithm(graph, n):
    # Initialize MST set
    selected = [False] * n
    selected[0] = True  # Starting with the first vertex
    edges_count = 0
    total_cost = 0
    
    # Store the result
    mst_edges = []
    
    while edges_count < n - 1:
        min_weight = sys.maxsize
        x, y = 0, 0
        
        # Find the minimum edge that connects the tree to another vertex
        for u in range(n):
            if selected[u]:
                for v in range(n):
                    if not selected[v] and graph[u][v] and graph[u][v] < min_weight:
                        min_weight = graph[u][v]
                        x, y = u, v
        
        # Add this edge to the MST
        selected[y] = True
        mst_edges.append((x, y, min_weight))
        total_cost += min_weight
        edges_count += 1
    
    return mst_edges, total_cost

# Example graph as an adjacency matrix
# graph[i][j] holds the weight of the edge between i and j
graph = [
    [0, 10, 6, 5],
    [10, 0, 15, 0],
    [6, 15, 0, 4],
    [5, 0, 4, 0]
]

n = 4  # Number of vertices

mst_edges, total_cost = prims_algorithm(graph, n)

print("Edges in MST:", mst_edges)
print("Total cost of MST:", total_cost)