#include <stdio.h>
#include <ctype.h> // needed for isdigit, isalpha

/*
    NOTES: 

    Challenging question!
*/
void expand(const char compressed[], char expanded[]);
int expandHelper(char expanded[], int loadPt, char start, char end, int mode);

int main()
{
    char e[100];
    char c1[] = "0-9";
    expand(c1, e);
    printf("%s\n", e); // should be 0123456789
    char c2[] = "a-z";
    expand(c2, e);
    printf("%s\n", e); // should be abcdefghijklmnopqrstuvwxyz
    char c3[] = "A-Z";
    expand(c3, e);
    printf("%s\n", e); // should be ABCDEFGHIJKLMNOPQRSTUVWXYZ
    char c4[] = "-1-3-";
    expand(c4, e);
    printf("%s\n", e); // should be -123-
    char c5[] = "-123-";
    expand(c5, e);
    printf("%s\n", e); // should be -123-
    char c6[] = "1-1";
    expand(c6, e);
    printf("%s\n", e); // should be 1
    char c7[] = "3-1";
    expand(c7, e);
    printf("%s\n", e); // should be 3-1
    char c8[] = "1-2-3";
    expand(c8, e);
    printf("%s\n", e); // should be 123
    char c9[] = "1-1-1";
    expand(c9, e);
    printf("%s\n", e); // should be 1
    char c10[] = "1-2-3-4-5";
    expand(c10, e);
    printf("%s\n", e); // should be 12345
    return 0;
}

/*
    Expands a compressed (shorthand) version of a string into an expanded (long) version. 
    The decompressions that occur are: 

    0-9 -> 0123456789
    a-z -> abcdefghijklmnopqrstuvwxyz 

    All other characters are left the same. 

    Parameters:
        compressed : the compressed (shorthand) string whose expanded version will be found 
            (not edited - const)
        expanded : the expanded (long) string

    Output: 
        expanded version of 'compressed' string is placed into 'expanded' string 
*/
void expand(const char compressed[], char expanded[])
{
    // iterate over compressed 
    int i = 0; 
    // iterate over expanded
    int j = 0; 
    // marks index of last char in last digit short hand - used for setting mode in expandHelper()
    int lastDigSH = -1; 
    // marks index of last char in last alphabetic short hand - used for setting mode in expandHelper()
    int lastAlpSH = -1; 
 
    while (compressed[i] != '\0')
    {
        // if we've found range of form x-y where x, y digits (e.g. 0-9)
        if (isdigit(compressed[i]) && compressed[i + 1] == '-' && isdigit(compressed[i + 2])) {
            // if i matches index of last digit SH seen previously, use expandHelper() mode 1 
            // this handles case where we have something like 1-2-3 where i is at 2. 
            // also will handle more general cases like 1-2-3-4-5
            if (i == lastDigSH) {
                j = expandHelper(expanded, j, compressed[i], compressed[i + 2], 1);
            }
            // otherwise, i is at least lastDigSH+1 (that is, it's its own range)
            else {
                j = expandHelper(expanded, j, compressed[i], compressed[i + 2], 0);
            }
            // i should go to end of range (NOT one beyond it). This way, if-statement above
            // can detect cases like 1-2-3
            i += 2;
            // update last dig SH
            lastDigSH = i;
        }

        // similar logic for digit case commented above
        else if (isalpha(compressed[i]) && compressed[i + 1] == '-' && isalpha(compressed[i + 2])) {
            if (i == lastAlpSH) {
                j = expandHelper(expanded, j, compressed[i], compressed[i + 2], 1);
            }
            else {
                j = expandHelper(expanded, j, compressed[i], compressed[i + 2], 0);
            }
            i += 2; 
            lastAlpSH = i;
        }
        else {
            // make sure we are not repeating end of a SH when printing
            // e.g. for 1-3, we want 123 nor 1233
            // this is because i gets incremented only by 2 in above cases 
            // only updated expanded, j when is not the end of a SH and compressed[i] is some standalone char
            if (i != lastDigSH && i != lastAlpSH) {
                expanded[j] = compressed[i];
                j++;
            }
            i++;
        }
    }

    // remember, terminate with null char
    expanded[j] = '\0';
}

/*
    Helper function to expand() that loads a range into the expanded string starting at a specific 
    load point. The range is delimited by a start and end character. (e.g. 0 to 9, a to z, etc.)
    
    There are also 2 modes. 
        mode 0 is the normal mode where 0-3 is expanded to 0123. 
        mode 1 is to handle "nested" ranges. e.g. 1-2-3 should be expanded to 123 NOT 1223. 

    Parameters: 
        expanded : string to load with expansion
        loadPt : where expansion should be loaded into 
        start : starting character of shorthand to expand
        end : ending character of shorthand to expand 
        mode : handling mode described above 

    Output: 
        If start-end is a valid range of length n, then expanded[loadPt...loadPt+n-1] is filled
        with expanded range according to the mode setting. 

        If start-end is invalid (for instance we have something like 9-5), then the literals are
        placed into the range according to the mode setting.

        In all cases, the next load point is returned (where future expansions should be made
        in expand() function).
*/
int expandHelper(char expanded[], int loadPt, char start, char end, int mode)
{
    // if compressed has something like "9-5", this is interpreted literally as characters 9-5 
    // however, if mode = 1, that means something like "7-9-5". This should only add "-5".
    if (start > end)
    {
        if (mode == 0) {
            expanded[loadPt++] = start;
        }
        expanded[loadPt++] = '-';
        expanded[loadPt++] = end;
        return loadPt;
    }
    else
    {
        char curr = start;
        if (mode == 1) {
            curr++;
        }
        while (curr <= end)
        {
            expanded[loadPt++] = curr;
            curr++;
        }
        return loadPt;
    }
}