#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 20

// Function to check if assigning color c to vertex v is valid
bool isValid(int v, int color[], int c, bool graph[][MAX_VERTICES], int n) {
    for (int i = 0; i < n; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

// Function to display the assigned colors
void showColors(int color[], int n) {
    printf("\nAssigned Colors are:\n");
    printf("Vertex \tColor\n");
    for (int i = 0; i < n; i++)
        printf("%d \t%d\n", i + 1, color[i]);
}

// Recursive function to solve graph coloring
bool graphColoring(int colors, int color[], int vertex, bool graph[][MAX_VERTICES], int n) {
    // When all vertices are assigned a color
    if (vertex == n)
        return true;
        
    for (int col = 1; col <= colors; col++) {
        // Check if color is valid for this vertex
        if (isValid(vertex, color, col, graph, n)) {
            color[vertex] = col;
            // Proceed to next vertex
            if (graphColoring(colors, color, vertex + 1, graph, n))
                return true;
            // Backtrack if no solution found
            color[vertex] = 0;
        }
    }
    // No solution exists
    return false;
}

// Function to check if a solution exists and display it
bool checkSolution(int m, bool graph[][MAX_VERTICES], int n) {
    // Allocate memory for color array
    int *color = (int *)malloc(n * sizeof(int));
    if (color == NULL) {
        printf("Memory allocation failed\n");
        return false;
    }
    
    // Initialize all colors to 0
    for (int i = 0; i < n; i++)
        color[i] = 0;
        
    // Try to color the graph
    if (graphColoring(m, color, 0, graph, n) == false) {
        printf("\nSolution does not exist with %d colors.\n", m);
        free(color);
        return false;
    }
    
    // Display the solution
    showColors(color, n);
    free(color);
    return true;
}

int main() {
    int n, m;
    bool graph[MAX_VERTICES][MAX_VERTICES];
    
    // Get number of vertices
    printf("Enter the number of vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_VERTICES) {
        printf("Invalid number of vertices. Please enter a value between 1 and %d.\n", MAX_VERTICES);
        return 1;
    }
    
    // Initialize graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = false;
        }
    }
    
    // Get adjacency matrix
    printf("\nEnter the adjacency matrix (1 if vertices are adjacent, 0 otherwise):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val;
            scanf("%d", &val);
            graph[i][j] = (val == 1);
        }
    }
    
    // Get number of colors
    printf("\nEnter the number of colors: ");
    scanf("%d", &m);
    
    if (m <= 0) {
        printf("Invalid number of colors. Please enter a positive value.\n");
        return 1;
    }
    
    printf("\nSolving the Graph Coloring problem with %d colors...\n", m);
    checkSolution(m, graph, n);
    
    return 0;
}