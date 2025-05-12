#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Global variables
int *w;         // Array to store the set elements
int *x;         // Solution vector
int sum;        // Target sum
int n;          // Number of elements in the set
int total = 0;  // Sum of all elements in the set
int count = 0;  // Count of solutions found

// Function to print the solution
void printSolution() {
    printf("\nSolution %d: { ", ++count);
    for (int i = 0; i < n; i++) {
        if (x[i] == 1) {
            printf("%d ", w[i]);
        }
    }
    printf("}\n");
}

// Function to check if the current subset can lead to a solution
bool promising(int i, int currentSum, int remainingSum) {
    // Check if we can potentially reach the target sum
    if (currentSum > sum) {
        return false;  // Already exceeded the target sum
    }
    
    if (currentSum + remainingSum < sum) {
        return false;  // Cannot reach the target sum even with all remaining elements
    }
    
    return true;
}

// Sum of Subset using Branch and Bound
void sumOfSubset(int i, int currentSum, int remainingSum) {
    // If current subset sum equals target sum, we found a solution
    if (currentSum == sum) {
        printSolution();
        return;
    }
    
    // If we've considered all elements or current subset isn't promising, return
    if (i >= n || !promising(i, currentSum, remainingSum)) {
        return;
    }
    
    // Include current element
    x[i] = 1;
    sumOfSubset(i + 1, currentSum + w[i], remainingSum - w[i]);
    
    // Exclude current element
    x[i] = 0;
    sumOfSubset(i + 1, currentSum, remainingSum - w[i]);
}

int main() {
    printf("Sum of Subset Problem using Branch and Bound\n");
    printf("===========================================\n\n");
    
    printf("Enter the number of elements in the set: ");
    scanf("%d", &n);
    
    // Allocate memory for arrays
    w = (int *)malloc(n * sizeof(int));
    x = (int *)malloc(n * sizeof(int));
    
    if (w == NULL || x == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the elements of the set:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &w[i]);
        total += w[i];
        x[i] = 0;  // Initialize solution vector
    }
    
    printf("Enter the target sum: ");
    scanf("%d", &sum);
    
    printf("\nOriginal set: { ");
    for (int i = 0; i < n; i++) {
        printf("%d ", w[i]);
    }
    printf("}\n");
    
    printf("Target sum: %d\n", sum);
    
    // Check if the problem has a solution
    if (total < sum) {
        printf("\nNo solution exists. The sum of all elements (%d) is less than the target sum (%d).\n", total, sum);
        free(w);
        free(x);
        return 0;
    }
    
    printf("\nFinding all subsets with sum = %d...\n", sum);
    
    // Solve using Branch and Bound
    sumOfSubset(0, 0, total);
    
    if (count == 0) {
        printf("\nNo solution found.\n");
    } else {
        printf("\nTotal number of solutions found: %d\n", count);
    }
    
    // Free allocated memory
    free(w);
    free(x);
    
    return 0;
}