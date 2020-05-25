#include <stdio.h>

void squeeze(char s[], int c);

int main()
{
    char s[] = "ababa";
    squeeze(s, 'a');
    printf("%s\n", s);
    squeeze(s, 'a');
    printf("%s\n", s);
    squeeze(s, 'b');
    printf("%s\n", s);

    return 0;
}

/*
    Removes all occurrences of a character c from a string s. 

    Parameters: 
        s : an array of characters 
        c : a character c 
*/
void squeeze(char s[], int c)
{
    int i = 0;
    int j = 0;

    while (s[i] != '\0')
    {
        if (s[i] != c)
        {
            s[j] = s[i];
            j++;
        }
        i++;
    }

    s[j] = '\0';
}