#include <stdio.h>
#include <ctype.h> // needed for isspace()

/*
    NOTES: 

    textbook only removes training whitespace
*/

void trim(char s[]);

int main()
{
    char s1[] = "123";
    trim(s1);
    printf("[%s]\n", s1); // 123
    char s2[] = "123 ";
    trim(s2);
    printf("[%s]\n", s2); // 123
    char s3[] = " 123";
    trim(s3);
    printf("[%s]\n", s3); // 123
    char s4[] = " 123 ";
    trim(s4);
    printf("[%s]\n", s4); // 123
    char s5[] = "1 3";
    trim(s5);
    printf("[%s]\n", s5); // 1 3
    char s6[] = " 1 3 ";
    trim(s6);
    printf("[%s]\n", s6); // 1 3
    char s7[] = "   123   ";
    trim(s7);
    printf("[%s]\n", s7); // 123
    char s8[] = "   1 2 3   ";
    trim(s8);
    printf("[%s]\n", s8); // 1 2 3
    char s9[] = "\t1\t2\t";
    trim(s9);
    printf("[%s]\n", s9); // 1  2 (tabbed)
    char s10[] = "\n1\n2\n";
    trim(s10);
    printf("[%s]\n", s10); // 1 on a line, 2 on a line
    return 0;
}

/*
    Given a string of characters, removes all leading and trailing whitespace.

    Parameters: 
        s : a string of characters 
    
    Output: 
        s has its leading and trailing whitespace removed
*/
void trim(char s[])
{

    // compute # of leading spaces
    int numLeadingSpaces = 0;
    while (s[numLeadingSpaces] != '\0' && isspace(s[numLeadingSpaces]))
    {
        numLeadingSpaces++;
    }

    // this will hold index of last non WS character (NOTE: index in original s, not post-shifting)
    int lastNonWS = numLeadingSpaces;

    // this will be used to shift characters of s over after # leading spaces have been identified
    int i = 0;

    // inserting at s[i], s[i + numLeadingSpaces] will be the char being shifted
    while (s[i + numLeadingSpaces] != '\0')
    {
        // if non space character, update index
        if (!isspace(s[i + numLeadingSpaces]))
        {
            lastNonWS = i + numLeadingSpaces;
        }

        // shift character by numLeadingSpaces
        s[i] = s[i + numLeadingSpaces];

        // update index for next shift
        i++;
    }

    // want to put null character after last non whitespace character (hence + 1) in shifted string
    // (hence - numLeadingSpaces)
    s[lastNonWS + 1 - numLeadingSpaces] = '\0';
}