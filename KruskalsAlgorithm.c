#include <stdio.h>
#include <stdlib.h>

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

// Structure for subset for union-find
typedef struct {
    int parent;
    int rank;
} Subset;

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

// Function to find set of an element i (uses path compression technique)
int find(Subset subsets[], int i) {
    // Find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    
    return subsets[i].parent;
}

// Function that does union of two sets x and y (uses union by rank)
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    
    // Attach smaller rank tree under root of high rank tree
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        // If ranks are same, make one as root and increment its rank
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare function for qsort
int compareEdges(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight - b1->weight;
}

// Function to construct MST using Kruskal's algorithm
void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge* result = (Edge*)malloc((V-1) * sizeof(Edge));  // This will store the resultant MST
    if (result == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    int e = 0;       // Index variable for result[]
    int i = 0;       // Index variable for sorted edges
    
    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);
    
    // Allocate memory for creating V subsets
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    if (subsets == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    // Create V subsets with single elements
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    // Number of edges to be taken is V-1
    while (e < V - 1 && i < graph->E) {
        // Step 2: Pick the smallest edge. Increment index for next iteration
        Edge next_edge = graph->edge[i++];
        
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        
        // If including this edge doesn't cause cycle, include it in result
        // and increment the index of result for next edge
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the edge
    }
    
    // Print the constructed MST
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
    
    // Print the input graph
    printf("\nInput Graph:\n");
    printf("Edge \tWeight\n");
    for (int i = 0; i < E; i++) {
        printf("%d - %d \t%d\n", graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    }
    
    // Find MST using Kruskal's algorithm
    KruskalMST(graph);
    
    // Free allocated memory
    free(graph->edge);
    free(graph);
    
    return 0;
}