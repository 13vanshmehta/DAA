#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR 256

void rabinKSearch(char text[], char pattern[], int prime, int array[], int *index) {
    int m = strlen(pattern);
    int n = strlen(text);
    int charIndex, pattHash = 0, strHash = 0, h = 1;
    
    for(int i = 0; i < m-1; i++) {
        h = (h * MAXCHAR) % prime;
    }
    
    for(int i = 0; i < m; i++) {
        pattHash = (MAXCHAR * pattHash + pattern[i]) % prime;
        strHash = (MAXCHAR * strHash + text[i]) % prime;
    }
    
    for(int i = 0; i <= (n - m); i++) {
        if(pattHash == strHash) {
            for(charIndex = 0; charIndex < m; charIndex++) {
                if(text[i + charIndex] != pattern[charIndex])
                    break;
            }
            
            if(charIndex == m) {
                (*index)++;
                array[(*index)] = i;
            }
        }
        
        if(i < (n - m)) {
            strHash = (MAXCHAR * (strHash - text[i] * h) + text[i + m]) % prime;
            if(strHash < 0) {
                strHash += prime;
            }
        }
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
    
    int prime = 13;
    int *locArray = (int *)malloc(strlen(text) * sizeof(int));
    int index = -1;
    
    if (locArray == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    rabinKSearch(text, pattern, prime, locArray, &index);
    
    if(index == -1) {
        printf("Pattern not found in the text.\n");
    } else {
        for(int i = 0; i <= index; i++) {
            printf("Pattern found at position: %d\n", locArray[i]);
        }
    }
    
    free(locArray);
    return 0;
}