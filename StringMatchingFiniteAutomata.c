#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_OF_CHARS 256

// Build the finite automaton for the pattern
int** computeTransitionFunction(char* pattern, int m) {
    int** TF = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        TF[i] = (int*)malloc(NO_OF_CHARS * sizeof(int));
    }
    
    int i, lps, x;
    
    // Initialize all entries in transition table to 0
    for (i = 0; i <= m; ++i) {
        for (x = 0; x < NO_OF_CHARS; ++x) {
            TF[i][x] = 0;
        }
    }
    
    // Fill the actual values in the transition table
    for (i = 0; i <= m; ++i) {
        // For each character in pattern alphabet
        for (x = 0; x < NO_OF_CHARS; ++x) {
            // If i = 0, always go to state 1 if the character matches
            if (i == 0) {
                TF[i][x] = (x == (unsigned char)pattern[0]) ? 1 : 0;
            }
            // For i > 0, try to extend current state
            else if (x == (unsigned char)pattern[i]) {
                TF[i][x] = i + 1;
            }
            // For mismatch, go back to a state that has longest proper prefix
            else {
                TF[i][x] = TF[i-1][x];
            }
        }
    }
    
    return TF;
}

// Search for pattern in text using finite automaton
void search(char* text, char* pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    int found = 0;
    
    int** TF = computeTransitionFunction(pattern, m);
    
    // Process text over the finite automaton
    int state = 0;
    for (int i = 0; i < n; i++) {
        state = TF[state][(unsigned char)text[i]];
        if (state == m) {
            printf("Pattern found at position: %d\n", i - m + 1);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Pattern not found in the text.\n");
    }
    
    // Free the allocated memory
    for (int i = 0; i <= m; i++) {
        free(TF[i]);
    }
    free(TF);
}

int main() {
    char text[1000], pattern[100];
    
    printf("Enter the text string: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // Remove newline
    
    printf("Enter the pattern to search for: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = 0; // Remove newline
    
    search(text, pattern);
    
    return 0;
}