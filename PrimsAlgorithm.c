#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100

int findMinKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    
    return min_index;
}

void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    int totalWeight = 0;
    printf("Edge\t\tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t\t%d\n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("Total MST Weight: %d\n", totalWeight);
}

void primsMST(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool mstSet[MAX_VERTICES];
    
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    
    key[0] = 0;
    parent[0] = -1;
    
    for (int count = 0; count < V - 1; count++) {
        int u = findMinKey(key, mstSet, V);
        mstSet[u] = true;
        
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    
    printMST(parent, graph, V);
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
    printf("(Enter 0 for no edge, positive weight for an edge)\n");
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] < 0) {
                printf("Negative weights are not allowed!\n");
                return 1;
            }
        }
    }
    
    printf("\nInput Graph (Adjacency Matrix):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMinimum Spanning Tree using Prim's Algorithm:\n");
    primsMST(graph, V);
    
    return 0;
}