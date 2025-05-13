#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
typedef struct {
    int id;         // Item identifier
    float weight;   // Weight of the item
    float profit;    // profit of the item
    float ratio;    // profit-to-weight ratio
} Item;

// Function to compare items based on their profit-to-weight ratio (for qsort)
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    
    // Sort in descending order of profit-to-weight ratio
    if (itemB->ratio > itemA->ratio)
        return 1;
    else if (itemB->ratio < itemA->ratio)
        return -1;
    else
        return 0;
}

// Function to solve Fractional Knapsack problem
float fractionalKnapsack(Item items[], int n, float capacity) {
    // Calculate profit-to-weight ratio for each item
    for (int i = 0; i < n; i++) {
        items[i].ratio = items[i].profit / items[i].weight;
    }
    
    // Sort items based on profit-to-weight ratio (in descending order)
    qsort(items, n, sizeof(Item), compare);
    
    float totalprofit = 0.0;    // Total profit of items in knapsack
    float currentWeight = 0.0; // Current weight in knapsack
    
    printf("\nItems selected:\n");
    printf("Item ID\tObject\t\tWeight Added\tProfit Added\n");
    printf("--------------------------------------------------------\n");
    
    // Fill the knapsack with items in decreasing order of profit-to-weight ratio
    for (int i = 0; i < n; i++) {
        // If adding the entire item doesn't exceed capacity
        if (currentWeight + items[i].weight <= capacity) {
            // Add the entire item
            currentWeight += items[i].weight;
            totalprofit += items[i].profit;
            
            printf("%d\t100%% of Item %d\t%.2f\t\t%.2f\n", 
                   items[i].id, items[i].id, items[i].weight, items[i].profit);
        } else {
            // Add a fraction of the item
            float remainingCapacity = capacity - currentWeight;
            float fraction = remainingCapacity / items[i].weight;
            float percentTaken = fraction * 100;
            float weightAdded = items[i].weight * fraction;
            float profitAdded = items[i].profit * fraction;
            
            totalprofit += profitAdded;
            currentWeight += weightAdded;
            
            printf("%d\t%.0f%% of Item %d\t%.2f\t\t%.2f\n", 
                   items[i].id, percentTaken, items[i].id, weightAdded, profitAdded);
            
            // Knapsack is full, break the loop
            break;
        }
    }
    
    printf("--------------------------------------------------------\n");
    printf("Total weight: %.2f\n", currentWeight);
    printf("Total profit: %.2f\n", totalprofit);
    
    return totalprofit;
}

int main() {
    int n;
    float capacity;
    
    printf("Enter the number of items: ");
    scanf("%d", &n);
    
    Item *items = (Item *)malloc(n * sizeof(Item));
    if (items == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the capacity of the knapsack: ");
    scanf("%f", &capacity);
    
    printf("Enter the details of each item:\n");
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        printf("Item %d:\n", i + 1);
        printf("  Weight: ");
        scanf("%f", &items[i].weight);
        printf("  profit: ");
        scanf("%f", &items[i].profit);
    }
    
    printf("\nItem details:\n");
    printf("ID\tWeight\tprofit\n");
    printf("------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.2f\t%.2f\n", items[i].id, items[i].weight, items[i].profit);
    }
    
    // Solve the Fractional Knapsack problem
    float maxprofit = fractionalKnapsack(items, n, capacity);
    
    printf("\nMaximum profit that can be obtained: %.2f\n", maxprofit);
    
    // Free allocated memory
    free(items);
    
    return 0;
}