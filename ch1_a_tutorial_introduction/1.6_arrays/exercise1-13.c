#include <stdio.h> 

int main() {

    int MAX_WORD_LENGTH = 30;
    int frequencies[MAX_WORD_LENGTH];

    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        frequencies[i] = 0;
    }

    int currChar = getchar();
    int lastWordLength = 0; 
    while (currChar != EOF) {
        if (currChar == ' ' || currChar == '\t' || currChar == '\n') {
            frequencies[lastWordLength - 1]++;
            lastWordLength = 0;
        }
        else {
            lastWordLength++;
        }
        currChar = getchar(); 
    }

    printf("Histogram of Word Frequencies by Length in characters\n\n");
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        printf("%d\t",i+1);
        for (int j = 0; j < frequencies[i]; j++) {
            putchar('*');
        }
        putchar('\n');
    }

    return 0;
}