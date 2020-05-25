#include <stdio.h>

/*
    NOTES: 

    In this program a tab is counted as "multiple blanks" and is replaced with a single space. 
    Newlines are not replaced. 
*/

int main()
{
    int currChar = getchar();
    // tracks if blanks have been seen since the last non blank character 
    // this is set to '1' when ' ' or '\t' are seen 
    // when a non blank is seen and a blank is seen prior, put a space before putting non blank char
    char seenBlanks = '0';

    while (currChar != EOF)
    {
        if (currChar == ' ' || currChar == '\t') {
            seenBlanks = '1';
        }
        else {
            if (seenBlanks == '1')  {
                putchar(' ');
                seenBlanks = '0';
            }
            putchar(currChar);
        }

        currChar = getchar(); 
    }

    return 0;
}