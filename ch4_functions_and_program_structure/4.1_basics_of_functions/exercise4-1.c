#include <stdio.h> 

int rightIndex(const char str[], const char substr[]); 
int equals(const char str[], const char substr[], int index);
int length(const char s[]);

int main() {
    char t[] = "ab";
    char s1[] = "abab";
    printf("%d\n", rightIndex(s1, t)); // 2
    char s2[] = "ab";
    printf("%d\n", rightIndex(s2, t)); // 0
    return 0;
}

/*
    Returns the rightmost (last) index in a string in which a substring occurs. 

    Paramters: 
        str : a string 
        substr : a substring to search for in str
         
    Output: 
        the rightmost index in which substr occurs in str or -1 if substr never occurs
*/
int rightIndex(const char str[], const char substr[]) {
    int j = length(str) - 1;
    while (j >= 0) {
        if (equals(str, substr, j)) {
            return j;
        }
        j--;
    }
    return -1;
}

/*
    Checks to see if a given string occurs at a specific index in another string. 

    Paramters: 
        str : a string 
        substr : another string 
        index : index in str  

    Output: 
        1 if substr occurs at index in str 
        0 otherwise 

    Example: 
        str = "abc"
        substr = "bc"
        
        for index = 0, equals() returns 0
        for index = 1, equals() returns 1
        for index = 2, equals() returns 0
*/
int equals(const char str[], const char substr[], int index)
{
    int j = 0;

    while (substr[j] != '\0')
    {
        // if reached end of str (but not substr), return 0
        // if encountered unequal character, return 0
        if (str[index + j] == '\0' || substr[j] != str[index + j])
        {
            return 0;
        }
        j++;
    }

    // reached end of substr and substr[j] = str[index + j] for each j in substr
    return 1;
}

int length(const char s[]) {
    int i = 0; 
    while (s[i] != '\0') {
        i++;
    }
    return i;
}