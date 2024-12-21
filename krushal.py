class Graph:
    def __init__(self, vertices):
        self.vertices = vertices  # Number of vertices
        self.edges = []           # List to store edges (u, v, weight)
    
    def add_edge(self, u, v, weight):
        """Add an edge to the graph."""
        self.edges.append((weight, u, v))
    
    def find(self, parent, i):
        """Find the parent of a node using path compression."""
        if parent[i] == i:
            return i
        parent[i] = self.find(parent, parent[i])  # Path compression
        return parent[i]
    
    def union(self, parent, rank, x, y):
        """Perform union of two sets."""
        root_x = self.find(parent, x)
        root_y = self.find(parent, y)
        
        if rank[root_x] < rank[root_y]:
            parent[root_x] = root_y
        elif rank[root_x] > rank[root_y]:
            parent[root_y] = root_x
        else:
            parent[root_y] = root_x
            rank[root_x] += 1
    
    def kruskal_mst(self):
        """Find and return the Minimum Spanning Tree using Kruskal's algorithm."""
        # Step 1: Sort edges by weight
        self.edges.sort()
        
        # Initialize parent and rank arrays
        parent = []
        rank = []
        for node in range(self.vertices):
            parent.append(node)
            rank.append(0)
        
        mst = []  # List to store the MST
        mst_cost = 0  # Cost of the MST
        
        # Step 2: Add edges to MST while avoiding cycles
        for weight, u, v in self.edges:
            root_u = self.find(parent, u)
            root_v = self.find(parent, v)
            
            # Check if including this edge creates a cycle
            if root_u != root_v:
                mst.append((u, v, weight))
                mst_cost += weight
                self.union(parent, rank, root_u, root_v)
        
        return mst, mst_cost


# Example usage
if __name__ == "__main__":
    # Create a graph with 4 vertices
    g = Graph(4)
    
    # Add edges: (u, v, weight)
    g.add_edge(0, 1, 10)
    g.add_edge(0, 2, 6)
    g.add_edge(0, 3, 5)
    g.add_edge(1, 3, 15)
    g.add_edge(2, 3, 4)
    
    # Find and print the MST
    mst, mst_cost = g.kruskal_mst()
    print("Edges in the MST:")
    for u, v, weight in mst:
        print(f"({u}, {v}) - {weight}")
    print("Cost of the MST:", mst_cost)
