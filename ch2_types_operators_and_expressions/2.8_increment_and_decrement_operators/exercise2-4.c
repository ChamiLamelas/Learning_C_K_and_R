#include <stdio.h>

/*
    NOTES: 

    if (x == 0) {...} is equivalent to if (!x) {...} 
    if (x == 1) {...} is equivalent to if (x) {...}
    If a variable is equal to 0, then that condition is deemed false. Otherwise, true.
*/

void squeeze(char s1[], const char s2[]);
int search(const char s[], int c); 

int main() {
    char s[] = "cabcabc";
    char t[] = "ab";

    squeeze(s, t);
    printf("%s\n", s);

    return 0; 
}

/*
    Removes all characters from one string that occur in a second string. 

    Parameters: 
        s1 : a string that will be "squeezed" of all characters that appear in s2
        s2 : string of characters to squeeze from s1 

    Output: 
        s1 will be updated to only contain the characters that don't appear in s2 
    
    s2 will not be modified (const)
*/
void squeeze(char s1[], const char s2[]) {
    int i = 0; 
    int j = 0;
     
    while (s1[i] != '\0') {
        if (!search(s2, s1[i])) {
            s1[j] = s1[i];
            j++;
        }
        i++;
    }

    s1[j] = '\0';
}

/*
    Performs a linear search of a string s for the character c. 

    Parameters: 
        s : a string to be searched
        c : a character to search for 

    Output: 
        1 - if c occurs in s
        0 - if c does not 
    
    s will not be modified (const)
*/
int search(const char s[], int c) {
    int k = 0; 
    while (s[k] != '\0') {
        if (s[k] == c) {
            return 1; 
        }
        k++;
    }
    return 0;
}


