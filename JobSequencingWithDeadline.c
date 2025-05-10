#include <stdio.h>
#include <stdlib.h>

// Structure to represent a job
typedef struct {
    char id;        // Job identifier
    int deadline;   // Deadline of the job
    int profit;     // Profit if job is completed before deadline
} Job;

// Function to compare jobs based on profit (for qsort)
int compareJobs(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;
    
    // Sort in descending order of profit
    return jobB->profit - jobA->profit;
}

// Function to find the maximum deadline among all jobs
int findMaxDeadline(Job jobs[], int n) {
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }
    return maxDeadline;
}

// Function to solve Job Sequencing Problem
void jobSequencing(Job jobs[], int n) {
    // Sort jobs in descending order of profit
    qsort(jobs, n, sizeof(Job), compareJobs);
    
    // Find the maximum deadline among all jobs
    int maxDeadline = findMaxDeadline(jobs, n);
    
    // Create a slot array to store the job sequence
    char *slot = (char *)malloc((maxDeadline + 1) * sizeof(char));
    if (slot == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    // Initialize all slots as free
    for (int i = 0; i <= maxDeadline; i++) {
        slot[i] = '-';
    }
    
    int totalProfit = 0;
    
    // Iterate through all jobs
    for (int i = 0; i < n; i++) {
        // Find a free slot for this job (start from the last possible slot)
        for (int j = jobs[i].deadline; j > 0; j--) {
            // If free slot found, add job to the sequence
            if (slot[j] == '-') {
                slot[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }
    
    // Print the job sequence
    printf("\nOptimal Job Sequence: ");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != '-') {
            printf("%c ", slot[i]);
        }
    }
    printf("\nTotal Profit: %d\n", totalProfit);
    
    // Free allocated memory
    free(slot);
}

int main() {
    int n;
    
    printf("Enter the number of jobs: ");
    scanf("%d", &n);
    
    Job *jobs = (Job *)malloc(n * sizeof(Job));
    if (jobs == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter the details of each job:\n");
    for (int i = 0; i < n; i++) {
        printf("Job %d:\n", i + 1);
        
        // Set job ID (A, B, C, ...)
        jobs[i].id = 'A' + i;
        
        printf("  Deadline: ");
        scanf("%d", &jobs[i].deadline);
        
        printf("  Profit: ");
        scanf("%d", &jobs[i].profit);
    }
    
    printf("\nJob details:\n");
    printf("ID\tDeadline\tProfit\n");
    printf("------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t%d\t\t%d\n", jobs[i].id, jobs[i].deadline, jobs[i].profit);
    }
    
    // Solve the Job Sequencing Problem
    jobSequencing(jobs, n);
    
    // Free allocated memory
    free(jobs);
    
    return 0;
}