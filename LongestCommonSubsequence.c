#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxValue(int x, int y) {
    return x > y ? x : y; 
}

void findLCS(char s1[], char s2[]) {
    int m = strlen(s1);
    int n = strlen(s2);
    
    int **L = (int **)malloc((m + 1) * sizeof(int *));
    if (L == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i <= m; i++) {
        L[i] = (int *)malloc((n + 1) * sizeof(int));
        if (L[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (s1[i - 1] == s2[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = maxValue(L[i - 1][j], L[i][j - 1]);
        }
    }
    
    printf("\nLength of Longest Common Subsequence: %d\n", L[m][n]);
    
    char *lcs = (char *)malloc((L[m][n] + 1) * sizeof(char));
    if (lcs == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    lcs[L[m][n]] = '\0';
    
    int i = m, j = n;
    int index = L[m][n] - 1;
    
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs[index] = s1[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }
    
    printf("Longest Common Subsequence: %s\n", lcs);
    
    free(lcs);
    for (int i = 0; i <= m; i++) {
        free(L[i]);
    }
    free(L);
}

int main() {
    char s1[100], s2[100];
    
    printf("Longest Common Subsequence (LCS) Algorithm\n");
    printf("==========================================\n");
    
    printf("\nEnter 1ST String: ");
    scanf("%s", s1);
    
    printf("Enter 2ND String: ");
    scanf("%s", s2);
    
    printf("\nString 1: %s (length: %d)\n", s1, (int)strlen(s1));
    printf("String 2: %s (length: %d)\n", s2, (int)strlen(s2));
    
    findLCS(s1, s2);
    
    return 0;
}