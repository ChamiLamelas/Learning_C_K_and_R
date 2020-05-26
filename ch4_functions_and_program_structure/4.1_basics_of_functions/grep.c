#include <stdio.h>

/*
    NOTES: 

    equals() could be generalized using pointers to a string comparison function by getting pointer
    to specific array position in string
*/

int getline(char line[], int MAX_LENGTH);
int search(const char str[], const char substr[]);
int equals(const char str[], const char substr[], int index);

int main()
{
    const int MAX_LENGTH = 1000;
    char pattern[MAX_LENGTH];
    printf("Enter grep pattern: ");
    const int PATTERN_LEN = getline(pattern, MAX_LENGTH);

    // user cancels early with EOF (Ctrl+Z/D)
    if (PATTERN_LEN == EOF)
    {
        return 0;
    }

    printf("\nAny line with pattern that you type will be printed.\n\n");
    char line[MAX_LENGTH];
    int lineLen = getline(line, MAX_LENGTH);

    while (lineLen != EOF)
    {
        if (search(line, pattern))
        {
            printf("%s\n", line);
        }
        lineLen = getline(line, MAX_LENGTH);
    }

    return 0;
}

// see ch1_a_tutorial_introduction/1.9_character_arrays/exercise1-16.c
int getline(char line[], int MAX_LENGTH)
{
    int currChar = getchar();

    if (currChar == EOF)
    {
        return EOF;
    }
    else if (currChar == '\n')
    {
        line[0] = '\0';
        return 0;
    }

    int i = 0;
    while (currChar != EOF && currChar != '\n')
    {
        if (i < MAX_LENGTH - 1)
        {
            line[i] = currChar;
        }
        i++;
        currChar = getchar();
    }

    if (i < MAX_LENGTH - 1)
    {
        line[i] = '\0';
    }
    else
    {
        line[MAX_LENGTH - 1] = '\0';
    }

    return i;
}

/*
    Performs a linear search to identify if a string contains another string as a substring. 

    Parameters: 
        str : a string to search 
        substr : the substring to search in str for 

    Output: 
        1 if substr is found in str
        0 if substr is not found 
*/
int search(const char str[], const char substr[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (equals(str, substr, i))
        {
            return 1;
        }
        i++;
    }

    return 0;
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