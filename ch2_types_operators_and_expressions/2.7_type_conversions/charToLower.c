#include <stdio.h> 

int charToLower(int c); 

int main() {
    putchar(charToLower('A'));
    putchar(charToLower('Z'));

    return 0; 
}

/*
    Converts a given character into lowercase as long as it is an uppercase ASCII character. 

    Parameters: 
        c : a character 

    Output: 
        returns the lowercase version of c if c is an upper case ASCII character
        if c is not uppercase, then it returns c unedited (inc. non characters)
*/
int charToLower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return 'a' + (c - 'A');
    }
    else {
        return c;
    }
}