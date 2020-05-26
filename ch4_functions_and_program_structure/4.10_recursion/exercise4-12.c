#include <stdio.h>

/*
    NOTES: 

    Challenging question!

*/

void intToString(char s[], int n);
int intToStringHelp(char s[], int n, int offset);

int main()
{
    char s[100];
    intToString(s, 123);
    printf("%s\n", s);

    intToString(s, -123);
    printf("%s\n", s);

    return 0;
}

/*
    Converts an integer n into a string s. 

    Parameters:
        s : character array to be filled with string version of number stored in n
        n : an integer number (positive or negative)

    Pre-conditions:
        s is large enough to accomodate all the digits (and the possible negative sign) in n. 

    Output: 
        s is loaded with n.
*/
void intToString(char s[], int n)
{
    if (n == 0)
    {
        s[0] = '0';
        s[1] = '\0';
    }
    else if (n < 0)
    {
        s[0] = '-';
        s[intToStringHelp(s, n * -1, 1) + 1] = '\0';
    }
    else
    {
        s[intToStringHelp(s, n, 0)] = '\0';
    }
}

/*
    Helper function to intToString() that recursively converts an integer n into a string. 

    Parameters: 
        s : character array to fill with string version of n
        n : a positive* integer
        offset : discussed below

    The offset is used to mark that s should be filled starting from index 1 as opposed to 0. 
    This is because intToString() adds a '-' at s[0] before making n positive before using
    this function. offset = 1 ==> n was originally negative, offset = 0 ==> n was positive. 
            
    Output: 
        s is filled with the value n. 
*/
int intToStringHelp(char s[], int n, int offset)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        int len = intToStringHelp(s, n / 10, offset);
        s[len + offset] = (n % 10) + '0';
        return 1 + len;
    }
}