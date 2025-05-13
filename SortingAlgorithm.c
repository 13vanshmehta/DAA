#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// QUICK SORT IMPLEMENTATION
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

// MERGE SORT IMPLEMENTATION
void merge(int arr[], int p, int q, int r) {
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

    int i = 0, j = 0, k = p;
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

    free(L);
    free(M);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n, choice;
    int *arr = NULL;
    
    while (1) {
        printf("\nSelect Sorting Algorithm\n");
        printf("1. Quick Sort\n");
        printf("2. Merge Sort\n");
        printf("3. Exit\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        
        if (choice == 3) {
            printf("Exiting program. Goodbye!\n");
            if (arr != NULL) {
                free(arr);
            }
            break;
        }
        
        printf("Enter the number of elements: ");
        scanf("%d", &n);
        if (arr != NULL) {
            free(arr);
        }

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