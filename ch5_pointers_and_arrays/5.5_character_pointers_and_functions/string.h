#ifndef STRING_H
#define STRING_H

#include <stddef.h>

/*
    Gets the length of a character string. 

    Parameters: 
        c : pointer to character string 

        Note: this includes string literals (const)

    Output: 
        The length (size_t) of the character string. 

    Runtime: O(n)   - n = # chars referenced by c
*/
size_t strlen(const char *c);

/*
    Copies a source character string into a destination pointer. 

    Parameters: 
        src : pointer to character string (could be literal hence const)
        dest : pointer to destination 

    Output: 
        The characters referenced by src are loaded into dest. If dest has
        not been dynamically allocated to fit the characters src, the behavior
        is undefined.

    Runtime: O(n)   - n = # characters referenced by src
*/
void strcopy(const char *src, char *dest);

/*
    Compares two character strings lexicographically. 

    Parameters:
        s : pointer to 1st character string (could be literal, hence const)
        t : pointer to 2nd character string (could be literal as well)

    Output: 
        Characters referenced by s are compared to those referenced by t.
        If string s occurs before t lexicographically, then negative number is returned
        If string s occurs after t lexicographically, then positive number is returned 
        If string s and t are equal, then 0 is returned. 

        The number will always be a comparison of ascii values hence int return type is safe. 
    
    Runtime: O(m + n)   - m = # characters referenced by s, n = # characters referenced by t
*/
int strcmp(const char *s, const char *t);

/*
    Concatenates one string after another. 

    Parameters: 
        s : pointer to the string that will be lengthened 
        t : pointer to the string to concatenate to the end of s (can be literal, hence const)

    Output: 
        The characters referenced by t are concatenated to the end of s. 

        If s is not dynamically allocated to accomodate the characters of t as well, then behavior
        is undefined. 

    Runtime: O(m + n)   - m = # characters referenced by s, n = # characters referenced by t
*/
void strconcat(char *s, const char *t);

/*
    Checks if a character string ends with another character string. 

    Parameters: 
        s : pointer to the string whose ending characters will be checked (can be literal, hence const)
        t : pointer to the string who may end s (can be literal, hence const)

    Output: 
        1 if s ends with characters of t, 0 otherwise. 

    Runtime: O(m + n)   - m = # characters referenced by s, n = # characters referenced by t
*/
int strend(const char *s, const char *t);

/*
    Retrieves the first index of a character in a string of characters.

    Parameters: 
        s : pointer to a character string (can be literal, hence const)
        c : pointer to a character 

    Output: 
        The first index of the character c in s or -1 if c does not occur in s. 

    Runtime: O(n)   - n = # characters referenced by s
*/
int strindex(const char *s, char c);

/*
    Retrieves the first index of a character string in another string. 

    Parameters: 
        s : pointer to a character string (can be literal, hence const)
        t : pointer to a character string (can be literal, hence const) 

    Output: 
        The first index of t in s or -1 if t does not occur in s. 

    Runtime: O(m*n)   - m = # characters referenced by s, n = # characters referenced by t

    Note: this is a conservative worst case runtime, and in most instances, runtime will be closer to (m + n)
*/
int substr(const char *s, const char *t);

/*
    Reverses a string of characters. 

    Parameters: 
        s : pointer to a character string 
    
    Output: 
        The characters of s have been reversed. If s is not a dynamically allocated string, behavior is undefined. 

    Runtime: O(n)   - n = # characters referenced by s 
*/
void reverse(char *s);

/*
    Converts a string of characters into an integer. 

    Parameters: 
        s : pointer to a character string (can be literal, hence const)

    Output: 
        Integer (base-10) representation of characters referenced by s. 
        If the chars referenced by s do not form a valid integer, 0 is returned. 

    Runtime: O(n)   - n = # characters referenced by s
*/
int stringToInt(const char *s);

/*  
    Converts an integer into a string of characters. 

    Parameters: 
        s : buffer to store integer 
        n : an integer 

    Output: 
        The integer digits of n (and potential negative sign) are stored in character string
        referenced by s.

        If s is not a dynamically allocated array that can fit the integer n, the behavior is
        undefined. 

    Runtime: O(d)   - d = # digits in n
*/
void intToString(char *s, int n);

/*
    Converts a string of characters into a floating point number. 

    Parameters: 
        s : pointer to a character string (can be literal, hence const)

    Output: 
        A floating-point (base-10) representation of characters referenced by s. 
        If the chars referenced by s do not form a valid floating point number, 0.0 is returned. 

    Runtime: O(n)   - n = # characters referenced by s
*/
double stringToDouble(const char *s);

/*
    Gets a line of characters from keyboard input and stores them in a string buffer. 

    Parameters: 
        s : pointer to string buffer
        MAX_LEN : integer signifying 1 + max # characters allowed in 1 line 

    Output: 
        s is filled with up to MAX_LEN characters from a line of keyboard input.
            If s is not a properly allocated array, then behavior is undefined. 
        The number of characters in the line is returned (size_t for safety). 
            This could be more than the number of chars in s. 
        EOF is returned if getline() is called and there is no input to be read. 

    Runtime: 
        O(n)    - n = # characters in the line 
*/
size_t getline(char *s, int MAX_LEN);

/*
    Trims a character string of whitespace from the front and back. 

    Parameters: 
        s : pointer to character string 

    Output: 
        s has the whitespace removed from front, back
        If s is a string literal, behavior is undefined 

    Runtime: 
        O(n)    - n = # characters referenced by s 
*/
void trim(char *s);

#endif