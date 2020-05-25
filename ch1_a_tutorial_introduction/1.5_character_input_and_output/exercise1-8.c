#include <stdio.h>

int main()
{
    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;
    int wsCount = 0;

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
            wsCount++;
        }
        else
        {
            enteredWord = '1';
        }
        charCount++;
        currChar = getchar();
    }

    printf("Line count: %d\nWord count: %d\nCharacter count:%d\nWhitespace count:%d\n", lineCount, wordCount, charCount, wsCount);
    return 0;
}