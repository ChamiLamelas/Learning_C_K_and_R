#include <stdio.h>

/*
    NOTES: 

    Counting frequencies of letters only a-z, A-Z

    putchar() when passed an integer, will print it as a character
    for instance putchar(97) prints 'a' not '97'. this is used in histogram code below.
 */
int main()
{
    int frequencies[52];
    for (int i = 0; i < 52; i++)
    {
        frequencies[i] = 0;
    }

    int currChar = getchar();

    while (currChar != EOF)
    {
        if (currChar >= 'a' && currChar <= 'z')
        {
            frequencies[currChar - 'a']++;
        }
        else if (currChar >= 'A' && currChar <= 'Z')
        {
            frequencies[currChar - 'A' + 26]++;
        }

        currChar = getchar();
    }

    printf("Histogram of Letter (a-z, A-Z) Frequencies\n\n");

    for (int i = 0; i < 52; i++)
    {
        if (i < 26)
        {
            putchar('a' + i);
        }
        else
        {
            putchar('A' + (i - 26));
        }
        putchar('\t');
        for (int j = 0; j < frequencies[i]; j++)
        {
            putchar('*');
        }
        putchar('\n');
    }

    return 0;
}