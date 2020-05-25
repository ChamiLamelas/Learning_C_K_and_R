#include <stdio.h>

/*
    NOTES: 

    This file contains a simple version of the UNIX wc command that provides line, word, and character
    counts for the input. This serves to combine the example code fragments in sections 1.5.2 through 
    1.5.4 in the text.

    You can compare an integer i with a character c. What will happen is that i will be compared with
    the ascii value of c. e.g. i == 'a' is equivalent to i == 97

    The character count includes whitespace characters. 

    Use Ctrl+Z to invoke EOF on Windows.
*/

int main()
{
    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;

    // used to track whether a word has been entered
    // can't just count words when spaces or tabs are entered other ' ' would count as 1 word
    // this is set to '1' when a word is entered (i.e. a non ws character seen)
    // this is set to '0' when a word is exited or hasn't been seen yet (i.e. a ws character seen)
    char enteredWord = '0';

    int currChar = getchar();
    while (currChar != EOF)
    {
        if (currChar == ' ' || currChar == '\n' || currChar == '\t')
        {
            if (enteredWord == '1')
            {
                wordCount++;
                enteredWord = '0';
            }
            if (currChar == '\n')
            {
                lineCount++;
            }
        }
        else
        {
            enteredWord = '1';
        }
        charCount++;
        currChar = getchar();
    }

    printf("Line count: %d\nWord count: %d\nCharacter count:%d\n", lineCount, wordCount, charCount);
    return 0;
}