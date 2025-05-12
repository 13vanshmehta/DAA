#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>  // Added for time() function

#define MAX_CITIES 15

// Function to find the minimum of two numbers
int minimum(int a, int b) {
    return (a < b) ? a : b;
}

// Function to find the minimum cost path
int tsp(int graph[MAX_CITIES][MAX_CITIES], int mask, int pos, int n, int dp[1 << MAX_CITIES][MAX_CITIES]) {
    // If all cities have been visited
    if (mask == ((1 << n) - 1)) {
        return graph[pos][0];  // Return to starting city
    }

    // If the subproblem has already been solved
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    // Initialize result with a large value
    int ans = INT_MAX;

    // Try to go to an unvisited city
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {  // If city is not visited
            int newAns = graph[pos][city] + tsp(graph, mask | (1 << city), city, n, dp);
            if (newAns < ans) {
                ans = newAns;
            }
        }
    }

    // Store the result in dp table
    return dp[mask][pos] = ans;
}

// Function to reconstruct the path
void findPath(int graph[MAX_CITIES][MAX_CITIES], int n, int dp[1 << MAX_CITIES][MAX_CITIES], int path[MAX_CITIES]) {
    int mask = 1;  // Start with only city 0 visited
    int pos = 0;   // Start at city 0
    
    path[0] = 0;   // First city in path
    
    // Find remaining n-1 cities
    for (int i = 1; i < n; i++) {
        int nextCity = -1;
        int minCost = INT_MAX;
        
        // Find the next unvisited city with minimum cost
        for (int city = 0; city < n; city++) {
            if ((mask & (1 << city)) == 0) {  // If city is not visited
                int cost = graph[pos][city] + dp[mask | (1 << city)][city];
                if (cost < minCost) {
                    minCost = cost;
                    nextCity = city;
                }
            }
        }
        
        path[i] = nextCity;  // Add to path
        mask |= (1 << nextCity);  // Mark as visited
        pos = nextCity;  // Move to this city
    }
}

// Function to solve the TSP problem
void solveTSP(int graph[MAX_CITIES][MAX_CITIES], int n) {
    // Create a DP table
    int dp[1 << MAX_CITIES][MAX_CITIES];
    
    // Initialize the DP table with -1
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    
    // Array to store the path
    int path[MAX_CITIES];
    
    // Call the recursive function to find minimum cost
    int minCost = tsp(graph, 1, 0, n, dp);
    
    // Reconstruct the path
    findPath(graph, n, dp, path);
    
    // Print the minimum cost
    printf("\nMinimum cost: %d\n", minCost);
    
    // Print the path
    printf("Path: ");
    for (int i = 0; i < n; i++) {
        printf("%d", path[i]);
        if (i < n - 1) printf(" -> ");
    }
    printf(" -> 0\n");  // Return to starting city
}

// Function to print the DP table (for small instances)
void printDPTable(int dp[1 << MAX_CITIES][MAX_CITIES], int n) {
    printf("\nDP Table (partial view for small subsets):\n");
    printf("Mask\tPos\tValue\n");
    
    // Print only for small subsets to avoid overwhelming output
    for (int mask = 0; mask < (1 << minimum(n, 4)); mask++) {
        for (int pos = 0; pos < minimum(n, 4); pos++) {
            if (dp[mask][pos] != -1) {
                printf("%d\t%d\t%d\n", mask, pos, dp[mask][pos]);
            }
        }
    }
}

// Function to generate a random graph
void generateRandomGraph(int graph[MAX_CITIES][MAX_CITIES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;  // Distance to self is 0
            } else {
                graph[i][j] = rand() % 100 + 1;  // Random distance between 1 and 100
            }
        }
    }
}

// Function to print the graph
void printGraph(int graph[MAX_CITIES][MAX_CITIES], int n) {
    printf("\nDistance Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    int graph[MAX_CITIES][MAX_CITIES];
    
    printf("Travelling Salesperson Problem using Dynamic Programming\n");
    printf("------------------------------------------------------\n");
    
    printf("Enter the number of cities (max %d): ", MAX_CITIES);
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_CITIES) {
        printf("Invalid number of cities!\n");
        return 1;
    }
    
    int choice;
    printf("\nChoose input method:\n");
    printf("1. Enter distances manually\n");
    printf("2. Generate random distances\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("\nEnter the distance matrix (%d x %d):\n", n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("Distance from city %d to city %d: ", i, j);
                scanf("%d", &graph[i][j]);
            }
        }
    } else if (choice == 2) {
        // Seed the random number generator
        srand(time(NULL));
        generateRandomGraph(graph, n);
    } else {
        printf("Invalid choice!\n");
        return 1;
    }
    
    // Print the graph
    printGraph(graph, n);
    
    // Solve the TSP
    printf("\nSolving TSP using dynamic programming (Held-Karp algorithm)...\n");
    solveTSP(graph, n);
    
    return 0;
}