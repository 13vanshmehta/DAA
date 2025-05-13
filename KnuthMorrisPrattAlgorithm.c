#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void computeLPSArray(char* pattern, int m, int* lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int found = 0;

    int* lps = (int*)malloc(m * sizeof(int));
    if (lps == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    computeLPSArray(pattern, m, lps);

    int i = 0;
    int j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        if (j == m) {
            printf("Pattern found at position: %d\n", i - j);
            found = 1;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    if (!found) {
        printf("Pattern not found in the text.\n");
    }
    
    free(lps);
}

int main() {
    char text[1000], pattern[100];
    
    printf("Enter TEXT: ");
    scanf("%s", text);
    getchar();
    
    printf("Enter PATTERN: ");
    scanf("%s", pattern);
    printf("\n");
    
    KMPSearch(text, pattern);
    return 0;
}