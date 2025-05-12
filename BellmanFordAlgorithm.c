#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent an edge in the graph
typedef struct {
    int src;    // Source vertex
    int dest;   // Destination vertex
    int weight; // Weight of the edge
} Edge;

// Structure to represent a graph
typedef struct {
    int V;      // Number of vertices
    int E;      // Number of edges
    Edge* edge; // Array of edges
} Graph;

// Function to create a graph with V vertices and E edges
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    graph->V = V;
    graph->E = E;
    
    graph->edge = (Edge*)malloc(E * sizeof(Edge));
    if (graph->edge == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    return graph;
}

// Function to print the solution
void printSolution(int dist[], int V, int src) {
    printf("\nVertex\tDistance from Source (%d)\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("%d\t\tINF\n", i);
        else
            printf("%d\t\t%d\n", i, dist[i]);
    }
}

// Function to print the path from source to a vertex
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Function to print all paths
void printAllPaths(int dist[], int parent[], int V, int src) {
    printf("\nShortest Paths from Source (%d):\n", src);
    for (int i = 0; i < V; i++) {
        if (i != src && dist[i] != INT_MAX) {
            printf("Path to %d (Distance: %d): %d", i, dist[i], src);
            printPath(parent, i);
            printf("\n");
        }
    }
}

// Function that implements Bellman-Ford algorithm
int bellmanFord(Graph* graph, int src, int dist[], int parent[]) {
    int V = graph->V;
    int E = graph->E;
    
    // Step 1: Initialize distances from src to all other vertices as INFINITE
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0; // Distance of source vertex from itself is always 0
    
    // Step 2: Relax all edges |V| - 1 times
    // A simple shortest path from src to any other vertex can have at most |V| - 1 edges
    for (int i = 1; i <= V - 1; i++) {
        printf("\nIteration %d:\n", i);
        
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                printf("Edge (%d -> %d) relaxed. New distance to %d: %d\n", u, v, v, dist[v]);
            }
        }
        
        // Print current distances
        printSolution(dist, V, src);
    }
    
    // Step 3: Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("\nGraph contains negative weight cycle\n");
            return 0; // Return false
        }
    }
    
    return 1; // Return true if no negative cycle
}

int main() {
    int V, E, src;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    
    printf("Enter the number of edges: ");
    scanf("%d", &E);
    
    Graph* graph = createGraph(V, E);
    
    printf("Enter the details of each edge (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }
    
    printf("Enter the source vertex: ");
    scanf("%d", &src);
    
    if (src < 0 || src >= V) {
        printf("Invalid source vertex!\n");
        return 1;
    }
    
    // Print the input graph
    printf("\nInput Graph:\n");
    printf("Edge\tWeight\n");
    for (int i = 0; i < E; i++) {
        printf("%d -> %d\t%d\n", graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    }
    
    // Arrays to store distance and parent information
    int* dist = (int*)malloc(V * sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));
    
    if (dist == NULL || parent == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    // Run Bellman-Ford algorithm
    printf("\nRunning Bellman-Ford Algorithm from source %d:\n", src);
    if (bellmanFord(graph, src, dist, parent)) {
        printf("\nFinal Solution - ");
        printSolution(dist, V, src);
        printAllPaths(dist, parent, V, src);
    }
    
    // Free allocated memory
    free(dist);
    free(parent);
    free(graph->edge);
    free(graph);
    
    return 0;
}