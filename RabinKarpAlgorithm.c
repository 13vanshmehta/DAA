#include <stdio.h>
#include <string.h>

#define d 256 // Number of characters in the input alphabet

void rabinKarp(char pattern[], char text[], int q) {
    int M = strlen(pattern);
    int N = strlen(text);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;
    int found = 0;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {
        // Check the hash values of current window of text and pattern
        // If the hash values match then only check for characters one by one
        if (p == t) {
            // Check for characters one by one
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            // If p == t and pattern[0...M-1] = text[i, i+1, ...i+M-1]
            if (j == M) {
                printf("Pattern found at position: %d\n", i);
                found = 1;
            }
        }

        // Calculate hash value for next window of text: Remove leading digit,
        // add trailing digit
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            // We might get negative value of t, converting it to positive
            if (t < 0)
                t = (t + q);
        }
    }

    if (!found) {
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
    
    // A prime number for hash calculation
    int q = 101;
    
    rabinKarp(pattern, text, q);
    
    return 0;
}