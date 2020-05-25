#include <stdio.h>

int stringToInt(char s[]);

int main()
{
    char s[4]; 
    s[0] = '1';
    s[1] = '2';
    s[2] = '3';
    s[3] = '\0';

    printf("%d\n", stringToInt(s));
    return 0;
}

/*
    Converts a string containing a positive integer into that integer. If the string does not contain
    a positive integer, then a negative integer is returned. 
*/
int stringToInt(char s[])
{
    int res = 0;
    int i = 0;

    while (s[i] != '\0')
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return -1;
        }

        res = 10 * res + (s[i] - '0');
        i++;
    }

    return res;
}
