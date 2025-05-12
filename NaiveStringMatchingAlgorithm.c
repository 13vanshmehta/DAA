#include <stdio.h>
#include <string.h>

// Function to implement the Naive String Matching algorithm
void naiveStringMatch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;
    
    // Check for each possible position in text
    for (int i = 0; i <= n - m; i++) {
        int j;
        
        // For current index i, check for pattern match
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;  // Mismatch found, break inner loop
            }
        }
        
        // If inner loop completed, pattern was found
        if (j == m) {
            printf("Pattern found at position: %d\n", i);
            count++;
        }
    }
    
    if (count == 0) {
        printf("Pattern not found in the text.\n");
    }
}

int main() {
    char text[1000], pattern[100];
    
    printf("Enter the text string: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // Remove newline
    
    printf("Enter the pattern to search for: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = 0; // Remove newline
    
    naiveStringMatch(text, pattern);
    
    return 0;
}