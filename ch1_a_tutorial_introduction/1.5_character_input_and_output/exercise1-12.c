#include <stdio.h> 

int main() {
    int currChar = getchar();
    char inWord = '0';

    while (currChar != EOF) {
        if (currChar == '\n' || currChar == ' ' || currChar == '\t') {
            if (inWord == '1') {
                putchar('\n');
                inWord = '0';
            }
        }
        else {
            putchar(currChar);
            inWord = '1';
        }
        currChar = getchar();
    }
}