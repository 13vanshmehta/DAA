#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minCoins(int coins[], int n, int amount) {
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    dp[0] = 0;
    
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
    }
    
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                int subResult = dp[i - coins[j]];
                if (subResult != INT_MAX && subResult + 1 < dp[i]) {
                    dp[i] = subResult + 1;
                }
            }
        }
    }
    
    int result = dp[amount];
    free(dp);
    return result;
}

void printCoinCombination(int coins[], int n, int amount) {
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    int *coinUsed = (int *)malloc((amount + 1) * sizeof(int));
    
    if (dp == NULL || coinUsed == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    dp[0] = 0;
    
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
        coinUsed[i] = -1;
    }
    
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
    
    if (dp[amount] == INT_MAX) {
        printf("No solution exists for amount %d\n", amount);
        free(dp);
        free(coinUsed);
        return;
    }
    
    printf("Coins used to make amount %d (minimum %d coins):\n", amount, dp[amount]);
    
    int currentAmount = amount;
    while (currentAmount > 0) {
        int coinIndex = coinUsed[currentAmount];
        printf("%d ", coins[coinIndex]);
        currentAmount -= coins[coinIndex];
    }
    printf("\n");
    
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
    
    printf("Enter the sum of coins: ");
    scanf("%d", &amount);
    
    int min = minCoins(coins, n, amount);
    if (min == INT_MAX) {
        printf("\nIt's not possible to make change for %d with the given denominations\n", amount);
    } else {
        printf("\nMinimum number of coins needed: %d\n", min);
        printCoinCombination(coins, n, amount);
    }
    
    free(coins);
    return 0;
}