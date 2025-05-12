#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to print the optimal parenthesization
void printOptimalParenthesis(int i, int j, int n, int **bracket, char *name) {
    // If only one matrix, print its name
    if (i == j) {
        printf("%c", name[i]);
        return;
    }

    printf("(");
    
    // Get the split point from bracket table
    int k = bracket[i][j];
    
    // Print left part
    printOptimalParenthesis(i, k, n, bracket, name);
    
    // Print right part
    printOptimalParenthesis(k + 1, j, n, bracket, name);
    
    printf(")");
}

// Matrix Chain Multiplication using Dynamic Programming
void matrixChainMultiplication(int p[], int n) {
    // Length of the chain is n-1
    n = n - 1;
    
    // Tables for storing results
    int **m = (int **)malloc(n * sizeof(int *));     // For storing minimum number of operations
    if (m == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for(int i = 0; i < n; i++) {
        m[i] = (int *)malloc(n * sizeof(int));
        if (m[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    int **bracket = (int **)malloc(n * sizeof(int *)); // For storing optimal split positions
    if (bracket == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for(int i = 0; i < n; i++) {
        bracket[i] = (int *)malloc(n * sizeof(int));
        if (bracket[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    char *name = (char *)malloc(n * sizeof(char));    // For storing matrix names (A, B, C, ...)
    if (name == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    // Initialize matrix names
    for (int i = 0; i < n; i++) {
        name[i] = 'A' + i;
    }
    
    // Initialize m table with 0 for the diagonal (single matrix case)
    for (int i = 0; i < n; i++) {
        m[i][i] = 0;
    }
    
    // Build the table in bottom-up manner
    // l is the chain length
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            
            // Try each possible split position
            for (int k = i; k < j; k++) {
                // Calculate cost for this split
                int cost = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                
                // Update if this is better
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }
    
    // Print the DP table
    printf("\nDP Table (Minimum number of operations):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < i) {
                printf("\t");
            } else {
                printf("%d\t", m[i][j]);
            }
        }
        printf("\n");
    }
    
    // Print the dimensions of each matrix
    printf("\nMatrix Dimensions:\n");
    for (int i = 0; i < n; i++) {
        printf("%c: %d x %d\n", name[i], p[i], p[i + 1]);
    }

    // Print the optimal parenthesization
    printf("\nOptimal Parenthesization: ");
    printOptimalParenthesis(0, n - 1, n, bracket, name);
    
    // Print the minimum number of operations
    printf("\nMinimum number of operations: %d\n", m[0][n - 1]);
    

    
    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(m[i]);
        free(bracket[i]);
    }
    free(m);
    free(bracket);
    free(name);
}

int main() {
    int n;
    
    printf("Enter the number of matrices: ");
    scanf("%d", &n);
    
    if (n < 2) {
        printf("At least 2 matrices are required for matrix chain multiplication.\n");
        return 1;
    }
    
    // Array to store dimensions
    // For n matrices, we need n+1 dimensions
    int *p = (int *)malloc((n + 1) * sizeof(int));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the dimensions of matrices:\n");
    for (int i = 0; i < n; i++) {
        printf("Matrix %c (%d):\n", 'A' + i, i + 1);
        
        if (i == 0) {
            printf("  Rows: ");
            scanf("%d", &p[0]);
            printf("  Columns: ");
            scanf("%d", &p[1]);
        } else {
            printf("  Rows: %d (fixed from previous matrix)\n", p[i]);
            printf("  Columns: ");
            scanf("%d", &p[i + 1]);
        }
    }
    
    printf("\nMatrix Chain: ");
    for (int i = 0; i < n; i++) {
        printf("%c", 'A' + i);
        if (i < n - 1) printf(" x ");
    }
    printf("\n");
    
    // Solve the Matrix Chain Multiplication problem
    matrixChainMultiplication(p, n + 1);
    
    // Free allocated memory
    free(p);
    
    return 0;
}