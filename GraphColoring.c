#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 20

// Global variables
int n;              // Number of vertices
int m;              // Number of colors
int **graph;        // Adjacency matrix
int *color;         // Solution vector (colors assigned to vertices)
int colorCount = 0; // Count of solutions found

// Function to check if the color assignment is safe
bool isSafe(int v, int c) {
    // Check if any adjacent vertex has the same color
    for (int i = 0; i < n; i++) {
        if (graph[v][i] && color[i] == c) {
            return false;
        }
    }
    return true;
}

// Function to print the solution
void printSolution() {
    printf("\nSolution %d:\n", ++colorCount);
    printf("Vertex \tColor\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t%d\n", i + 1, color[i]);
    }
}

// Function to check if the current assignment is promising
bool promising(int v) {
    // Check if the current vertex can be assigned a color
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            return true;
        }
    }
    return false;
}

// Recursive function to solve graph coloring using Branch and Bound
bool graphColoringUtil(int v) {
    // If all vertices are assigned a color, we found a solution
    if (v == n) {
        printSolution();
        return true;
    }

    // Try different colors for vertex v
    bool foundSolution = false;
    for (int c = 1; c <= m; c++) {
        // Check if assignment of color c to v is valid
        if (isSafe(v, c)) {
            // Assign color c to vertex v
            color[v] = c;

            // Recur to assign colors to the rest of the vertices
            if (graphColoringUtil(v + 1)) {
                foundSolution = true;
                // Don't return true here to find all solutions
            }

            // Backtrack: Remove color c from vertex v
            color[v] = 0;
        }
    }

    return foundSolution;
}

// Function to solve the Graph Coloring problem
void graphColoring() {
    // Initialize all vertices with no color (0)
    for (int i = 0; i < n; i++) {
        color[i] = 0;
    }

    // Start with the first vertex
    if (!graphColoringUtil(0)) {
        printf("\nNo solution exists with %d colors.\n", m);
    } else {
        printf("\nTotal number of solutions found: %d\n", colorCount);
    }
}

// Function to allocate memory for the graph
void createGraph() {
    graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
    }

    // Initialize the adjacency matrix with zeros
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
}

// Function to free allocated memory
void freeMemory() {
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(color);
}

int main() {
    
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_VERTICES) {
        printf("Invalid number of vertices. Please enter a value between 1 and %d.\n", MAX_VERTICES);
        return 1;
    }
    
    // Allocate memory for the graph and color array
    createGraph();
    color = (int *)malloc(n * sizeof(int));
    
    if (graph == NULL || color == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("\nEnter the adjacency matrix (1 if vertices are adjacent, 0 otherwise):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    printf("\nEnter the number of colors: ");
    scanf("%d", &m);
    
    if (m <= 0) {
        printf("Invalid number of colors. Please enter a positive value.\n");
        freeMemory();
        return 1;
    }
    
    printf("\nSolving the Graph Coloring problem with %d colors...\n", m);
    graphColoring();
    
    // Free allocated memory
    freeMemory();
    
    return 0;
}