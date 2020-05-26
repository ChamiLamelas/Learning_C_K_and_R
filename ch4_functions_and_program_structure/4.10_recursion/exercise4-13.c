#include <stdio.h> 

void reverse(char s[]);
void reverseHelper(char s[], int index, int n);
int length(const char s[]);

int main() {
    char s[] = "abc";
    reverse(s);
    printf("%s\n", s);

    return 0; 
}

void reverse(char s[]) {
    reverseHelper(s, 0, length(s));
}

void reverseHelper(char s[], int index, int n) {
    if (index >= n - index - 1) {
        return;
    }

    int tmp = s[index];
    s[index] = s[n - index - 1];
    s[n - index - 1] = tmp;
    reverseHelper(s, index + 1, n);
}

// 4.1_basics_of_functions/exercise4-1.c
int length(const char s[]) {
    int i = 0; 
    while (s[i] != '\0') {
        i++;
    }
    return i;
}
