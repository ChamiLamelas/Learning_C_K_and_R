#include <stdio.h>

int any(const char s1[], const char s2[]);
int search(const char s[], int c);

int main()
{
    char s1[] = "abc";
    char s2[] = "bac";

    printf("%d\n", any(s1, s2));

    return 0;
}

int any(const char s1[], const char s2[])
{
    int i = 0;
    int firstOccurrence = -1;
    int searchRes = -1;
    while (s2[i] != '\0')
    {
        searchRes = search(s1, s2[i]);
        if (searchRes != -1)
        {
            if (firstOccurrence == -1 || searchRes < firstOccurrence)
            {
                firstOccurrence = searchRes;
            }
        }
        i++;
    }
    return firstOccurrence;
}

/*
    Performs a linear search of a string s to identify the index of the first occurence of c. 

    Parameters: 
        s : a string to be searched
        c : a character to search for 

    Output: 
        the index of the first occurrence of c in s
        or -1 if no occurrences exist
    
    s will not be modified (const)
*/
int search(const char s[], int c)
{
    int k = 0;
    while (s[k] != '\0')
    {
        if (s[k] == c)
        {
            return k;
        }
        k++;
    }
    return -1;
}
