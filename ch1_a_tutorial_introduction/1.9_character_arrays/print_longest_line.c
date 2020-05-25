#include <stdio.h>

int getline(char buf[], int bufLen);
void copy(char src[], char dest[]);
void print(char arr[]);

/*
    NOTES: 

    printf("%s", arr) can be used to print a character array 'arr'

    program assumes input lines do not exceed 100 characters
*/
int main()
{
    int MAX_LINE_LENGTH = 100;
    int maxSeen = 0;
    char currLine[MAX_LINE_LENGTH];
    char maxLine[MAX_LINE_LENGTH];
    int currLen = getline(currLine, MAX_LINE_LENGTH);

    while (currLen != EOF)
    {
        if (currLen > maxSeen)
        {
            maxSeen = currLen;
            copy(currLine, maxLine);
        }

        currLen = getline(currLine, MAX_LINE_LENGTH);
    }

    if (maxSeen > 0)
    {
        print(maxLine);
    }
    return 0;
}

/*
    Reads a line of text from the console. 
    
    Parameters: 
        buf : character array to load with console input
        bufLen : length of buf 

    Output: 
        If line has less than 'bufLen-1' characters, then line's length is returned
        If line has more than or equal to 'bufLen - 1' characters, then bufLen - 1 is returned
            (this will lead to invalid behavior for lines that vary in length but are longer than bufLen - 1)
        If EOF has been reached immediately, then EOF returned and buf is not edited
        If line has more than 'bufLen - 1' characters, only (bufLen - 1) characters are included. 
        If line never terminated with '\n', when EOF is reached, all input is considered 1 line.
*/
int getline(char buf[], int bufLen)
{
    int i = 0;
    int currChar = getchar();

    // check here before loop to see if EOF or newline reached immediately
    // if EOF reached, then EOF should be returned and buffer not edited
    // if newline reached, then 0 returned and buffer is empty
    if (currChar == EOF)
    {
        return EOF;
    }
    else if (currChar == '\n')
    {
        buf[0] = '\0';
        return 0;
    }

    // if this stops for EOF, getline needs to be called again to return EOF so that read line's length can be
    // properly returned
    // stop for i = len - 1 to include terminating null char
    while (currChar != EOF && currChar != '\n' && i < bufLen - 1)
    {
        buf[i] = currChar;
        currChar = getchar();
        i++;
    }

    buf[i] = '\0';
    return i - 1;
}

/*
    Copies the characters from a source character array into a destination array with adequate size. 

    Parameters: 
        src : the source character array
        dest : the destination array 

    Pre-conditions:
        src is terminated with null character 
        dest has enough space to accomodate characters in src
*/
void copy(char src[], char dest[])
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
}

/*
    Prints the contents of a character array followed by a newline. 

    Parameters: 
        arr : the character array to print

    Pre-conditions: 
        arr is terminated with null character
*/
void print(char arr[])
{
    int i = 0;
    while (arr[i] != '\0')
    {
        putchar(arr[i]);
        i++;
    }

    putchar('\n');
}
