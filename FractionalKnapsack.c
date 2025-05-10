#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
typedef struct {
    int id;         // Item identifier
    float weight;   // Weight of the item
    float value;    // Value of the item
    float ratio;    // Value-to-weight ratio
} Item;

// Function to compare items based on their value-to-weight ratio (for qsort)
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    
    // Sort in descending order of value-to-weight ratio
    if (itemB->ratio > itemA->ratio)
        return 1;
    else if (itemB->ratio < itemA->ratio)
        return -1;
    else
        return 0;
}

// Function to solve Fractional Knapsack problem
float fractionalKnapsack(Item items[], int n, float capacity) {
    // Calculate value-to-weight ratio for each item
    for (int i = 0; i < n; i++) {
        items[i].ratio = items[i].value / items[i].weight;
    }
    
    // Sort items based on value-to-weight ratio (in descending order)
    qsort(items, n, sizeof(Item), compare);
    
    float totalValue = 0.0;    // Total value of items in knapsack
    float currentWeight = 0.0; // Current weight in knapsack
    
    printf("\nItems selected:\n");
    printf("ID\tWeight\tValue\tRatio\tFraction\n");
    printf("----------------------------------------\n");
    
    // Fill the knapsack with items in decreasing order of value-to-weight ratio
    for (int i = 0; i < n; i++) {
        // If adding the entire item doesn't exceed capacity
        if (currentWeight + items[i].weight <= capacity) {
            // Add the entire item
            currentWeight += items[i].weight;
            totalValue += items[i].value;
            
            printf("%d\t%.2f\t%.2f\t%.2f\t1.00\n", 
                   items[i].id, items[i].weight, items[i].value, items[i].ratio);
        } else {
            // Add a fraction of the item
            float remainingCapacity = capacity - currentWeight;
            float fraction = remainingCapacity / items[i].weight;
            
            totalValue += items[i].value * fraction;
            currentWeight += items[i].weight * fraction;
            
            printf("%d\t%.2f\t%.2f\t%.2f\t%.2f\n", 
                   items[i].id, items[i].weight, items[i].value, items[i].ratio, fraction);
            
            // Knapsack is full, break the loop
            break;
        }
    }
    
    printf("----------------------------------------\n");
    printf("Total weight: %.2f\n", currentWeight);
    printf("Total value: %.2f\n", totalValue);
    
    return totalValue;
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
        printf("  Value: ");
        scanf("%f", &items[i].value);
    }
    
    printf("\nItem details:\n");
    printf("ID\tWeight\tValue\n");
    printf("------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.2f\t%.2f\n", items[i].id, items[i].weight, items[i].value);
    }
    
    // Solve the Fractional Knapsack problem
    float maxValue = fractionalKnapsack(items, n, capacity);
    
    printf("\nMaximum value that can be obtained: %.2f\n", maxValue);
    
    // Free allocated memory
    free(items);
    
    return 0;
}