#include <stdio.h> 

int push(int element);
int pop(void);
int size(void);
int peek(void);
int duplicate(void);
int swap(void);
void clear(void);

int main() {

    return 0;
}

// stack external variables, only to be used by stack functions below

// max stack size (assumed to be at least 2 by swap, duplicate)
#define STACK_SIZE 100

// error return value (should be made public to other files)
#define ERROR 0

// integer array to hold stack
int stack[STACK_SIZE]; 

// top index in stack
int top;

/*
    Pushes an element into the stack if there's space. 

    Parameters:
        element : an element to push 
    
    Output: 
        the element is pushed onto the top of the stack if there's space 
        if there's space, the element is returned 
        if there's no space, ERROR is returned
*/
int push(int element) {
    if (top == STACK_SIZE) {
        return ERROR;
    }

    stack[top] = element;
    top++;
    return element;
}

/*
    Pops the top element of the stack if one exists. 

    Parameters: 
        None 

    Output: 
        The top element of the stack is removed if one exists
        if an element was removed, it is returned
        if no element was removed (no top), ERROR is returned
*/
int pop(void) {
    if (top == 0) {
        return ERROR;
    }

    top--;
    return stack[top];
}

/*
    Returns the size of the stack (# current elements)
*/
int size(void) {
    return top;
}

/*
    Gets the top element in the stack if one exists

    Parameters: 
        None 

    Output: 
        the top element in the stack if one exists
        ERROR if none exists
*/
int peek(void) {
    if (top == 0) {
        return ERROR;
    }

    return stack[top - 1];
}

/*
    Duplicates the top element of the stack if one exists. 

    Parameters: 
        None 

    Output: 
        Duplicates the top element of the stack if one exists. 
        The top element if one exists (now there will be at least 2 occurrences on the top)
        ERROR if there was no top 
*/
int duplicate(void) {
    if (top == 0 || top == STACK_SIZE) {
        return ERROR;
    }

    stack[top] = stack[top - 1];
    top++;
    return stack[top - 1];
}

/*
    Swaps the top 2 elements on the stack. 

    Parameters: 
        None 

    Output: 
        Swaps the top 2 elements on the stack if at least 2 elements exist on the stack. 
        If 2 elements existed to be swapped, the new top is returned 
        If no 2 elements could be swapped, ERROR is returned
*/
int swap(void) {
    if (top <= 1) {
        return ERROR;
    }

    int tmp = stack[top - 1];
    stack[top - 1] = stack[top - 2];
    stack[top - 2] = tmp;
    return stack[top - 1];
}

/*
    Removes all of the elements from the stack.
*/
void clear(void) {
    top = 0;
}

