#include <stdio.h>

/*
    NOTES: 

    string literals can only be used at character array initialization 
    e.g.    char s[] = "123"; 
            s = "-123";
        
            does not work
*/

int stringToInt(char s[]);

int main()
{
    char s[] = "123";
    printf("%d\n", stringToInt(s));
    char t[] = "-123";
    printf("%d\n", stringToInt(t));

    return 0;
}

int stringToInt(char s[])
{
    int sign = 1;
    int num = 0;
    int i = 0;
    if (s[0] == '-')
    {
        sign = -1;
        i++;
    }
    while (s[i] != '\0')
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            num = num * 10 + (s[i] - '0');
        }
        // else: error (not a digit)
        i++;
    }

    return sign * num;
}