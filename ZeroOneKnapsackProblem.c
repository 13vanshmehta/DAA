#include <stdio.h>
#include <stdlib.h>

// Function to find the maximum of two integers
int maximum(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve 0/1 Knapsack problem using dynamic programming
int knapsack(int W, int weights[], int values[], int n) {
    // Create a 2D DP table to store results of subproblems
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
        if (dp[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    // Build table dp[][] in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;  // Base case: no items or no capacity
            else if (weights[i - 1] <= w)
                // Include or exclude the current item
                dp[i][w] = maximum(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                // Current item is too heavy, exclude it
                dp[i][w] = dp[i - 1][w];
        }
    }
    
    // Store the result
    int result = dp[n][W];
    
    // Print the DP table (optional)
    printf("\nDP Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            printf("%d\t", dp[i][w]);
        }
        printf("\n");
    }
    
    // Find which items are included in the optimal solution
    printf("\nItems included in the knapsack:\n");
    printf("Item\tWeight\tValue\n");
    printf("------------------------\n");
    
    int w = W;
    for (int i = n; i > 0 && result > 0; i--) {
        // If result comes from including the current item
        if (result != dp[i - 1][w]) {
            printf("%d\t%d\t%d\n", i, weights[i - 1], values[i - 1]);
            result -= values[i - 1];
            w -= weights[i - 1];
        }
    }
    
    // Free allocated memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return dp[n][W];
}

// Function to solve 0/1 Knapsack problem using 1D array (space-optimized)
int knapsackOptimized(int W, int weights[], int values[], int n) {
    // Create a 1D array for DP
    int *dp = (int *)malloc((W + 1) * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    // Initialize dp array
    for (int i = 0; i <= W; i++) {
        dp[i] = 0;
    }
    
    // Fill dp array in bottom-up manner
    for (int i = 0; i < n; i++) {
        // Process in reverse to avoid using items multiple times
        for (int w = W; w >= weights[i]; w--) {
            dp[w] = maximum(dp[w], values[i] + dp[w - weights[i]]);
        }
    }
    
    // Store the result
    int result = dp[W];
    
    // Free allocated memory
    free(dp);
    
    return result;
}

int main() {
    int n, W;
    
    printf("Enter the number of items: ");
    scanf("%d", &n);
    
    int *weights = (int *)malloc(n * sizeof(int));
    int *values = (int *)malloc(n * sizeof(int));
    
    if (weights == NULL || values == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the weight and value of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Weight: ");
        scanf("%d", &weights[i]);
        printf("  Value: ");
        scanf("%d", &values[i]);
    }
    
    printf("Enter the knapsack capacity: ");
    scanf("%d", &W);
    
    printf("\nItem details:\n");
    printf("Item\tWeight\tValue\n");
    printf("------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, weights[i], values[i]);
    }
    
    // Solve using standard DP approach
    int maxValue = knapsack(W, weights, values, n);
    printf("\nMaximum value that can be obtained: %d\n", maxValue);
    
    // Solve using space-optimized approach
    int maxValueOptimized = knapsackOptimized(W, weights, values, n);
    printf("\nMaximum value (space-optimized): %d\n", maxValueOptimized);
    
    // Free allocated memory
    free(weights);
    free(values);
    
    return 0;
}