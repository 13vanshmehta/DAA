#include <stdio.h>
#include <stdlib.h>

// Structure to store the minimum and maximum values
typedef struct {
    int min;
    int max;
} MinMax;

// Function to find minimum and maximum in an array using divide and conquer
MinMax findMinMax(int arr[], int low, int high) {
    MinMax result, left, right;
    int mid;
    
    // If there is only one element
    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }
    
    // If there are two elements
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
    
    // If there are more than 2 elements, divide the array
    mid = (low + high) / 2;
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);
    
    // Compare minimums of two parts
    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;
    
    // Compare maximums of two parts
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
    
    // Using recursive divide and conquer approach
    MinMax result1 = findMinMax(arr, 0, n - 1);
    printf("\nUsing Divide and Conquer approach:\n");
    printf("Minimum element is %d\n", result1.min);
    printf("Maximum element is %d\n", result1.max);
    
    free(arr);
    return 0;
}

// Notes:
// - The `MinMax` structure is used to store the minimum and maximum values.
// - The `findMinMax` function recursively divides the array into two parts and compares the minimum and maximum values of the two parts.
// - The time complexity of this algorithm is O(n) in the worst case.
// - The space complexity is O(log n) due to the recursive calls on the stack.
// - The divide and conquer approach makes approximately 3n/2 - 2 comparisons