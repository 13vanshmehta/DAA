#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 99999
#define MAX_VERTICES 100

// Function to print the solution matrix
void printSolution(int dist[][MAX_VERTICES], int V) {
    printf("\nShortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to print the path from vertex i to j
void printPath(int path[][MAX_VERTICES], int i, int j) {
    if (path[i][j] == -1) {
        printf("%d -> %d", i, j);
        return;
    }
    
    printPath(path, i, path[i][j]);
    printf(" -> %d", j);
}

// Function to print all paths
void printAllPaths(int path[][MAX_VERTICES], int dist[][MAX_VERTICES], int V) {
    printf("\nAll shortest paths:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j && dist[i][j] != INF) {
                printf("Path from %d to %d (distance: %d): ", i, j, dist[i][j]);
                printPath(path, i, j);
                printf("\n");
            }
        }
    }
}

// Floyd Warshall Algorithm
void floydWarshall(int graph[][MAX_VERTICES], int V) {
    int dist[MAX_VERTICES][MAX_VERTICES]; // Output matrix
    int path[MAX_VERTICES][MAX_VERTICES]; // To store the path
    
    // Initialize dist and path matrices
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
            
            if (i == j || graph[i][j] == INF)
                path[i][j] = -1;
            else
                path[i][j] = i; // Initialize path
        }
    }
    
    // Print initial distance matrix
    printf("Initial distance matrix:\n");
    printSolution(dist, V);
    
    // Core of the algorithm
    // Consider each vertex as an intermediate vertex
    for (int k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++) {
            // Pick all vertices as destination
            for (int j = 0; j < V; j++) {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j]; // Update path
                }
            }
        }
        
        // Print distance matrix after considering vertex k as intermediate
        printf("\nDistance matrix after considering vertex %d as intermediate:\n", k);
        printSolution(dist, V);
    }
    
    // Print the final solution
    printf("\nFinal solution - ");
    printSolution(dist, V);
    
    // Print all paths
    printAllPaths(path, dist, V);
    
    // Check for negative weight cycles
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("\nWARNING: The graph contains a negative weight cycle!\n");
            break;
        }
    }
}

int main() {
    int V;
    int graph[MAX_VERTICES][MAX_VERTICES];
    
    printf("Enter the number of vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &V);
    
    if (V <= 0 || V > MAX_VERTICES) {
        printf("Invalid number of vertices!\n");
        return 1;
    }
    
    printf("Enter the adjacency matrix (%d x %d):\n", V, V);
    printf("(Enter %d for infinity/no direct path)\n", INF);
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == INF)
                graph[i][j] = INF;
        }
    }
    
    // Print the input graph
    printf("\nInput Graph (Adjacency Matrix):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
    
    // Apply Floyd Warshall Algorithm
    floydWarshall(graph, V);
    
    return 0;
}