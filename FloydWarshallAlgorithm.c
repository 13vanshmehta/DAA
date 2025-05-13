#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 99999
#define MAX_VERTICES 100

void printSolution(int dist[][MAX_VERTICES], int V) {
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

void printPath(int path[][MAX_VERTICES], int i, int j) {
    if (path[i][j] == -1) {
        printf("%d -> %d", i, j);
        return;
    }
    printPath(path, i, path[i][j]);
    printf(" -> %d", j);
}

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

void floydWarshall(int graph[][MAX_VERTICES], int V) {
    int dist[MAX_VERTICES][MAX_VERTICES];
    int path[MAX_VERTICES][MAX_VERTICES];
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
            if (i == j || graph[i][j] == INF)
                path[i][j] = -1;
            else
                path[i][j] = i;
        }
    }
    
    // Initial distance matrix is the same as input graph in this case
    // so we don't need to display it separately
    
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    
    printf("\nFinal solution (All-Pairs Shortest Paths):\n");
    printSolution(dist, V);
    
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("\nWARNING: Negative weight cycle detected!\n");
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
    
    printf("\nInput Graph (Adjacency Matrix):\n");
    printSolution(graph, V);
    
    floydWarshall(graph, V);
    return 0;
}