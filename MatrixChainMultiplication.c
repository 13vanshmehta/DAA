#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INT_MAX 999999

int mc[50][50];

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

int DynamicProgramming(int arr[], int i, int j) {
    if (i == j) return 0;
    
    if (mc[i][j] != -1) return mc[i][j];
    
    mc[i][j] = INT_MAX;
    for (int k = i; k < j; k++) {
        mc[i][j] = minimum(mc[i][j], 
                       DynamicProgramming(arr, i, k) + 
                       DynamicProgramming(arr, k + 1, j) + 
                       arr[i - 1] * arr[k] * arr[j]);
    }
    return mc[i][j];
}

void printCostTable(int n) {
    printf("\nCost Table (DP Table):\n");
    printf("    ");
    for (int j = 1; j <= n; j++) {
        printf("M%-4d", j);
    }
    printf("\n");
    
    for (int i = 1; i <= n; i++) {
        printf("M%-3d", i);
        for (int j = 1; j <= n; j++) {
            if (j < i) {
                printf("     ");
            } else if (i == j) {
                // Print 0 for diagonal elements
                printf("%-5d", 0);
            } else if (mc[i][j] == INT_MAX) {
                printf("INF  ");
            } else {
                printf("%-5d", mc[i][j]);
            }
        }
        printf("\n");
    }
}

void printParenthesis(int i, int j) {
    if (i == j) {
        printf("M%d", i);
        return;
    }
    printf("(");
    
    int k;
    int min = INT_MAX;
    for (int l = i; l < j; l++) {
        if (mc[i][l] + mc[l+1][j] + mc[i][j] < min) {
            min = mc[i][l] + mc[l+1][j] + mc[i][j];
            k = l;
        }
    }
    
    printParenthesis(i, k);
    printf(" x ");
    printParenthesis(k + 1, j);
    printf(")");
}

int main() {
    int n;
    printf("Enter number of matrices: ");
    scanf("%d", &n);
    
    if (n < 2) {
        printf("Need at least 2 matrices\n");
        return 1;
    }
    
    int *dimensions = (int *)malloc((n + 1) * sizeof(int));
    if (!dimensions) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("\nEnter matrix dimensions:\n");
    for (int i = 0; i < n; i++) {
        printf("Matrix %d:\n", i + 1);
        if (i == 0) {
            printf("Rows: ");
            scanf("%d", &dimensions[0]);
        }
        printf("Columns: ");
        scanf("%d", &dimensions[i + 1]);
    }
    
    memset(mc, -1, sizeof(mc));
    
    printf("\nMatrix Chain: ");
    for (int i = 1; i <= n; i++) {
        printf("M%d", i);
        if (i < n) printf(" x ");
    }
    printf("\n");
    
    int result = DynamicProgramming(dimensions, 1, n);
    
    // Print the cost table
    printCostTable(n);
    
    printf("\nMinimum number of multiplications: %d\n", result);
    printf("Optimal Parenthesization: ");
    printParenthesis(1, n);
    printf("\n");
    
    free(dimensions);
    return 0;
}