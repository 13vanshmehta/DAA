#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find the minimum number of coins needed to make change
int minCoins(int coins[], int n, int amount) {
    // Create a table to store the minimum number of coins for each amount
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    // Base case: 0 coins needed to make amount 0
    dp[0] = 0;
    
    // Initialize all other values as infinity
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
    }
    
    // Fill the dp table bottom-up
    for (int i = 1; i <= amount; i++) {
        // Try each coin
        for (int j = 0; j < n; j++) {
            // If the coin value is less than or equal to the current amount
            if (coins[j] <= i) {
                // Check if we can use this coin
                int subResult = dp[i - coins[j]];
                if (subResult != INT_MAX && subResult + 1 < dp[i]) {
                    dp[i] = subResult + 1;
                }
            }
        }
    }
    
    // Store the result
    int result = dp[amount];
    
    // Free allocated memory
    free(dp);
    
    // Return the result (INT_MAX means no solution exists)
    return result;
}

// Function to find all possible ways to make change
int countWays(int coins[], int n, int amount) {
    // Create a table to store the number of ways for each amount
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    // Base case: 1 way to make amount 0 (using no coins)
    dp[0] = 1;
    
    // Initialize all other values as 0
    for (int i = 1; i <= amount; i++) {
        dp[i] = 0;
    }
    
    // Fill the dp table
    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    
    // Store the result
    int result = dp[amount];
    
    // Free allocated memory
    free(dp);
    
    return result;
}

// Function to print the coins used to make change (minimum number of coins)
void printCoinCombination(int coins[], int n, int amount) {
    // Create tables for dp and to track which coins were used
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    int *coinUsed = (int *)malloc((amount + 1) * sizeof(int));
    
    if (dp == NULL || coinUsed == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    // Base case
    dp[0] = 0;
    
    // Initialize all other values as infinity
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
        coinUsed[i] = -1;
    }
    
    // Fill the dp table bottom-up
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                int subResult = dp[i - coins[j]];
                if (subResult != INT_MAX && subResult + 1 < dp[i]) {
                    dp[i] = subResult + 1;
                    coinUsed[i] = j;
                }
            }
        }
    }
    
    // If no solution exists
    if (dp[amount] == INT_MAX) {
        printf("No solution exists for amount %d\n", amount);
        free(dp);
        free(coinUsed);
        return;
    }
    
    // Print the coins used
    printf("Coins used to make amount %d (minimum %d coins):\n", amount, dp[amount]);
    
    int currentAmount = amount;
    while (currentAmount > 0) {
        int coinIndex = coinUsed[currentAmount];
        printf("%d ", coins[coinIndex]);
        currentAmount -= coins[coinIndex];
    }
    printf("\n");
    
    // Free allocated memory
    free(dp);
    free(coinUsed);
}

int main() {
    int n, amount;
    
    printf("Enter the number of coin denominations: ");
    scanf("%d", &n);
    
    int *coins = (int *)malloc(n * sizeof(int));
    if (coins == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the coin denominations:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }
    
    printf("Enter the amount to make change for: ");
    scanf("%d", &amount);
    
    // Find and print the minimum number of coins needed
    int min = minCoins(coins, n, amount);
    if (min == INT_MAX) {
        printf("It's not possible to make change for %d with the given denominations\n", amount);
    } else {
        printf("Minimum number of coins needed: %d\n", min);
        
        // Print the coin combination
        printCoinCombination(coins, n, amount);
    }
    
    // Find and print the total number of ways to make change
    int ways = countWays(coins, n, amount);
    printf("Total number of ways to make change: %d\n", ways);
    
    // Free allocated memory
    free(coins);
    
    return 0;
}