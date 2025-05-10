#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to dynamically allocate memory for a matrix
int** createMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to free memory allocated for a matrix
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to add two matrices
void addMatrix(int** A, int** B, int** C, int n, int sign) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + sign * B[i][j];
        }
    }
}

// Function to print a matrix
void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Strassen's matrix multiplication algorithm
void strassenMultiply(int** A, int** B, int** C, int n) {
    // Base case: if matrix size is small, use standard multiplication
    if (n <= 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    
    int newSize = n / 2;
    
    // Create submatrices
    int** A11 = createMatrix(newSize);
    int** A12 = createMatrix(newSize);
    int** A21 = createMatrix(newSize);
    int** A22 = createMatrix(newSize);
    
    int** B11 = createMatrix(newSize);
    int** B12 = createMatrix(newSize);
    int** B21 = createMatrix(newSize);
    int** B22 = createMatrix(newSize);
    
    // Temporary matrices for calculations
    int** M1 = createMatrix(newSize);
    int** M2 = createMatrix(newSize);
    int** M3 = createMatrix(newSize);
    int** M4 = createMatrix(newSize);
    int** M5 = createMatrix(newSize);
    int** M6 = createMatrix(newSize);
    int** M7 = createMatrix(newSize);
    
    int** C11 = createMatrix(newSize);
    int** C12 = createMatrix(newSize);
    int** C21 = createMatrix(newSize);
    int** C22 = createMatrix(newSize);
    
    int** temp1 = createMatrix(newSize);
    int** temp2 = createMatrix(newSize);
    
    // Divide matrices into 4 submatrices each
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    
    // Calculate 7 products (Strassen's formulas)
    
    // M1 = (A11 + A22) * (B11 + B22)
    addMatrix(A11, A22, temp1, newSize, 1);
    addMatrix(B11, B22, temp2, newSize, 1);
    strassenMultiply(temp1, temp2, M1, newSize);
    
    // M2 = (A21 + A22) * B11
    addMatrix(A21, A22, temp1, newSize, 1);
    strassenMultiply(temp1, B11, M2, newSize);
    
    // M3 = A11 * (B12 - B22)
    addMatrix(B12, B22, temp1, newSize, -1);
    strassenMultiply(A11, temp1, M3, newSize);
    
    // M4 = A22 * (B21 - B11)
    addMatrix(B21, B11, temp1, newSize, -1);
    strassenMultiply(A22, temp1, M4, newSize);
    
    // M5 = (A11 + A12) * B22
    addMatrix(A11, A12, temp1, newSize, 1);
    strassenMultiply(temp1, B22, M5, newSize);
    
    // M6 = (A21 - A11) * (B11 + B12)
    addMatrix(A21, A11, temp1, newSize, -1);
    addMatrix(B11, B12, temp2, newSize, 1);
    strassenMultiply(temp1, temp2, M6, newSize);
    
    // M7 = (A12 - A22) * (B21 + B22)
    addMatrix(A12, A22, temp1, newSize, -1);
    addMatrix(B21, B22, temp2, newSize, 1);
    strassenMultiply(temp1, temp2, M7, newSize);
    
    // Calculate the resulting submatrices
    
    // C11 = M1 + M4 - M5 + M7
    addMatrix(M1, M4, temp1, newSize, 1);
    addMatrix(temp1, M5, temp2, newSize, -1);
    addMatrix(temp2, M7, C11, newSize, 1);
    
    // C12 = M3 + M5
    addMatrix(M3, M5, C12, newSize, 1);
    
    // C21 = M2 + M4
    addMatrix(M2, M4, C21, newSize, 1);
    
    // C22 = M1 + M3 - M2 + M6
    addMatrix(M1, M3, temp1, newSize, 1);
    addMatrix(temp1, M2, temp2, newSize, -1);
    addMatrix(temp2, M6, C22, newSize, 1);
    
    // Combine the 4 submatrices into the result matrix
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    
    // Free all allocated memory
    freeMatrix(A11, newSize);
    freeMatrix(A12, newSize);
    freeMatrix(A21, newSize);
    freeMatrix(A22, newSize);
    
    freeMatrix(B11, newSize);
    freeMatrix(B12, newSize);
    freeMatrix(B21, newSize);
    freeMatrix(B22, newSize);
    
    freeMatrix(M1, newSize);
    freeMatrix(M2, newSize);
    freeMatrix(M3, newSize);
    freeMatrix(M4, newSize);
    freeMatrix(M5, newSize);
    freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);
    
    freeMatrix(C11, newSize);
    freeMatrix(C12, newSize);
    freeMatrix(C21, newSize);
    freeMatrix(C22, newSize);
    
    freeMatrix(temp1, newSize);
    freeMatrix(temp2, newSize);
}

// Function to find the next power of 2
int nextPowerOf2(int n) {
    int power = 1;
    while (power < n) {
        power *= 2;
    }
    return power;
}

int main() {
    int n;
    printf("Enter the size of matrices (n for n x n): ");
    scanf("%d", &n);
    
    // Find the next power of 2 for the matrix size
    int paddedSize = nextPowerOf2(n);
    
    // Create matrices with padded size
    int** A = createMatrix(paddedSize);
    int** B = createMatrix(paddedSize);
    int** C = createMatrix(paddedSize);
    
    // Initialize matrices with zeros
    for (int i = 0; i < paddedSize; i++) {
        for (int j = 0; j < paddedSize; j++) {
            A[i][j] = 0;
            B[i][j] = 0;
            C[i][j] = 0;
        }
    }
    
    // Input for matrix A
    printf("Enter elements of matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    
    // Input for matrix B
    printf("Enter elements of matrix B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }
    
    // Perform Strassen's matrix multiplication
    strassenMultiply(A, B, C, paddedSize);
    
    // Print the original matrices
    printf("\nMatrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMatrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", B[i][j]);
        }
        printf("\n");
    }
    
    // Print the result matrix
    printf("\nResult Matrix (using Strassen's algorithm):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }
    
    // Free allocated memory
    freeMatrix(A, paddedSize);
    freeMatrix(B, paddedSize);
    freeMatrix(C, paddedSize);
    
    return 0;
}