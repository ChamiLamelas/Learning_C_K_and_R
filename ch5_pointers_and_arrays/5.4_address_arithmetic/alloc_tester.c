#include <stdio.h> 
#include "memory_allocation.h"

int main() {
    char *p1 = alloc(4);
    *p1 = 'a';
    *(p1 + 1) = 'b';
    *(p1 + 2) = 'c';
    *(p1 + 3) = '\0';
    printf("%s\n", p1); // abc 

    char *p2 = alloc(4); 
    *p2 = '1';
    *(p2 + 1) = '2';
    *(p2 + 2) = '3';
    *(p2 + 3) = '\0';
    printf("%s\n", p1); // abc 
    printf("%s\n", p2); // 123

    free(p2);
    printf("%s\n", p1); // abc 

    free(p1);

    char *p3 = alloc(3);
    *p3 = 'o';
    *(p3 + 1) = 'k';
    *(p3 + 2) = '\0';
    printf("%s\n", p3);

    return 0;
}