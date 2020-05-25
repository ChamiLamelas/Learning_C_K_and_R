#include <stdio.h> 

/*
    NOTES: 

    1. The name of this file matches the section header on p. 16 of the text (1.5.1 File Copying) even
    though it is really user input that is copied. The stream is filled when the user presses 'Return'
    and then is copied and printed. This can be repeated for each time 'Return' is pressed. 'Ctrl+C'
    stops the program.

    2. Even though characters are technically being read, getchar() has int return type since EOF is
    a possible return value (constant in stdio.h signifying end-of-file). Therefore, int must be used
    for the variable currChar. 

    3. In response to exercise 1-7, EOF = -1. 
*/
int main() {
    int currChar = getchar();

    while (currChar != EOF) {
        putchar(currChar);
        currChar = getchar();
    }

    return 0; 
}