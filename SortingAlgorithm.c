#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// QUICK SORT IMPLEMENTATION
// Function to find the partition position
int partition(int array[], int low, int high) {
    // Select the rightmost element as pivot
    int pivot = array[high];
    
    // Pointer for greater element
    int i = (low - 1);
    
    // Traverse through all elements
    // compare each element with pivot
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            // If element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;
            
            // Swap element at i with element at j
            swap(&array[i], &array[j]);
        }
    }
    
    // Swap the pivot element with the greater element at i
    swap(&array[i + 1], &array[high]);
    
    // Return the partition point
    return (i + 1);
}

// Function to implement quick sort
void quickSort(int array[], int low, int high) {
    if (low < high) {
        // Find the pivot element such that
        // elements smaller than pivot are on left
        // elements greater than pivot are on right
        int pi = partition(array, low, high);
        
        // Recursive call on the left of pivot
        quickSort(array, low, pi - 1);
        
        // Recursive call on the right of pivot
        quickSort(array, pi + 1, high);
    }
}

// MERGE SORT IMPLEMENTATION
// Merge two subarrays L and M into arr
void merge(int arr[], int p, int q, int r) {
    // Create L ← A[p..q] and M ← A[q+1..r]
    int n1 = q - p + 1;
    int n2 = r - q;
    
    int *L = (int*)malloc(n1 * sizeof(int));
    int *M = (int*)malloc(n2 * sizeof(int));
    
    if (L == NULL || M == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];
    
    // Maintain current index of sub-arrays and main array
    int i = 0, j = 0, k = p;
    
    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }
    
    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
    
    // Free allocated memory
    free(L);
    free(M);
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // m is the point where the array is divided into two subarrays
        int m = l + (r - l) / 2;
        
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        
        // Merge the sorted subarrays
        merge(arr, l, m, r);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function to test the sorting algorithms
int main() {
    int n, choice;
    int *arr = NULL;
    
    while (1) {
        printf("\n----- Sorting Algorithm Menu -----\n");
        printf("1. Quick Sort\n");
        printf("2. Merge Sort\n");
        printf("3. Exit\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        
        if (choice == 3) {
            printf("Exiting program. Goodbye!\n");
            // Free memory if allocated
            if (arr != NULL) {
                free(arr);
            }
            break;
        }
        
        printf("Enter the number of elements: ");
        scanf("%d", &n);
        
        // Free previous array if it exists
        if (arr != NULL) {
            free(arr);
        }
        
        // Allocate new array
        arr = (int*)malloc(n * sizeof(int));
        
        if (arr == NULL) {
            printf("Memory allocation failed\n");
            return -1;
        }
        
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        switch (choice) {
            case 1:
                printf("\nOriginal array: \n");
                printArray(arr, n);
                quickSort(arr, 0, n - 1);
                
                printf("Sorted array using Quick Sort: \n");
                printArray(arr, n);
                break;
                
            case 2:
                printf("\nOriginal array: \n");
                printArray(arr, n);
                mergeSort(arr, 0, n - 1);
                
                printf("Sorted array using Merge Sort: \n");
                printArray(arr, n);
                break;
                
            default:
                printf("Invalid choice! Please select 1, 2, or 3.\n");
        }
    }
    
    return 0;
}