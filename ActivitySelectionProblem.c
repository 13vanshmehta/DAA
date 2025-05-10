#include <stdio.h>
#include <stdlib.h>

// Structure to represent an activity
typedef struct {
    int id;         // Activity identifier
    int start;      // Start time
    int finish;     // Finish time
} Activity;

// Function to compare activities based on finish time (for qsort)
int compareActivities(const void *a, const void *b) {
    Activity *activityA = (Activity *)a;
    Activity *activityB = (Activity *)b;
    
    return activityA->finish - activityB->finish;
}

// Function to solve Activity Selection Problem
void activitySelection(Activity activities[], int n) {
    // Sort activities based on finish time
    qsort(activities, n, sizeof(Activity), compareActivities);
    
    printf("\nSelected Activities:\n");
    printf("ID\tStart\tFinish\n");
    printf("------------------------\n");
    
    // Always select the first activity
    int i = 0;
    printf("%d\t%d\t%d\n", activities[i].id, activities[i].start, activities[i].finish);
    
    // Consider rest of the activities
    for (int j = 1; j < n; j++) {
        // If this activity has start time greater than or equal to the finish
        // time of previously selected activity, then select it
        if (activities[j].start >= activities[i].finish) {
            printf("%d\t%d\t%d\n", activities[j].id, activities[j].start, activities[j].finish);
            i = j;
        }
    }
}

int main() {
    int n;
    
    printf("Enter the number of activities: ");
    scanf("%d", &n);
    
    Activity *activities = (Activity *)malloc(n * sizeof(Activity));
    if (activities == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the details of each activity:\n");
    for (int i = 0; i < n; i++) {
        activities[i].id = i + 1;
        printf("Activity %d:\n", i + 1);
        printf("  Start time: ");
        scanf("%d", &activities[i].start);
        printf("  Finish time: ");
        scanf("%d", &activities[i].finish);
    }
    
    printf("\nActivity details:\n");
    printf("ID\tStart\tFinish\n");
    printf("------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", activities[i].id, activities[i].start, activities[i].finish);
    }
    
    // Solve the Activity Selection Problem
    activitySelection(activities, n);
    
    // Free allocated memory
    free(activities);
    
    return 0;
}