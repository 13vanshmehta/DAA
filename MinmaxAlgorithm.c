#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int min;
    int max;
} MinMax;

MinMax findMinMax(int arr[], int low, int high) {
    MinMax result, left, right;
    int mid;

    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }

    mid = (low + high) / 2;
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;
    
    return result;
}

int main() {
    int n, i;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    MinMax result1 = findMinMax(arr, 0, n - 1);
    printf("\nUsing Divide and Conquer approach:\n");
    printf("Minimum element is %d\n", result1.min);
    printf("Maximum element is %d\n", result1.max);
    
    free(arr);
    return 0;
}