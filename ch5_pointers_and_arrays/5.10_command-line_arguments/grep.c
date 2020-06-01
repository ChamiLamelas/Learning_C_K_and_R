#include "C:\Users\Chami\programming\c\kernigan_ritchie\ch5_pointers_and_arrays\5.5_character_pointers_and_functions\string.h"
#include "C:\Users\Chami\programming\c\kernigan_ritchie\ch5_pointers_and_arrays\5.4_address_arithmetic\memory_allocation.h"
#include <stdio.h>

int readLines(char *lines[]);

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[])
{
    // grep needs arguments
    if (argc == 1)
    {
        return 1;
    }

    // s will concatenate the arguments with spaces between them (even if the input was not spaces)
    char *s = alloc(MAX_LINE_LENGTH);
    *s = '\0';
    for (int i = 1; i < argc; i++) {
        strconcat(s, argv[i]);
        if (i < argc - 1) {
            strconcat(s, " ");
        }
    }

    char *lines[MAX_LINES];
    int numLines = readLines(lines);

    // for each line, see if it contains s. If so, print it
    for (int i = 0; i < numLines; i++)
    {
        if (substr(lines[i], s) >= 0)
        {
            printf("%s\n", lines[i]);
        }
    }

    return 0;
}

// see ch5_pointers_and_arrays/5.6_pointer_arrays/line_sort.c
int readLines(char *lines[])
{
    int numLines = 0;
    lines[0] = alloc(MAX_LINE_LENGTH);
    int len = getline(lines[0], MAX_LINE_LENGTH);

    while (len != EOF && numLines < MAX_LINES - 1)
    {
        numLines++;
        lines[numLines] = alloc(MAX_LINE_LENGTH);
        len = getline(lines[numLines], MAX_LINE_LENGTH);
    }

    return numLines;
}
