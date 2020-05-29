/*
    This file holds the implementation of memory_allocation.h 
*/

#include "memory_allocation.h"
#include <stdio.h> // needed for NULL 

// capacity of buffer 
#define BUF_SIZE 1000

// character buffer (static to not allow access after compilation to object file)
static char buf[BUF_SIZE]; 

// Tracks the index in the buffer for next allocation (static for same reason as above)
// Slightly different from textbook implementation which uses a pointer at "top" of buffer instead
static int top; 

void free(char *ptr) {
    // if ptr is not pointing to anything in the buffer, return immediately 
    if (ptr < buf || ptr >= buf + BUF_SIZE) {
        return;
    }
    top = ptr - buf;
}

char *alloc(int numChars) {
    // if user asked for too much space, return NULL to signify space couldn't be allocated
    if (top + numChars > BUF_SIZE) {
        return NULL;
    }
    // else create, return a pointer to allocated space and update top 
    else {
        char *tmp = &buf[top];
        top += numChars;
        return tmp;
    }
}
