#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_VERTICES 100

int minDistance(int dist[], bool visited[], int V) {
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++) {
        if (visited[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printSolution(int dist[], int V, int src) {
    printf("Vertex \t Distance from Source (%d)\n", src);
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

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

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int V) {
    int *dist = (int *)malloc(V * sizeof(int));
    bool *visited = (bool *)malloc(V * sizeof(bool));
    int *parent = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && 
                dist[u] + graph[u][v] < dist[v]) {
                    parent[v] = u;
                    dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, V, src);
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

    printf("\nInput Graph (Adjacency Matrix):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }

    dijkstra(graph, source, V);
    
    return 0;
}