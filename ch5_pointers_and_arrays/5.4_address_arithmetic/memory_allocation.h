/*
    This file contains a stack based memory allocation library for dynamically storing character data
    at runtime.
*/

#ifndef MEMORY_ALLOCATION_H
#define MEMORY_ALLOCATION_H

/*
    Frees the space allocated to a provided character pointer from the top of the stack memory buffer. 

    Parameters: 
        ptr : a character pointer 

    Output: 
        The space at the top of the stack memory buffer that was allocated to ptr is now freed for 
        future allocation.

        The pointer ptr still has access to this buffer and can change the buffer in future leading to
        bugs. Therefore, it is recommended that the calling function set ptr to NULL following the use
        of this function.
*/
void free(char *ptr);

/*
    Allocates space at the top of the stack memory buffer for a provided number of characters. 

    Parameters: 
        numChars : the number of characters needed 

    Output: 
        Allocates space for numChars characters at the top of the buffer and returns a character pointer
        to that allocated space.
*/
char *alloc(int numChars);

#endif 