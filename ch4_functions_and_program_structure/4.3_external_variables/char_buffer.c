#include <stdio.h> 

/*
    NOTES: 

    This is a combination of exercises 4-7, 4-8, and 4-9

    In evercise 4-9, I assume that the EOF error with the provided code is the following: 

        suppose one executes: 
            ungetch('a')
            ungetch(EOF)
            ungetch(EOF)
    
        one would want: 
            getch() -> EOF 
            getch() -> 'a'

        Instead, their implementation yields 
            getch() -> EOF
            getch() -> EOF
            getch() -> 'a'
*/

void ungetstr(const char s[]);
int getch();
int ungetch(int c);
int length(const char s[]);

int main() {
    ungetch('a');
    ungetch(EOF);
    ungetch(EOF);
    putchar(getch());
    putchar(getch()); 

    ungetstr("abcd");
    putchar(getch());
    putchar(getch());
    putchar(getch());
    putchar(getch());

    return 0;
}

/*
    "Un-gets" a string into the buffer.  That is, it puts a string into the buffer. 

    Parameters: 
        s : a string of characters 

    Output: 
        Puts the characters of s into the buffer as long as there is space in the buffer. 
        If the buffer runs out of space, the whole string s won't necessarily be entered. 
*/
void ungetstr(const char s[]) {
    for (int i = length(s) - 1; i >= 0; i--) {
        ungetch(s[i]);
    }
}

// 4.1_basics_of_functions/exercise4-1.c
int length(const char s[]) {
    int i = 0; 
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

// external variables of the buffer manager functions getch(), ungetch()

// maximum capacity of buffer 
#define BUFFER_SIZE 100

// error code for manager functions 
#define ERROR 0

// character buffer 
char buf[BUFFER_SIZE];

// index of buffer end
int end; 

/*
    Gets a character from the buffer if the buffer isn't empty or from keyboard. 

    Parameters: 
        None 

    Output: 
        Returns the next character from the end of the buffer if the buffer isn't empty 
        OR 
        Returns the next character from keyboard

        EOF can be returned if at end of input or if EOF is on buffer. 
*/
int getch() {
    if (end == 0) {
        return getchar();
    }
    else {
        end--;
        return buf[end];
    }
}

/*
    "Un-gets" a character from the buffer. That is, it puts the character into the buffer. 

    Parameters: 
        c : a character to push 

    Output: 
        If the character can be pushed, then the character is placed at the end of the buffer. 
        If the character is pushed, it is returned. 
        
        The character won't be pushed if the buffer is full OR if c = EOF and end of buffer is EOF. 
        This will prevent the EOF from being pushed multiple times. 
        If the character isn't pushed, ERROR is returned.
*/
int ungetch(int c) {
    if (end == BUFFER_SIZE) {
        return ERROR;
    }

    if (c != EOF || buf[end - 1] != EOF) {
        buf[end] = c;
        end++;
        return c;
    }

    return ERROR;
}



