#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to compute the LPS (Longest Proper Prefix which is also Suffix) array
void computeLPSArray(char* pattern, int m, int* lps) {
    // Length of the previous longest prefix & suffix
    int len = 0;
    
    lps[0] = 0; // lps[0] is always 0
    
    // Calculate lps[i] for i = 1 to m-1
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                // This is the tricky part
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP algorithm for pattern searching
void KMPSearch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int found = 0;
    
    // Create lps[] that will hold the longest prefix suffix values for pattern
    int* lps = (int*)malloc(m * sizeof(int));
    if (lps == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pattern, m, lps);
    
    int i = 0; // index for text[]
    int j = 0; // index for pattern[]
    
    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        
        if (j == m) {
            // Found pattern at index i-j
            printf("Pattern found at position: %d\n", i - j);
            found = 1;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            // Mismatch after j matches
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
    
    free(lps); // Free the allocated memory
}

int main() {
    char text[1000], pattern[100];
    
    printf("Enter the text string: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // Remove newline
    
    printf("Enter the pattern to search for: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = 0; // Remove newline
    
    KMPSearch(text, pattern);
    
    return 0;
}