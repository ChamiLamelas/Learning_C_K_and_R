#include <stdio.h>

void reverse(char s[]);

int main() {
    char s[4];
    s[0] = 'a';
    s[1] = 'b';
    s[2] = 'c';
    s[3] = '\0';

    reverse(s);
    printf("%s\n", s);

    return 0; 
}

void reverse(char s[]) {
    int len = 0; 
    while (s[len] != '\0') {
        len++; 
    }

    int tmp = 0; 
    for (int i = 0; i < len/2; i++) {
        tmp = s[0];
        s[0] = s[len - i - 1];
        s[len - i - 1] = tmp;
    }
}
