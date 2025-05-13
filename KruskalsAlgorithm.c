#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

typedef struct {
    int V;
    int E;
    Edge* edge;
} Graph;

typedef struct {
    int parent;
    int rank;
} Subset;

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

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight - b1->weight;
}

void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge* result = (Edge*)malloc((V-1) * sizeof(Edge));
    if (result == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    int e = 0;
    int i = 0;
    
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);
    
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    if (subsets == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edge[i++];
        
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    
    printf("\nEdges in the Minimum Spanning Tree:\n");
    printf("Edge \tWeight\n");
    int totalWeight = 0;
    for (i = 0; i < e; i++) {
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total Weight of MST: %d\n", totalWeight);
    
    free(subsets);
}

int main() {
    int V, E;
    
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
    
    printf("\nInput Graph:\n");
    printf("Edge \tWeight\n");
    for (int i = 0; i < E; i++) {
        printf("%d - %d \t%d\n", graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    }
    
    KruskalMST(graph);
    
    free(graph->edge);
    free(graph);
    
    return 0;
}