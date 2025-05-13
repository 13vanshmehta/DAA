#include <stdio.h>
#include <string.h>

void naiveStringMatch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;
    
    for (int i = 0; i <= n - m; i++) {
        int j;
        
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        
        if (j == m) {
            printf("Pattern found at position: %d\n", i);
            count++;
        }
    }
    
    if (count == 0) {
        printf("Pattern not found");
    } else {
        printf("Pattern found %d times", count);
    }
}

int main() {
    char text[1000], pattern[100];
    
    printf("Enter TEXT: ");
    scanf("%s", text);
    getchar();
    
    printf("Enter PATTERN: ");
    scanf("%s", pattern);
    printf("\n");
    
    naiveStringMatch(text, pattern);
    
    return 0;
}