#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Number of vertices in the graph
#define MAX_VERTICES 100

// Function to find the vertex with minimum distance value
// from the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[], int V) {
    // Initialize min value
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int V, int src) {
    printf("Vertex \t Distance from Source (%d)\n", src);
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Function to print the path from source to a specific vertex
void printPath(int parent[], int j) {
    // Base Case: If j is source
    if (parent[j] == -1)
        return;
    
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Function to print the shortest path from source to all vertices
void printAllPaths(int dist[], int parent[], int V, int src) {
    printf("\nShortest Paths from Source (%d):\n", src);
    for (int i = 0; i < V; i++) {
        if (i != src) {
            printf("Path to %d (Distance: %d): %d", i, dist[i], src);
            printPath(parent, i);
            printf("\n");
        }
    }
}

// Function that implements Dijkstra's algorithm for a graph represented
// using adjacency matrix representation
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int V) {
    // The output array dist[i] holds the shortest distance from src to i
    int *dist = (int *)malloc(V * sizeof(int));
    
    // sptSet[i] will be true if vertex i is included in shortest path tree
    // or shortest distance from src to i is finalized
    bool *sptSet = (bool *)malloc(V * sizeof(bool));
    
    // Parent array to store shortest path tree
    int *parent = (int *)malloc(V * sizeof(int));
    
    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }
    
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
    
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, V);
        
        // Mark the picked vertex as processed
        sptSet[u] = true;
        
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {
            // Update dist[v] only if:
            // 1. There is an edge from u to v
            // 2. Vertex v is not in sptSet
            // 3. Distance through u is smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && 
                dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    
    // Print the constructed distance array
    printSolution(dist, V, src);
    
    // Print all shortest paths
    printAllPaths(dist, parent, V, src);
}

int main() {
    int V;
    int graph[MAX_VERTICES][MAX_VERTICES];
    int source;
    
    printf("Enter the number of vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &V);
    
    if (V <= 0 || V > MAX_VERTICES) {
        printf("Invalid number of vertices!\n");
        return 1;
    }
    
    printf("Enter the adjacency matrix (%d x %d):\n", V, V);
    printf("(Enter 0 for no edge, positive weight for an edge)\n");
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
            
            // Ensure non-negative weights
            if (graph[i][j] < 0) {
                printf("Dijkstra's algorithm doesn't work with negative weights!\n");
                return 1;
            }
        }
    }
    
    printf("Enter the source vertex (0 to %d): ", V - 1);
    scanf("%d", &source);
    
    if (source < 0 || source >= V) {
        printf("Invalid source vertex!\n");
        return 1;
    }
    
    // Print the input graph
    printf("\nInput Graph (Adjacency Matrix):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
    
    // Find and print the shortest paths
    dijkstra(graph, source, V);
    
    return 0;
}